
#include "debug.h"
#include "matrix.h"
#include "print.h"
#include "quantum.h"
#include "z29_state.h"

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

#define RESET_DDR DDRD
#define RESET_PIN PIND
#define RESET_PORT PORTD
#define RESET_MASK (1 << 1)

// Note that the schematic shows inverters on both kbd lines, so the logic here is inverted relative to the actual terminal.

#define KBD_IN_DDR DDRD
#define KBD_IN_PIN PIND
#define KBD_IN_PORT PORTD
#define KBD_IN_MASK (1 << 2)

#define KBD_OUT_DDR DDRD
#define KBD_OUT_PORT PORTD
#define KBD_OUT_MASK (1 << 3)

#define MATRIX_SHIFT (1 << 2)
#define MATRIX_CTRL (1 << 1)

#define KB_SHFT 0x40
#define KB_CNTR 0x20

#define KB_UP 0x80
#define KB_DOWN 0x81
#define KB_LEFT 0x82
#define KB_RIGHT 0x83
#define KB_HOME 0x84
#define KB_ERASE 0x85
#define KB_HELP 0x86
#define KB_SCROLL 0x87
#define KB_SETUP 0x88
#define KB_BREAK 0x89
#define KB_CAPS 0x8A
#define KB_TAB 0x8B
#define KB_SPACE 0x8C

#define KB_POWER 0x8F

#define KB_0 0x90
#define KB_1 0x91
#define KB_2 0x92
#define KB_3 0x93
#define KB_4 0x94
#define KB_5 0x95
#define KB_6 0x96
#define KB_7 0x97
#define KB_8 0x98
#define KB_9 0x99
#define KB_DEC 0x9A
#define KB_ENT 0x9B
#define KB_DASH 0x9C
#define KB_COMMA 0x9D

#define KB_ACC 0x9F

#define KB_F1 0x80
#define KB_F2 0x81
#define KB_F3 0x82
#define KB_F4 0x83
#define KB_F5 0x84
#define KB_F6 0x85
#define KB_F7 0x86
#define KB_F8 0x87
#define KB_F9 0x88

#define KB_ID 0x98

#define KBC_ID 0x80
#define KBC_BELL 0x81
#define KBC_EC 0x82
#define KBC_DC 0x83
#define KBC_EL 0x84
#define KBC_XL 0x85
#define KBC_ER 0x86
#define KBC_DR 0x87
#define KBC_DK 0x88
#define KBC_EK 0x89
#define KBC_OFFLN 0x8A
#define KBC_ONLN 0x8B

void matrix_init(void) {
    for (uint8_t i = 0; i < MATRIX_ROWS; i++) matrix[i] = 0;

    KBD_IN_DDR &= ~KBD_IN_MASK;
    KBD_IN_PORT |= KBD_IN_MASK;
    KBD_OUT_DDR |= KBD_OUT_MASK;
    KBD_OUT_PORT &= ~KBD_OUT_MASK;
    RESET_DDR &= ~RESET_MASK;
    RESET_PORT |= RESET_MASK;

    matrix_init_quantum();
}

static const uint8_t PROGMEM shifted[][2] = {
   { '\'', '"' },
   { ',', '<' },
   { '-', '_' },
   { '.', '>' },
   { '/', '?' },
   { '0', ')' },
   { '1', '!' },
   { '2', '@' },
   { '3', '#' },
   { '4', '$' },
   { '5', '%' },
   { '6', '^' },
   { '7', '&' },
   { '8', '*' },
   { '9', '(' },
   { ';', ':' },
   { '=', '+' },
   { '[', '{' },
   { ']', '}' },
   { '\\', '|' },
   { '`', '~' },
};

static inline uint8_t unshift_code(uint8_t code) {
    for (uint8_t i = 0; i < sizeof(shifted)/sizeof(shifted[0]); i++) {
        const uint8_t *p_shifted = shifted[i];
        if (code == pgm_read_byte(p_shifted + 1)) {
            return pgm_read_byte(p_shifted + 0);
        }
    }
    return code;
}

