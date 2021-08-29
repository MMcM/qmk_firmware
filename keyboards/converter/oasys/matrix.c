
#include "debug.h"
#include "matrix.h"
#include "print.h"
#include "quantum.h"

#include <avr/io.h>
#include "protocol/serial.h"

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
  
    serial_init();

    matrix_init_quantum();
}

static inline void set_key(uint8_t code, bool state) {
    uint8_t col = code & 0x0F;
    uint8_t row = (code >> 4) & 0x07;
    if (state) {
        matrix[row] |= (1 << col);
    } else {
        matrix[row] &= ~(1 << col);
    }
}

bool oasys_is_jis = false;

uint8_t matrix_scan(void) {
    debug_enable = true;

    static uint8_t prefix_code = 0;

    int16_t data2 = serial_recv2();
    if (data2 < 0) {
        return 0;
    }

    uint8_t code = data2 & 0xFF;
    dprintf("%02X%c", code, code & 0x80 ? ' ' : '\n');
    if ((code & 0x80) != 0) {
        prefix_code = code;
        return 0;
    }

    if ((prefix_code & 0xF0) == 0xF0) {
        // Special handling for arrow keys.
        switch (prefix_code) {
        case 0xF0:
            // Auto-repeat of cursor; uses ordinary code.
            set_key(code, true);
            break;
        case 0xF1:
            // Break, but with special cursor code.
            set_key(0x4D + (code & 0x07), false);
            break;
        case 0xF2:              // Make with cursor code.
        case 0xF8:              // Exit diagonal mode.
        case 0xFA:              // Combination of these two.
            set_key(0x4D + (code & 0x07), true);
            break;
        case 0xF9:
            // Enter diagonal mode: nibble for each cursor code.
            set_key(0x4D + (code & 0x07), true);
            set_key(0x4D + ((code >> 4) & 0x03), true);
            break;
        }
    } else if ((prefix_code & 0xF0) == 0xE0) {
        // Apparently this is mouse data in some format.
    } else {
        // 10 make / break; 20 thumb / JIS
        if ((prefix_code & 0x10) == 0) {
            oasys_is_jis = (prefix_code & 0x20) != 0;
            set_key(code, true);
        } else if (code == 0x7F) {
            for (uint8_t i = 0; i < MATRIX_ROWS; i++) matrix[i] = 0x00;            
        } else {
            set_key(code, false);
        }
    }

    matrix_scan_quantum();
    return 1;
}

void matrix_print(void) {
    print("\nr/c 0123456789ABCDEF\n");
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
