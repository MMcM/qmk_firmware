
#include "debug.h"
#include "matrix.h"
#include "quantum.h"

void matrix_init_custom(void) {
    setPinOutput(PIN_ADDR);
    setPinOutput(PIN_CLOCK);
    setPinInput(PIN_KEY);
    setPinInput(PIN_J2);
}

bool matrix_scan_custom(matrix_row_t current_matrix[]) {
    static uint8_t key_code = 0;
    uint8_t row = key_code >> 4;
    uint8_t col = key_code & 0x0F;
    uint8_t addr = KEY_ADDR(row, col);
    bool key_state = false;
    for (int i = 0; i < 8; i++) {
        // The SR can handle up to 25MHz and we are 16MHz, so no delay needed in strobe.
        writePin(PIN_ADDR, (addr & (1 << i)) != 0);
        writePinHigh(PIN_CLOCK);
        if (i == 7) {
            // Small delay needed for mux to stabilize.
            asm("nop\n\t");
            key_state = readPin(PIN_KEY);
        }
        writePinLow(PIN_CLOCK);
    }
    bool current_state = (current_matrix[row] & (1 << col)) != 0;
    bool changed = key_state != current_state;
    if (changed) {
        dprintf("%c%02X\n", key_state ? 'M' : 'B', key_code);
        if (key_state) {
            current_matrix[row] |= 1 << col;
        } else {
            current_matrix[row] &= ~(1 << col);
        }
    }
    key_code = (key_code + 1) & 0x7F; 
    return changed;
}
