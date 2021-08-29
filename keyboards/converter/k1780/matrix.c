
#include <avr/io.h>
#include "debug.h"
#include "matrix.h"
#include "protocol/serial.h"
#include "print.h"

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

    SERIAL_UART_INIT();

    matrix_init_quantum();
}

uint8_t matrix_scan(void) {
    // No up transitions, so clear all but shifts.
    for (uint8_t i = 0; i < MATRIX_ROWS - 1; i++) matrix[i] = 0x00;

    if (!SERIAL_UART_RXD_PRESENT) {
        return 0;
    }

    uint8_t data = SERIAL_UART_DATA;
    if (data == 0xFF) {
        if (SERIAL_UART_TXD_READY) {
            // TODO: Not sure what the other possibilities are.
            SERIAL_UART_DATA = 0x00;
        }
        return 0;
    }

    if (data & 0x80) {
        // Update shifts for next key(s).
        matrix[MATRIX_ROWS - 1] = data & 0x07;
    } else {
        uint8_t col, row;
        col = data & 0x07;
        row = (data >> 3) & 0x0F;
        matrix[row] |=  (1 << col);
    }

    matrix_scan_quantum();
    return 1;
}

void matrix_print(void) {
    print("\nr/c 01234567\n");
    for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
        print_hex8(row); print(": ");
        print_bin_reverse8(matrix_get_row(row));
        print("\n");
    }
}

inline
matrix_row_t matrix_get_row(uint8_t row) {
    return matrix[row];
}
