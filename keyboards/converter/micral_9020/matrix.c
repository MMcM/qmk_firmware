
#include "debug.h"
#include "matrix.h"
#include "print.h"
#include "quantum.h"

#include <avr/io.h>
#include "uart.h"

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

inline
matrix_row_t matrix_get_row(uint8_t row) {
    return matrix[row];
}

void matrix_print(void) {
    print("\nr/c 0123456789ABCDEF\n");
    for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
        print_hex8(row); print(": ");
        print_bin_reverse16(matrix_get_row(row));
        print("\n");
    }
}

void matrix_init(void) {
    for (uint8_t i = 0; i < MATRIX_ROWS; i++) matrix[i] = 0x00;

    uart_init(600);

    matrix_init_kb();
}

uint8_t matrix_scan(void) {
    // There are only break codes for high codes, so must clear everything else.
    for (uint8_t i = 0; i < 8; i++) {
        matrix[i] = 0x00;
    }

    if (!uart_available()) {
        return 0;
    }

    uint8_t code = uart_read();
    dprintf("R: %02X\n", code);

    uint8_t row = code >> 4;
    uint8_t col = code & 0x0F;
    if ((row >= 8) && ((col & 1) != 0)) {
        // Key up.
        matrix[row] &= ~(1 << (col - 1));
    } else {
        // Key down.
        matrix[row] |= (1 << col);
    }

    matrix_scan_kb();
    return 1;
}
