
#include <avr/io.h>
#include "debug.h"
#include "matrix.h"
#include "protocol/serial.h"
#include "print.h"

#define AC_DDR DDRB
#define AC_PORT PORTB

#define KEY_UP_DDR DDRB
#define KEY_UP_PORT PORTB
#define KEY_UP_PIN PINB
#define KEY_UP_MASK (1 << 7)

#define SINGLE_KEYS_DDR DDRC
#define SINGLE_KEYS_PIN PINC
#define SINGLE_KEYS_PORT PORTC
#define BREAK_KEY_MASK (1 << 7)
#define CTRL_KEY_MASK (1 << 6)

#define BREAK_KEY_CODE 000

#ifdef VT50H
#define AC_MASK 0177
#define SINGLE_KEYS_MASK BREAK_KEY_MASK
#define MIN_KEY_CODE 1
#define MAX_KEY_CODE 0117
#else
#define AC_MASK 077
#define SINGLE_KEYS_MASK (BREAK_KEY_MASK|CTRL_KEY_MASK)
#define CTRL_KEY_CODE 070
#define MIN_KEY_CODE 0
#define MAX_KEY_CODE 070
#endif

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
    for (uint8_t i = 0; i < MATRIX_ROWS; i++) matrix[i] = 0x00;

    AC_DDR |= AC_MASK;
    KEY_UP_DDR &= ~KEY_UP_MASK;
    KEY_UP_PORT |= KEY_UP_MASK;
    SINGLE_KEYS_DDR &= ~SINGLE_KEYS_MASK;
    SINGLE_KEYS_PORT |= SINGLE_KEYS_MASK;

    matrix_init_quantum();
}

uint8_t matrix_scan(void) {
    static uint8_t key_code = MIN_KEY_CODE;

    uint8_t state;
#ifdef BREAK_KEY_CODE
    if (key_code == BREAK_KEY_CODE) {
        state = SINGLE_KEYS_PIN & BREAK_KEY_MASK;
    } else
#endif
#ifdef CTRL_KEY_CODE
        if (key_code == CTRL_KEY_CODE) {
            state = SINGLE_KEYS_PIN & CTRL_KEY_MASK;
        } else
#endif
            // Note: the VT61 has an ACT signal that needs to be taken low after loading AC.
            // It also has CAPS LOCK as a single key pin.
            // It uses a 16-wire connection, so these new signals would need to be wired someplace.
            {
                AC_PORT = (AC_PORT & ~AC_MASK) | (key_code & AC_MASK);
                state = KEY_UP_PIN & KEY_UP_MASK;
            }

    uint8_t row = key_code >> 3;
    uint8_t col = key_code & 07;
    if (state == 0) {
        matrix[row] |= (1 << col);
    } else {
        matrix[row] &= ~(1 << col);
    }

    key_code++;
    if (key_code > MAX_KEY_CODE) {
        key_code = MIN_KEY_CODE;
    }

    matrix_scan_quantum();
    return 1;
}

void matrix_print(void) {
    print("\nr/c  01234567\n");
    for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
        xprintf("%02o: ", row);
        print_bin_reverse8(matrix_get_row(row));
        print("\n");
    }
}

inline
matrix_row_t matrix_get_row(uint8_t row) {
    return matrix[row];
}
