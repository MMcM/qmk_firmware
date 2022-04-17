
#include "debug.h"
#include "matrix.h"
#include "print.h"
#include "quantum.h"

/*
 * Received codes. (See https://sbeach.up.seesaa.net/image/141115_01_66SR_keycode.jpg.)
 * For matrix codes, see nec_pc_6601sr.h.
 *
 * Base:
 * +---+  +---+
 * |   |  |408|
 * +---+  +---+
 *
 * +---+---+-------+-------+-------+-------+-------+---+---+-----+
 * |1FA|1FD|1F0    |1F1    |1F2    |1F3    |1F4    |00C|0FE|07F  |
 * +-------------------------------------------------------------+
 * |01B|031|032|033|034|035|036|037|038|039|030|02D|05E|05C|012  |
 * +-------------------------------------------------------------+
 * |009  |071|077|065|072|074|079|075|069|06F|070|040|05B|05D|   |
 * +---------------------------------------------------------|   |
 * |      |061|073|064|066|067|068|06A|06B|06C|03B|03A|0DB|00D   |
 * +-------------------------------------------------------------+
 * |        |07A|078|063|076|062|06E|06D|02C|02E|02F|    |01E|1FE|
 * +-------------------------------------------------------------+
 * |1FB|   |020                                      |01D|01F|01C|
 * +---+---+-----------------------------------------+---+---+---+
 *
 * Shift:
 * +---+---+-------+-------+-------+-------+-------+---+---+-----+
 * |1FA|1FD|1F5    |1F6    | 1F7   |1F8    |1F9    |00B|1FC|07F  |
 * +-------------------------------------------------------------+
 * |01B|021|022|023|024|025|026|027|028|029|0A6|03D|000|000|012  |
 * +-------------------------------------------------------------+
 * |009  |051|057|045|052|054|059|055|049|04F|059|040|0A2|0A3|   |
 * +---------------------------------------------------------|   |
 * |      |041|053|044|046|047|048|04A|04B|04C|02B|02A|05F|00D   |
 * +-------------------------------------------------------------+
 * |        |05A|058|043|056|042|04E|04D|03C|03E|03F|    |01E|1FE|
 * +-------------------------------------------------------------+
 * |1FB|   |020                                      |01D|01F|01C|
 * +---+---+-----------------------------------------+---+---+---+
 *
 * Ctrl:
 * +---+---+-------+-------+-------+-------+-------+---+---+-----+
 * |202|1FD|100    |100    |100    |100    |100    |00C|0FE|07F  |
 * +-------------------------------------------------------------+
 * |000|000|000|000|000|000|000|000|000|000|000|000|000|000|012  |
 * +-------------------------------------------------------------+
 * |000  |011|017|005|012|014|019|015|009|00F|010|000|01B|01D|   |
 * +---------------------------------------------------------|   |
 * |      |001|013|004|006|007|008|00A|00B|00C|000|000|000|000   |
 * +-------------------------------------------------------------+
 * |        |01A|018|003|016|002|00E|00D|000|000|000|000 |000|1FE|
 * +-------------------------------------------------------------+
 * |1FB|   |000                                      |000|000|000|
 * +---+---+-----------------------------------------+---+---+---+
 *
 * Graph:
 * +---+---+-------+-------+-------+-------+-------+---+---+-----+
 * |100|1FD|1F0    |1F1    |1F2    |1F3    |1F4    |00C|0FE|07F  |
 * +-------------------------------------------------------------+
 * |100|107|101|102|103|104|105|106|10D|10E|10F|117|100|109|012  |
 * +-------------------------------------------------------------+
 * |100  |100|100|118|112|119|108|100|116|100|110|100|184|185|   |
 * +---------------------------------------------------------|   |
 * |      |100|10C|114|115|113|10A|100|100|11E|182|181|183|100   |
 * +-------------------------------------------------------------+
 * |        |100|11C|11A|111|11B|100|10B|11F|11D|180|    |100|1FE|
 * +-------------------------------------------------------------+
 * |1FB|   |100                                      |120|108|100|
 * +---+---+-----------------------------------------+---+---+---+
 *
 * TV:
 * +---+---+-------+-------+-------+-------+-------+---+---+-----+
 * |   |   |300    |301    |302    |303    |30F    |30A|304|31C  |
 * +-------------------------------------------------------------+
 * |   |310|311|312|313|314|315|316|317|318|319|31A|31B|   |     |
 * +-------------------------------------------------------------+
 * |     |   |   |   |   |   |   |   |   |   |   |   |   |   |   |
 * +---------------------------------------------------------|   |
 * |      |   |   |   |   |   |   |   |   |   |   |   |   |      |
 * +-------------------------------------------------------------+
 * |        |   |   |   |   |   |   |   |   |   |   |    |   |   |
 * +-------------------------------------------------------------+
 * |   |   |                                         |   |   |   |
 * +---+---+-----------------------------------------+---+---+---+
 *
 */

