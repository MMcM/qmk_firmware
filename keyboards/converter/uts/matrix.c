
#include "debug.h"
#include "matrix.h"
#include "print.h"
#include "quantum.h"

#include <avr/io.h>
#include "protocol/serial.h"
#define SERIAL_UART_TXD_READY (UCSR1A & _BV(UDRE1))

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
    for (uint8_t i = 0; i < MATRIX_ROWS; i++) matrix[i] = 0;

    serial_init();

    matrix_init_quantum();
}

uint8_t matrix_scan(void) {
    static uint8_t prefix = 0;
    static enum { IDLE, PREFIX, HELD, ALL_UP } state = IDLE;

    if (state == ALL_UP) {
        // There are no up transitions, so clear everything between codes.
        for (uint8_t i = 0; i < MATRIX_ROWS - 1; i++) matrix[i] = 0;
        state = IDLE;
    }

    if (SERIAL_UART_TXD_READY) {
        serial_send(0);
    }

    int16_t data2 = serial_recv2();
    if (data2 >= 0) {
        uint8_t data = data2 & 0xFF;
        if (data & 0x80) {
            prefix = data;
            matrix[8] = data & 5; // Update shift state (FCTN and SHIFT -- the 2 bit might be CAPS, but LOCK is SHIFT LOCK).
            if (state == HELD) {
                // Only get enough information to keep one character down.
                for (uint8_t i = 0; i < MATRIX_ROWS - 1; i++) matrix[i] = 0;
            }
            state = PREFIX;
        } else if (state == PREFIX) {
            // B0 00 indicates release of held state; there is no scan code 00 otherwise.
            // This is usually sent when A8 was sent, but also for the arrow keys, as though they had a faster auto-repeat threshold.
            if (data) {
                uint8_t col = data & 0x0F;
                uint8_t row = (data >> 4) & 0x07;
                matrix[row] |= (1 << col);
            }
            if (prefix & 0x08) {
                state = HELD;
            } else {
                state = ALL_UP;
            }
        }
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
