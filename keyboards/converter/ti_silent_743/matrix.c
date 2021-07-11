
#include <avr/io.h>
#include "matrix.h"
#include "print.h"
#include "quantum.h"
#include "timer.h"

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

    PORTB = 0xFF;               // Enable pullups.

    DDRD = 0xFF;                // Built-in LED and row selectors.
    PORTD |= 0xBF;

    DDRC |= (1 << 7);           // Carrier detect LED.

    PORTF = 0xFF;               // Direct switches.
    
    matrix_init_quantum();
}

uint8_t matrix_scan(void) {
    static uint8_t row = 0;

    if (row < MATRIX_ROWS - 1) {
        uint8_t mask = (row == 6) ? (1 << 7) : (1 << row);
        PORTD &= ~mask;
        wait_us(15);
        matrix[row] = ~PINB;
        PORTD |= mask;
        row++;
    } else {
        matrix[row] = ~PINF;
        row = 0;
    }

    matrix_scan_quantum();
    return 1;
}

void matrix_print(void) {
    print("\nr/c 012345678\n");
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