#define _S(ch) ((ch) | (1 << 8))
#define _C(ch) ((ch) | (1 << 9))
#define _G(ch) ((ch) | (1 << 10))
#define _TV(ch) ((ch) | (1 << 11))

static const uint16_t PROGMEM ascii_keys[0xB0] = {
    ['0'] = '0', [0xA6] = _S('0'),
    ['1'] = '1', ['!'] = _S('1'),
    ['2'] = '2', ['"'] = _S('2'),
    ['3'] = '3', ['#'] = _S('3'),
    ['4'] = '4', ['$'] = _S('4'),
    ['5'] = '5', ['%'] = _S('5'),
    ['6'] = '6', ['&'] = _S('6'),
    ['7'] = '7', ['\''] = _S('7'),
    ['8'] = '8', ['('] = _S('8'),
    ['9'] = '9', [')'] = _S('9'),
    ['a'] = 'a', ['A'] = _S('a'), [0x01] = _C('a'),
    ['b'] = 'b', ['B'] = _S('b'), [0x02] = _C('b'),
    ['c'] = 'c', ['C'] = _S('c'), [0x03] = _C('c'),
    ['d'] = 'd', ['D'] = _S('d'), [0x04] = _C('d'),
    ['e'] = 'e', ['E'] = _S('e'), [0x05] = _C('e'),
    ['f'] = 'f', ['F'] = _S('f'), [0x06] = _C('f'),
    ['g'] = 'g', ['G'] = _S('g'), [0x07] = _C('g'),
    ['h'] = 'h', ['H'] = _S('h'), [0x08] = _C('h'),
    ['i'] = 'i', ['I'] = _S('i'), // 09 is TAB
    ['j'] = 'j', ['J'] = _S('j'), [0x0A] = _C('j'),
    ['k'] = 'k', ['K'] = _S('k'), // 0B is HOME
    ['l'] = 'l', ['L'] = _S('l'), // 0C is CLR
    ['m'] = 'm', ['M'] = _S('m'), // 0D is RETURN
    ['n'] = 'n', ['N'] = _S('n'), [0x0E] = _C('n'),
    ['o'] = 'o', ['O'] = _S('o'), [0x0F] = _C('o'),
    ['p'] = 'p', ['P'] = _S('p'), [0x10] = _C('p'),
    ['q'] = 'q', ['Q'] = _S('q'), [0x11] = _C('q'),
    ['r'] = 'r', ['R'] = _S('r'), // 12 is INS
    ['s'] = 's', ['S'] = _S('s'), [0x13] = _C('s'),
    ['t'] = 't', ['T'] = _S('t'), [0x14] = _C('t'),
    ['u'] = 'u', ['U'] = _S('u'), [0x15] = _C('u'),
    ['v'] = 'v', ['V'] = _S('v'), [0x16] = _C('v'),
    ['w'] = 'w', ['W'] = _S('w'), [0x17] = _C('w'),
    ['x'] = 'x', ['X'] = _S('x'), [0x18] = _C('x'),
    ['y'] = 'y', ['Y'] = _S('y'), [0x19] = _C('y'),
    ['z'] = 'z', ['Z'] = _S('z'), [0x1A] = _C('z'),
    [' '] = ' ',
    [','] = ',', ['<'] = _S(','),
    ['-'] = '-', ['='] = _S('-'),
    ['.'] = '.', ['>'] = _S('.'),
    ['/'] = '/', ['?'] = _S('/'),
    ['@'] = '@',
    ['['] = '[', [0xA2] = _S('['),
    [']'] = ']', [0xA3] = _S(']'),
    ['^'] = '^',
    ['_'] = _S('_'),            // unshifted is DB (ろ)
    [0x5C] = 0x5C,              // YEN
    [':'] = ':', ['*'] = _S(':'),
    [';'] = ';', ['+'] = _S(';'),
    [0x09] = 0x09,              // TAB
    [0x0C] = 0x0C,              // CLR
    [0x0B] = _S(0x0C),          // HOME
    [0x0D] = 0x0D,              // RETURN
    [0x12] = 0x12,              // INS
    [0x1B] = 0x1B,              // ESC
    [0x1C] = 0x1C,              // RIGHT
    [0x1D] = 0x1D,              // LEFT
    [0x1E] = 0x1E,              // UP
    [0x1F] = 0x1F,              // DOWN
    [0x7F] = 0x7F,              // DEL
};

