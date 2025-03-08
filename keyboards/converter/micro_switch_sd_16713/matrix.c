
#include <avr/io.h>
#include "debug.h"
#include "matrix.h"
#include "print.h"
#include "timer.h"
#include "wait.h"

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

#define CONTROL_DDR DDRD
#define CONTROL_PIN PIND
#define CONTROL_PORT PORTD
#define ACK_MASK ((1 << 0) | (1 << 2))
#define RESET_MASK (1 << 1)
#define AVAIL_MASK (1 << 3)
#define CLICK_MASK (1 << 4)
#define CHAR_PORT PORTB
#define CHAR_PIN PINB

void matrix_init(void) {
    for (uint8_t i = 0; i < MATRIX_ROWS; i++) {
        matrix[i] = 0x0000;
    }

    CONTROL_DDR = ACK_MASK | RESET_MASK;
    CONTROL_PORT = AVAIL_MASK;
    CHAR_PORT = 0xFF;

    CONTROL_PORT |= RESET_MASK;
    wait_us(5);
    CONTROL_PORT &= ~RESET_MASK;

    CONTROL_PORT |= ACK_MASK;

    matrix_init_kb();
}

uint8_t matrix_scan(void) {
    // There are no up transitions; clear initially.
    for (uint8_t i = 0; i < MATRIX_ROWS; i++) {
        if (i == 4) {
            matrix[i] &= 0xF000; // Keep 4 shift chars that send break.
        } else {
            matrix[i] = 0x0000;
        }
    }
    
    if ((CONTROL_PIN & AVAIL_MASK) == 0) {
        uint8_t code = PINB;

        PORTD &= ~0x05;
        wait_us(1);
        PORTD |= 0x05;
        
        dprintf("%02X\n", code);

        uint8_t row = (code >> 4) & 0x07;
        uint8_t col = code & 0x0F;
        if ((code & 0x80) != 0) {
            matrix[row] &= ~(1 << col);
        } else {
            matrix[row] |= (1 << col);
        }
    }
    
    matrix_scan_kb();
    return 1;
}
