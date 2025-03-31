
#include "debug.h"
#include "matrix.h"
#include "quantum.h"

#define ROW_PORT PORTD
#define ROW_DDR DDRD
#define ROW_MASK 0x0F
#define COL_PORT PORTB
#define COL_PIN PINB
#define DIRECT_PORT PORTF
#define DIRECT_PIN PINF

void matrix_init_custom(void) {
    ROW_DDR |= ROW_MASK;
    COL_PORT = 0xFF;
    DIRECT_PORT |= 0xF3;
}

bool matrix_scan_custom(matrix_row_t current_matrix[]) {
    bool changed = false;

    uint8_t direct = ~DIRECT_PIN & 0xF3;
    if (current_matrix[16] != direct) {
      current_matrix[16] = direct;
      changed = true;
    }

    static uint8_t row = 0;
    ROW_PORT = (ROW_PORT & ~ROW_MASK) | (row & ROW_MASK);
    wait_us(5);                 // Wait for pull-ups to stabilize

    uint8_t cols = ~COL_PIN;
    if (current_matrix[row] != cols) {
        current_matrix[row] = cols;
        changed = true;
    }

    row = (row + 1) & ROW_MASK;

    return changed;
}