static const uint8_t PROGMEM graph_keys[0x88] = {
    [0x0F] = '0',
    [0x07] = '1',
    [0x01] = '2',
    [0x02] = '3',
    [0x03] = '4',
    [0x04] = '5',
    [0x05] = '6',
    [0x06] = '7',
    [0x0D] = '8',
    [0x0E] = '9',
    [0x1B] = 'b',
    [0x1A] = 'c',
    [0x14] = 'd',
    [0x18] = 'e',
    [0x15] = 'f',
    [0x13] = 'g',
    [0x0A] = 'h',
    [0x16] = 'i',
    [0x1E] = 'l',
    [0x0B] = 'm',
    [0x10] = 'p',
    [0x12] = 'r',
    [0x0C] = 's',
    [0x19] = 't',
    [0x11] = 'v',
    [0x1C] = 'x',
    [0x1F] = ',',
    [0x17] = '-',
    [0x1D] = '.',
    [0x80] = '/',
    [0x84] = '[',
    [0x85] = ']',
    [0x83] = '_',
    [0x09] = 0x5C,              // YEN
    [0x81] = ':',
    [0x82] = ';',
};

static const uint8_t PROGMEM tv_keys[0x20] = {
    [0x19] = '0',
    [0x10] = '1',
    [0x11] = '2',
    [0x12] = '3',
    [0x13] = '4',
    [0x14] = '5',
    [0x15] = '6',
    [0x16] = '7',
    [0x17] = '8',
    [0x18] = '9',
    [0x1A] = '-',
    [0x1B] = '^',
    [0x0A] = 0x0C,              // HOME
    [0x1C] = 0x7F,              // DEL
    [0x04] = 0x8E,              // PAGE
    [0x00] = 0x80,              // F1
    [0x01] = 0x81,              // F2
    [0x02] = 0x82,              // F3
    [0x03] = 0x83,              // F4
    [0x0F] = 0x84,              // F5
};

