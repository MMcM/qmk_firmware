
#include "debug.h"
#include "matrix.h"
#include "quantum.h"

#define ROW_DDR DDRB
#define ROW_PIN PINB
#define ROW_PORT PORTB
#define ROW_MASK ((1 << MATRIX_ROWS) - 1)

#define CLK_PIN D0
#define B_PIN D1

static inline void shift_out(bool level) {
    gpio_write_pin(B_PIN, level);
    gpio_write_pin_high(CLK_PIN);
    wait_us(1);
    gpio_write_pin_low(CLK_PIN);
}

void matrix_init_custom(void) {
    ROW_DDR &= ~ROW_MASK;
    ROW_PORT |= ROW_MASK;
    gpio_set_pin_output(CLK_PIN);
    gpio_set_pin_output(B_PIN);

    for (uint8_t c = 0; c < 16; c++) {
        shift_out(true);        // Fill with H.
    }
}

// Given the column shift register position, get the physical position.
static const uint8_t PROGMEM colshifts[16] = {
#define COL_SHIFT(col, ic, pos) [col] = ic*8+pos
    COL_SHIFT(0, 1, 3),
    COL_SHIFT(1, 1, 2),
    COL_SHIFT(2, 1, 1),
    COL_SHIFT(3, 1, 0),
    COL_SHIFT(4, 1, 7),
    COL_SHIFT(5, 1, 6),
    COL_SHIFT(6, 1, 5),
    COL_SHIFT(7, 1, 4),
    COL_SHIFT(8, 0, 3),
    COL_SHIFT(9, 0, 2),
    COL_SHIFT(10, 0, 1),
    COL_SHIFT(11, 0, 0),
    COL_SHIFT(12, 0, 7),
    COL_SHIFT(13, 0, 6),
    COL_SHIFT(14, 0, 5),
    COL_SHIFT(15, 0, 4),
};

bool matrix_scan_custom(matrix_row_t current_matrix[]) {
    bool changed = false;

    static uint8_t col_shift = 0xFF;

    col_shift = (col_shift + 1) & 0x0F;
    shift_out(col_shift != 0);  // New L bit every 16 shifts.
    wait_us(5);                 // Diode + pull-ups needs a while.

    uint8_t col = pgm_read_byte(colshifts + col_shift);
    uint16_t mask = (uint16_t)1 << col;

    uint8_t rows = ROW_PIN & ROW_MASK;
    for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
        if ((rows & (1 << row)) == 0) { // Low means pressed.
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

    return changed;
}
