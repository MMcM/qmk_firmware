
#include "debug.h"
#include "matrix.h"
#include "quantum.h"

#define ADDR_PORT PORTC
#define ADDR_DDR DDRC
#define DATA_PIN PINF
#define KYBD_PORT PORTE
#define KYBD_DDR DDRE
#define KYBD_MASK (1 << 0)

void matrix_init_custom(void) {
    ADDR_DDR = 0xFF;
    KYBD_DDR |= KYBD_MASK;
    KYBD_PORT |= KYBD_MASK;
}

bool matrix_scan_custom(matrix_row_t current_matrix[]) {
    bool changed = false;
    for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
        ADDR_PORT = (1 << row);
        KYBD_PORT &= ~KYBD_MASK;
        wait_us(1);
        uint8_t cols = DATA_PIN;
        KYBD_PORT |= KYBD_MASK;
        if (current_matrix[row] != cols) {
            current_matrix[row] = cols;
            changed = true;
        }
    }
    return changed;
}