static uint16_t unascii(uint8_t control, uint8_t ch) {
    if (control == 0) {
        if (ch >= 0xB0) {
            // There are only a few of these.
            switch (ch) {
            case 0xDB:
                return 0x5F;    // _
            case 0xFE:
                return 0x7E;    // PAGE
            default:
                return 0;
            }
        }
        return pgm_read_word(ascii_keys + ch);
    } else if (control == 1) {
        if (ch >= 0x88) {
            switch (ch) {
            case 0xF0:          // F1-5
            case 0xF1:
            case 0xF2:
            case 0xF3:
            case 0xF4:
            case 0xFA:          // STOP
            case 0xFB:          // CAPS
            case 0xFD:          // MODE
            case 0xFE:          // KANA
                return ch - (0xF0 - 0x80);
            case 0xF5:          // shift F1-5
            case 0xF6:
            case 0xF7:
            case 0xF8:
            case 0xF9:
                return _S(ch - (0xF5 - 0x80));
            case 0xFC:
                return _S(0x7E); // shift PAGE
            default:
                return 0;
            }
        } else {
            uint8_t base = pgm_read_byte(graph_keys + ch);
            if (base != 0) {
                return _G(base);
            } else {
                return 0;
            }
        }
    } else if (control == 4 && ch == 0x08) {
        return 0x08;            // POWER
    } else if (control == 3) {
        if (ch < 0x20) {
            uint8_t base = pgm_read_byte(tv_keys + ch);
            if (base != 0) {
                return _TV(base);
            } else {
                return 0;
            }
        } else {
            return 0;
        }
    } else {
        return 0;
    }
}

typedef struct {
    unsigned from_source:1;
    unsigned error:1;
    union {
        uint32_t bits;
        struct {
            uint8_t state;
            uint16_t data;
        };
    };
} queue_entry_t;

#define QUEUE_SIZE 16
static queue_entry_t code_queue[QUEUE_SIZE];
static uint8_t code_queue_in, code_queue_out;

static inline void queue_clear(void) {
    code_queue_in = code_queue_out = 0;
}

static inline bool queue_is_empty(void) {
    return (code_queue_in == code_queue_out);
}

static inline bool queue_is_full(void) {
    // One entry wasted to be able to check this easily.
    return (((code_queue_in + 1) % QUEUE_SIZE) == code_queue_out);
}

static inline queue_entry_t queue_remove(void) {
    queue_entry_t entry = code_queue[code_queue_out];
    code_queue_out = (code_queue_out + 1) % QUEUE_SIZE;
    return entry;
}

static inline void queue_add(queue_entry_t entry) {
    code_queue[code_queue_in] = entry;
    code_queue_in = (code_queue_in + 1) % QUEUE_SIZE;
}

#define DATA_PIN PIND
#define DATA_PORT PORTD
#define DATA_MASK (1 << 0)
#define SENSE_MASK (1 << 1)
#define IR_MASK (1 << 2)

#define RECV_LED_PORT PORTC
#define RECV_LED_DDR DDRC
#define RECV_LED_MASK (1 << 7)

#define SENSE_LED_PORT PORTD
#define SENSE_LED_DDR DDRD
#define SENSE_LED_MASK (1 << 5)

typedef enum { IR, RJ }  source_t;

static inline source_t read_sense_source(void) {
    return ((DATA_PIN & SENSE_MASK) == 0) ? RJ : IR; // Pin is grounded on keyboard side.
}

static source_t sense_source;

static enum { INIT, ERROR, IDLE, HEADER_1, HEADER_2_INTERVAL, HEADER_2_PULSE, DATA_INTERVAL, DATA_PULSE } state;

static uint16_t last_time;
static uint32_t recv_bits;
static uint8_t recv_bit_count;

static void recv_error(uint16_t data, source_t from_source) {
    queue_entry_t error;
    error.from_source = from_source;
    error.error = true;
    error.state = state;
    error.data = data;
    if (!queue_is_full()) {
        queue_add(error);
    }
    state = ERROR;
}

