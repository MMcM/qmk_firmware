
#include "debug.h"
#include "matrix.h"
#include "quantum.h"

#define ADDR_PORT PORTB
#define ADDR_DDR DDRB
#define ADDR_MASK 0x7F
#define SENSE_PIN D0

void matrix_init_custom(void) {
    ADDR_DDR |= ADDR_MASK;
    gpio_set_pin_input(SENSE_PIN);
}

bool matrix_scan_custom(matrix_row_t current_matrix[]) {
    bool changed = false;

    for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
        for (uint8_t col = 0; col < MATRIX_COLS; col++) {
            ADDR_PORT = col | (row << 4);
            wait_us(1);
            bool state = gpio_read_pin(SENSE_PIN);
            uint16_t mask = 1 << col;
            if (state) {
                if ((current_matrix[row] & mask) == 0) {
                    current_matrix[row] |= mask;
                    changed = true;
                }
            } else {
                if ((current_matrix[row] & mask) == mask) {
                    current_matrix[row] &= ~mask;
                    changed = true;
                }
            }
        }
    }
    
    return changed;
}
