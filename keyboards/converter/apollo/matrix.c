
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

// RESET - idle high
#define RESET_PIN D1

static void reset(void) {
    setPinOutput(RESET_PIN);
    writePinLow(RESET_PIN);
    wait_us(5);
    writePinHigh(RESET_PIN);
}

void matrix_init(void) {
    for (uint8_t i = 0; i < MATRIX_ROWS; i++) matrix[i] = 0x00;

    serial_init();

    reset();

    matrix_init_quantum();
}

uint8_t matrix_scan(void) {
    int16_t data = serial_recv2();
    if (data < 0) {
        return 0;
    }

    uint8_t code = data & 0xFF;
    dprintf("R: %02X\n", code);

    static bool mode_next = false;
    static bool mode_set = false;
    if (mode_next) {
        mode_next = false;
        if (code == 0x01) {
            mode_set = true;
        } else {
            // Switch to mode 1.
            dprintln("S: FF 01");
            serial_send(0xFF);
            serial_send(0x01);
        }
    } else if (code == 0xFF) {
        mode_next = true;
    } else if (!mode_set) {
        // Ignore until in proper mode.
    } else if (code == 0x7F) {
        // Ignore auto-repeat.
    } else {
        uint8_t row = (code >> 4) & 0x07;
        uint8_t col = code & 0x0F;
        if (code & 0x80) {
            // Key up.
            matrix[row] &= ~(1 << col);
        } else {
            // Key down.
            matrix[row] |= (1 << col);
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
