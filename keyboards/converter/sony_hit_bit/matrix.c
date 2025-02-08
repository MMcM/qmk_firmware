
#include "debug.h"
#include "matrix.h"
#include "quantum.h"

#define DATA_DDR DDRB
#define DATA_PIN PINB
#define DATA_PORT PORTB
#define KBDIR_DDR DDRD
#define KBDIR_PORT PORTD
#define KBDIR_MASK (1 << 0)

void matrix_init_custom(void) {
    DATA_DDR = 0;
    DATA_PORT = 0xFF;

    KBDIR_DDR |= KBDIR_MASK;
    KBDIR_PORT |= KBDIR_MASK;
}

bool matrix_scan_custom(matrix_row_t current_matrix[]) {
    bool changed = false;

    for (uint8_t row = 0; row < 11; row++) {
        uint8_t mask = 0x00;
        if (row & 1) {
            mask |= 0x80;
        }
        if (row & 2) {
            mask |= 0x40;
        }
        if (row & 4) {
            mask |= 0x20;
        }
        if (row & 8) {
            mask |= 0x10;
        }
        KBDIR_PORT &= ~KBDIR_MASK;
        asm("nop");
        DATA_DDR = 0xF0;
        DATA_PORT = mask;
        KBDIR_PORT |= KBDIR_MASK;
        asm("nop");
        DATA_DDR = 0x00;
        DATA_PORT = 0xFF;
        wait_us(4);
        uint8_t bits = ~DATA_PIN;
        if (current_matrix[row] != bits) {
            current_matrix[row] = bits;
            changed = true;
        }
    }

    return changed;
}
