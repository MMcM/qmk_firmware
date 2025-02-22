
#include "debug.h"
#include "matrix.h"
#include "print.h"
#include "quantum.h"

#include <avr/io.h>
#include "uart.h"

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

    uart_init(1200);
    /* even parity */
    UCSR1C |= _BV(UPM11);

    reset();

    matrix_init_kb();
}

uint8_t matrix_scan(void) {
    if (!uart_available()) {
        return 0;
    }

    uint8_t code = uart_read();
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
            uart_write(0xFF);
            uart_write(0x01);
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

    matrix_scan_kb();
    return 1;
}