// ASCII control characters that correspond to keys and so are not mapped back to Ctrl + character.
static const uint8_t PROGMEM control_keys[] = {
    0x08, 0x0D, 0x0A, 0x1B  
};

static inline uint8_t unctrl_code(uint8_t code) {
    for (uint8_t i = 0; i < sizeof(control_keys)/sizeof(control_keys[0]); i++) {
        if (code == pgm_read_byte(control_keys + i)) {
            return code;
        }
    }
    return 0x40 + code;
}

static uint8_t get_command(z29_state_t* states) {
    // One-shot commands.
    if (states[0].id) {
        states[0].id = states[1].id = false;
        return KBC_ID;
    }
    if (states[0].bell) {
        states[0].bell = states[1].bell = false;
        return KBC_BELL;
    }
    // Actual states.
    if (states[0].click != states[1].click) {
        states[1].click = states[0].click;
        return states[0].click ? KBC_EC : KBC_DC;
    }
    if (states[0].caps != states[1].caps) {
        states[1].caps = states[0].caps;
        return states[0].caps ? KBC_EL : KBC_XL;
    }
    if (states[0].repeat != states[1].repeat) {
        states[1].repeat = states[0].repeat;
        return states[0].repeat ? KBC_ER : KBC_DR;
    }
    if (states[0].disable != states[1].disable) {
        states[1].disable = states[0].disable;
        return states[0].disable ? KBC_DK : KBC_EK;
    }
    if (states[0].offline != states[1].offline) {
        states[1].offline = states[0].offline;
        return states[0].offline ? KBC_OFFLN : KBC_ONLN;
    }
    states[1].raw = states[0].raw;
    return 0;
}

// Target state.
z29_state_t z29_state = {
    .click = true,
    .repeat = true
};

// Current state. (Initially: power-on state.)
static z29_state_t current_z29_state = {
    .click = true,
    .repeat = true
};

static inline void key_down(uint8_t code) {
    uint8_t col = code & 0x0F;
    uint8_t row = (code >> 4) & 0x0F;
    matrix[row] |= (1 << col);
}

