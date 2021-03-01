
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

#define DATA_DDR DDRB
#define DATA_PIN PINB
#define DATA_PORT PORTB

#define CONTROL_DDR DDRD
#define CONTROL_PIN PIND
#define CONTROL_PORT PORTD

void matrix_init(void) {
    for (uint8_t i = 0; i < MATRIX_ROWS; i++) matrix[i] = 0;
  
    DATA_DDR = 0x00;
    DATA_PORT = 0x7F;

    CONTROL_DDR &= ~0x03;
    CONTROL_DDR |= 0x0C;
    CONTROL_PORT |= 0x0B;

    matrix_init_quantum();
}

typedef union {
    uint8_t as_byte;
    struct {
        unsigned key_up:1;
        unsigned code:7;
    };
} key_state_t;

uint8_t matrix_scan(void) {
    static key_state_t last_key_state = { .key_up = 1 };
    key_state_t key_state = { .key_up = PIND, .code = PINB };
    if (last_key_state.as_byte != key_state.as_byte) {
        uint8_t col = key_state.code & 0x0F;
        uint8_t row = (key_state.code >> 4) & 0x07;
        if (key_state.key_up) {
            matrix[row] &= ~(1 << col);
        } else {
            matrix[row] |= (1 << col);
        }
        last_key_state.as_byte = key_state.as_byte;
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
