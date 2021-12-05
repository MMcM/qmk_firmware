
#include <avr/io.h>
#include <avr/interrupt.h>
#include "debug.h"
#include "matrix.h"
#include "print.h"
#include "timer.h"
#include "../xt_usb/xt.h"

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

    xt_host_init();

    matrix_init_quantum();
}

uint8_t matrix_scan(void) {
    debug_enable = true;

    uint8_t code = xt_host_recv();
    if (code == 0) {
        return 0;
    }

    dprintf("%02X\n", code);

    uint8_t col = code & 0x0F;
    uint8_t row = (code >> 4) & 0x07;
    if ((code & 0x80) != 0) {
        matrix[row] &= ~(1 << col);
    } else {
        matrix[row] |= (1 << col);
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