static void recv_change(uint16_t now, bool data_state, source_t from_source) {
    if (state == INIT || state == ERROR || sense_source != from_source) {
        return;
    }
    
    if (state == IDLE) {
        if (data_state) {
            state = HEADER_1;
            last_time = now;
            RECV_LED_PORT |= RECV_LED_MASK;
        }
        return;
    }

    uint16_t width = now - last_time;
    last_time = now;

    if (state == HEADER_1) {
        if (data_state || width < 150 || width > 175) {
            recv_error(width, from_source);
            return;
        }
        state = HEADER_2_INTERVAL;
        return;
    }
    if (state == HEADER_2_INTERVAL) {
        if (!data_state || width < 20 || width > 35) {
            recv_error(width, from_source);
            return;
        }
        state = HEADER_2_PULSE;
        recv_bits = 0;
        recv_bit_count = 0;
        return;
    }
    if (state == HEADER_2_PULSE || state == DATA_PULSE) {
        // The last bit RJ pulse seems to be extra long.
        if (data_state || (from_source == RJ ? (width < 12 || width > (recv_bit_count == 24 ? 35 : 15)) : (width < 24 || width > 35))) {
            recv_error(width, from_source);
            return;
        }
        if (recv_bit_count < 24) {
            state = DATA_INTERVAL;
        } else {
            queue_entry_t entry;
            entry.from_source = from_source;
            entry.bits = recv_bits;
           if (!queue_is_full()) {
               queue_add(entry);
           }
           state = IDLE;
           RECV_LED_PORT &= ~RECV_LED_MASK;
        }
        return;
    }
    if (state == DATA_INTERVAL && data_state) {
        if (from_source == RJ) {
            if (width >= 8 && width <= 12) {
                recv_bit_count++;
                state = DATA_PULSE;
                return;
            } else if (width >= 28 && width <= 35) {
                recv_bits |= (1L << recv_bit_count);
                recv_bit_count++;
                state = DATA_PULSE;
                return;
            }
        } else {
            if (width >= 10 && width <= 20) {
                recv_bit_count++;
                state = DATA_PULSE;
                return;
            } else if (width >= 55 && width <= 65) {
                recv_bits |= (1L << recv_bit_count);
                recv_bit_count++;
                state = DATA_PULSE;
                return;
            }
        }
    }
    recv_error(width, from_source);    
}

// D0 is the data signal
ISR(INT0_vect) {
    recv_change(TCNT3, (DATA_PIN & DATA_MASK) == 0, RJ);
}

// D2 is the IR sensor
ISR(INT2_vect) {
    recv_change(TCNT3, (DATA_PIN & IR_MASK) == 0, IR);
}

#define INIT_DELAY_MS 100
static uint16_t init_time;

static matrix_row_t matrix[MATRIX_ROWS];

__attribute__ ((weak))
void matrix_init_kb(void) {
    matrix_init_user();
}

__attribute__ ((weak))
void matrix_scan_kb(void) {
    matrix_scan_user();
}

__attribute__ ((weak))
void matrix_init_user(void) {
}

__attribute__ ((weak))
void matrix_scan_user(void) {
}

void matrix_init(void) {
    DATA_PORT |= DATA_MASK | SENSE_MASK | IR_MASK; // Enable pullups.

    RECV_LED_DDR |= RECV_LED_MASK;
    SENSE_LED_DDR |= SENSE_LED_MASK;

#if F_CPU != 16000000
#error Wrong prescalar for clock rate
#endif

    // Configure TCNT3 to count once every 16us, which should be fast enough to distinguish the various pulses.
    TCCR3A = 0;                   // Normal
    TCCR3B = _BV(CS32);           // Prescalar = 256

    // Interrupts 0 and 2 on either edge.
    EICRA |= _BV(ISC00) | _BV(ISC20);

    state = INIT;
    init_time = timer_read();

    matrix_init_quantum();
}

static inline void key_state(uint8_t key, bool key_state) {
    uint8_t row = (key >> 4) & 0x0F;
    uint8_t col = key & 0x0F;
    if (key_state) {
        matrix[row] |= (1 << col);
    } else {
        matrix[row] &= ~(1 << col);
    }
}