uint8_t matrix_scan(void) {
    debug_enable = true;          // Not enough shifts for command key.

    static enum { UNKNOWN, RESET, AWAIT_POWER_ON, NORMAL, ACCESS, SHIFT, SHIFTED, ALL_UP } state = UNKNOWN;
    static uint8_t shifted_code;
    if ((RESET_PIN & RESET_MASK) == 0) {
        if (state != RESET) {
#if 1
            if (state != UNKNOWN) {
                // If RESET is asserted other than at program start, jump to bootloader.
                // Useful when developing on a board like Pro Micro without a Reset switch.
                reset_keyboard();
            }
#endif
            dprintln("RESET");
            state = RESET;
        }
        return 0;
    } else if (state == RESET) {
        state = AWAIT_POWER_ON;
    } else if (state == UNKNOWN) {
        state = NORMAL;
    } else if (state == ALL_UP) {
        // There are no up transitions, so clear everything between codes.
        for (uint8_t i = 0; i < MATRIX_ROWS; i++) matrix[i] = 0;
        state = NORMAL;
    } else if (state == SHIFT) {
        matrix[0] |= MATRIX_SHIFT;
        state = SHIFTED;
    } else if (state == SHIFTED) {
        key_down(shifted_code);
        state = ALL_UP;
    }

    do {
        if ((KBD_IN_PIN & KBD_IN_MASK) == 0) {
            // Keyboard data available.
            uint8_t data = 0;
            uint8_t shift = 0;
            do {
                KBD_OUT_PORT |= KBD_OUT_MASK;
                wait_us(200);
                if ((KBD_IN_PIN & KBD_IN_MASK) == 0) {
                    data |= (1 << shift);
                }
                KBD_OUT_PORT &= ~KBD_OUT_MASK;
                wait_us(100);
            } while (++shift < 8);
            if (data == KB_POWER) {
                if (state == AWAIT_POWER_ON) {
                    dprintln("ON");
                    state = NORMAL;
                }
                break;
            }
            dprintf("Recv %02X\n", data);
            if ((data & 0x80) == 0) {
                if (state == ACCESS) {
                    state = NORMAL;
                }
                if (data < 0x20) {
                    uint8_t unctrl = unctrl_code(data);
                    if (data != unctrl) {
                        matrix[0] |= MATRIX_CTRL;
                        data = unctrl;
                    }
                } else if (data >= 'a' && data <= 'z') {
                    data &= 0x5F;
                } else if (data >= 'A' && data <= 'Z') {
                    if (!current_z29_state.caps) {
                        // QMK shift would toggle caps lock.
                        matrix[0] |= MATRIX_SHIFT;
                    }
                } else {
                    uint8_t unshift = unshift_code(data);
                    if (data != unshift) {
                        matrix[0] |= MATRIX_SHIFT;
                        data = unshift;
                    }
                }
            } else {
                if ((data & KB_SHFT) != 0) {
                    matrix[0] |= MATRIX_SHIFT;
                    data &= ~KB_SHFT;
                }
                if ((data & KB_CNTR) != 0) {
                    matrix[0] |= MATRIX_CTRL;
                    data &= ~KB_CNTR;
                }
                if (state == ACCESS) {
                    if ((data & 0xF8) == KB_ID) {
                        break;              // Already dprint'ed, so not much more to do.
                    }
                    data |= 0x20;
                    state = NORMAL;
                } else if (data == KB_ACC) {
                    state = ACCESS;
                    break;
                }
            }
            if (matrix[0] != 0) {
                shifted_code = data;
                if ((matrix[0] & (MATRIX_SHIFT | MATRIX_SHIFT)) == (MATRIX_SHIFT | MATRIX_SHIFT)) {
                    // Both CTRL and SHIFT: do one at a time.
                    matrix[0] &= ~MATRIX_SHIFT;
                    state = SHIFT;
                } else {
                    state = SHIFTED;
                }
            } else {
                key_down(data);
                state = ALL_UP;
            }
        } else if (current_z29_state.raw != z29_state.raw) {
            // Command pending.
            z29_state_t updated_states[2];
            updated_states[0] = z29_state;
            updated_states[1] = current_z29_state;
            uint8_t command = get_command(updated_states);
            if (command != 0) {
                KBD_OUT_PORT |= KBD_OUT_MASK;
                if ((KBD_IN_PIN & KBD_IN_MASK) == 0) {
                    // In request seen right away, there is contention.
                    KBD_OUT_PORT &= ~KBD_OUT_MASK;
                    break;
                }
                dprintf("Send %02X\n", command);
                for (uint8_t shift = 0; shift < 8; shift++) {
                    while ((KBD_IN_PIN & KBD_IN_MASK) != 0) {
                        wait_us(500);
                    }
                    if ((command & (1 << shift)) != 0) {
                        KBD_OUT_PORT &= ~KBD_OUT_MASK;
                    } else {
                        KBD_OUT_PORT |= KBD_OUT_MASK;
                    }
                    // Timing here is delicate: we can't just loop back using the previous enable but not miss this transition.
                    // For this reason, SOF interrupts must be disabled.
                    while ((KBD_IN_PIN & KBD_IN_MASK) == 0) {
                    }
                }
                KBD_OUT_PORT &= ~KBD_OUT_MASK;
            }
            z29_state = updated_states[0];
            current_z29_state = updated_states[1];
        }
    } while (false);  

    matrix_scan_quantum();
    return 1;
}

void matrix_print(void) {
    print("\nr/c 012345678ABCDEF\n");
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
