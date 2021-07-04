
#include "debug.h"
#include "matrix.h"
#include "print.h"
#include "quantum.h"

#include <avr/io.h>

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

#define DATA_PIN PIND
#define DATA_PORT PORTD
#define IR_MASK (1 << 0)
#define DATA_MASK (1 << 2)

#define LED_DDR DDRD
#define LED_PORT PORTD
#define LED_MASK (1 << 6)

typedef struct {
    unsigned frame_error:1;
    unsigned start_bit:1;
    unsigned parity_bit:1;
    unsigned code:8;
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

static inline void queue_frame_error(void) {
    queue_entry_t error;
    error.frame_error = 1;
    if (!queue_is_full()) {
        queue_add(error);
    }
}

static uint16_t timer_high = 0;

static inline uint32_t read_timer(void) {
    return ((uint32_t)timer_high << 16) | (uint32_t)TCNT3;
}

SIGNAL(TIMER3_OVF_vect) {
    timer_high++;
}

// D0 is the IR detector
ISR(INT0_vect) {
    static uint32_t last_transition = 0;
    static uint16_t bits;
    static uint8_t bit_position;

    uint8_t ir_pin = DATA_PIN & IR_MASK;
    uint32_t now = read_timer();
    if (ir_pin == 0) {
        // Falling edge of IR pulse.
        if (last_transition != 0) {
            uint32_t width = now - last_transition;
            if (width < 10 || width > 100) {
                queue_frame_error();
                last_transition = 0;
            } else {
                last_transition = now;
            }
        }
        return;
    }
    uint32_t width = now - last_transition;
    if (last_transition == 0 || width > 250) {
        // Rising edge of start bit.
        bits = 1;
        bit_position = 1;
        last_transition = now;
        return;
    }
    uint8_t last_bit = (bits >> (bit_position - 1)) & 1;
    if (width < 40) {
        // A short interval is 0 followed by 1.
        if (last_bit == 0) {
            bits |= (1 << bit_position);
            bit_position++;
        } else {
            queue_frame_error();
            last_transition = 0;
        }
    } else if (width > 125) {
        // A long interval is 1 followed by 0.
        if (last_bit == 1) {
            bit_position++;
        } else {
            queue_frame_error();
            last_transition = 0;
        }
    } else {
        // A medium interval is two adjacent alike bits.
        bits |= (last_bit << bit_position);
        bit_position++;
    }
    if (bit_position >= 10) {
        queue_entry_t entry;
        entry.frame_error = 0;
        entry.start_bit = bits;
        entry.code = bits >> 1;
        entry.parity_bit = bits >> 9;
        if (!queue_is_full()) {
            queue_add(entry);
        }
        last_transition = 0;
    } else {
        last_transition = now;
    }
}

// D2 is the /DATA line
ISR(INT2_vect) {
    static uint32_t last_transition = 0;
    static uint16_t bits;
    static uint8_t half_bit_position;

    uint8_t data_pin = DATA_PIN & DATA_MASK;
    uint32_t now = read_timer();

    if (last_transition == 0) {
        if (data_pin == 0) {
            bits = 0;
            half_bit_position = 0;
            last_transition = now;
        }
        return;
    }
    
    uint32_t width = now - last_transition;
    bool two_wide;
    if (width > 50 && width < 60) {
        two_wide = false;
    } else if (width > 100 && width < 120) {
        two_wide = true;
    } else {
        queue_frame_error();
        last_transition = 0;
        return;
    }
    if (two_wide) {
        if (half_bit_position % 2 == 0) {
            queue_frame_error();
            last_transition = 0;
            return;
        }
        half_bit_position += 2;
        if (data_pin != 0) {
            bits |= (1 << (half_bit_position / 2));
        }
    } else {
        if (half_bit_position++ % 2 == 0) {
            if (data_pin != 0) {
                bits |= (1 << (half_bit_position / 2));
            }
        }
    }
    if (data_pin != 0 && half_bit_position >= 19) {
        queue_entry_t entry;
        entry.frame_error = 0;
        entry.start_bit = bits;
        entry.code = bits >> 1;
        entry.parity_bit = bits >> 9;
        if (!queue_is_full()) {
            queue_add(entry);
        }
        last_transition = 0;
    } else {
        last_transition = now;
    }
}

void matrix_init(void) {
    for (uint8_t i = 0; i < MATRIX_ROWS; i++) matrix[i] = 0x00;

#if F_CPU != 16000000
#error Wrong prescalar for clock rate
#endif

    // Configure TCNT3 to count once every 4us, making the nominal half-bit width of 220us 55 ticks.
    TCCR3A = 0;                     // Normal
    TCCR3B = _BV(CS31) | _BV(CS30); // Prescalar = 64
    TIMSK3 |= _BV(TOIE3);           // Enable overflow interrupt

    DATA_PORT |= DATA_MASK;     // Pullup on DATA line

    // Interrupts 0 (IR) and 2 (DATA) on either edge.
    EIMSK |= (1 << INT0) | (1 << INT2);
    EICRA |= (1 << ISC00) | (1 << ISC20);

    LED_DDR |= LED_MASK;        // LED for error indicator

    matrix_init_quantum();
}

uint8_t matrix_scan(void) {
    while (!queue_is_empty()) {
        queue_entry_t entry = queue_remove();
        if (entry.frame_error || entry.start_bit != 1) {
            dprintf("Frame error\n");
            LED_PORT |= LED_MASK;
            for (uint8_t i = 0; i < MATRIX_ROWS; i++) matrix[i] = 0x00; // Don't let keys get stuck down.
            break;
        }
        uint8_t parity = entry.parity_bit;
        for (uint8_t i = 0; i < 8; i++) {
            if ((entry.code & (1 << i)) != 0) {
                parity ^= 1;
            }
        }
        if (parity == 0) {
            dprintf("Parity error\n");
            LED_PORT |= LED_MASK;
            for (uint8_t i = 0; i < MATRIX_ROWS; i++) matrix[i] = 0x00;
            break;
        }
        dprintf("%02X\n", entry.code);
        LED_PORT &= ~LED_MASK;
        uint8_t row = (entry.code >> 4) & 0x07;
        uint8_t col = entry.code & 0x0F;
        if (entry.code & 0x80) {
            // Key up.
            matrix[row] &= ~(1 << col);
        } else {
            // Key down.
            matrix[row] |= (1 << col);
        }
        break;
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