uint8_t matrix_scan(void) {
    // It does not work to set shifts and action key at the same time and then clear them both on next scan.
    static uint8_t pending_key = 0;
    if (pending_key != 0) {
        key_state(pending_key, true);
        pending_key = 0;
    } else {
        // Only the seven game keys send key up. Clear all the rest.
        for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
            switch (row) {
            case 0:
            case 2:
                matrix[row] &= (1 << 0); // shift / space
                break;
            case 1:
                matrix[row] &= ((1 << 0xC) | (1 << 0xD) | (1 << 0xE) | (1 < 0xF)); // arrows
                break;
            case 8:
                matrix[row] &= (1 << 0xA); // STOP
            default:
                matrix[row] = 0;
                break;
            }
        }

        // Process key event from interrupt.
        if (!queue_is_empty()) {
            queue_entry_t entry = queue_remove();
            if (entry.error) {
                dprintf("%S ERR: %d %d\n", entry.from_source == IR ? PSTR("IR ") : PSTR("RJ "),
                        entry.state, entry.data);
            } else {
                uint16_t bits = entry.bits & 0x0FFF;
                uint16_t comp = ~(entry.bits >> 12) & 0x0FFF;
                if (bits != comp) {
                    dprintf("%S complemented copy compare failed: %03X\n", entry.from_source == IR ? PSTR("IR ") : PSTR("RJ "),
                            entry.bits);
                } else {
                    uint8_t parity = 0;
                    for (uint8_t i = 0; i < 12; i++) {
                        if ((bits & (1 << i)) != 0) {
                            parity ^= 1;
                        }
                    }
                    if (parity != 0) {
                        dprintf("%S parity error: %02X\n", entry.from_source == IR ? PSTR("IR ") : PSTR("RJ "),
                                bits);
                    } else {
                        uint8_t control = bits & 7;
                        uint8_t ch = bits >> 3;
                        if (control == 2) {
                            dprintf("%S game %02X\n", entry.from_source == IR ? PSTR("IR ") : PSTR("RJ "), ch);
                            key_state(0x00, (ch & 0x01) != 0);
                            key_state(0x8A, (ch & 0x02) != 0);
                            key_state(0x1E, (ch & 0x04) != 0);
                            key_state(0x1F, (ch & 0x08) != 0);
                            key_state(0x1C, (ch & 0x10) != 0);
                            key_state(0x1D, (ch & 0x20) != 0);
                            key_state(0x20, (ch & 0x80) != 0);
                        } else {
                            uint16_t code = unascii(control, ch);
                            if (code == 0) {
                                dprintf("%S %d %02X UNMAPPED\n", entry.from_source == IR ? PSTR("IR ") : PSTR("RJ "),
                                        control, ch);
                            } else {
                                uint8_t shifts = code >> 8;
                                uint8_t key = code & 0xFF;
                                dprintf("%S %d %02X %X:%02X\n", entry.from_source == IR ? PSTR("IR ") : PSTR("RJ "),
                                        control, ch, shifts, key);
                                if (shifts != 0) {
                                    matrix[0] |= shifts;
                                    pending_key = key;
                                } else {
                                    key_state(key, true);
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    if (state == ERROR) {
        state = INIT;
        init_time = timer_read();
        RECV_LED_PORT &= ~RECV_LED_MASK;        
    } else if (state == INIT) {
        if (timer_read() - init_time > INIT_DELAY_MS) {
            sense_source = read_sense_source();
            // Enable appropriate interrupt and light LED if plugged in.
            // Note that the A-Star green LED is active low, while the yellow is active high.
            if (sense_source == RJ) {
                EIMSK |= _BV(INT0);
                SENSE_LED_PORT &= ~SENSE_LED_MASK;
            } else {
                EIMSK |= _BV(INT2);
                SENSE_LED_PORT |= SENSE_LED_MASK;
            }
            state = IDLE;

            for (uint8_t row = 0; row < MATRIX_ROWS; row++) matrix[row] = 0;
            pending_key = 0;
        }
    } else if (sense_source != read_sense_source()) {
        state = INIT;
        init_time = timer_read();
        EIMSK &= ~(_BV(INT0) | _BV(INT2)); // Disable interrupts until settled.
    }

    matrix_scan_quantum();
    return 1;
}

void matrix_print(void) {
    print("\nr/c 0123456789ABCDEF\n");
    for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
        print_hex8(row); print(": ");
        print_bin_reverse16(matrix_get_row(row));
        print("\n");
    }
}

inline
matrix_row_t matrix_get_row(uint8_t row) {
    return matrix[row];
}
