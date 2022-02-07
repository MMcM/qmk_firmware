
#include "debug.h"
#include "matrix.h"
#include "quantum.h"

#define ROW_PORT PORTD
#define ROW_DDR DDRD
#define ROW_MASK 0x0F
#define COL_PORT PORTB
#define COL_PIN PINB

void matrix_init_custom(void) {
    ROW_DDR |= ROW_MASK;
    COL_PORT = 0xFF;
}

bool matrix_scan_custom(matrix_row_t current_matrix[]) {
    static uint8_t row = 0;

    ROW_PORT = (ROW_PORT & ~ROW_MASK) | (row & ROW_MASK);
    wait_us(20);                // Wait for pull-ups to stabilize

    uint8_t cols = ~COL_PIN;
    bool changed = current_matrix[row] != cols;
    if (changed) {
        current_matrix[row] = cols;
    }

    row = (row + 1) & ROW_MASK;

    return changed;
}
