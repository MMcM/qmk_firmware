
#include "debug.h"
#include "matrix.h"
#include "print.h"
#include "quantum.h"

#include <avr/io.h>
#include "protocol/serial.h"

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

#define POWER_DDR DDRD
#define POWER_MASK (1 << 3)
#define POWER_PORT PORTD

void matrix_init(void) {
    for (uint8_t i = 0; i < MATRIX_ROWS; i++) matrix[i] = 0;

    // Always powered.
    POWER_DDR |= POWER_MASK;
    POWER_PORT &= ~POWER_MASK;

    serial_init();

    matrix_init_quantum();
}

uint8_t matrix_scan(void) {
    int16_t data = serial_recv2();
    if (data < 0) {
        return 0;
    }
  
    uint8_t code  = data & 0xFF;
    uint8_t col = code & 0x0F;
    uint8_t row = (code >> 4) & 0x0D;
    if ((code & 0x20) == 0) {
        matrix[row] |= (1 << col);
    } else {
        matrix[row] &= ~(1 << col);
    }

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
