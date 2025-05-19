
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

void matrix_init(void) {
    for (uint8_t i = 0; i < MATRIX_ROWS; i++) matrix[i] = 0x00;

    gpio_set_pin_input_high(D2); // Open collector
    uart_init(62500);
    UCSR1C |= _BV(USBS1);       // Two stop bits

    matrix_init_kb();
}

void wang_cmd(uint8_t cmd) {
    dprintf("W%02X ", cmd);
    uart_write(cmd);
}

uint8_t wang_version = 0x00;

uint8_t matrix_scan(void) {
    debug_enable = true;

    static enum {
        INIT, START, RESET, WAIT_PREAMBLE, WAIT_VERSION, HAVE_VERSION, DONE
    } init_state = INIT;
    if (init_state != DONE) {
        static uint16_t init_time;
        uint16_t now = timer_read();
        uint16_t time_diff = now - init_time;
        switch (init_state) {
        case INIT:
            init_state = START;
            init_time = now;
            break;
        case START:
            if (time_diff > 100) {
                wang_cmd(0x08);     // Power-on reset
                init_state = RESET;
                init_time = now;
            }
            break;
        case RESET:
            if (time_diff > 100) {
                wang_cmd(0x09); // Version level query
                init_state = WAIT_PREAMBLE;
                init_time = now;
            }
            break;
        case WAIT_PREAMBLE:
        case WAIT_VERSION:
            if (uart_available()) {
                uint8_t code = uart_read();
                dprintf("R%02X ", code);
                if (init_state == WAIT_VERSION) {
                    wang_version = code;
                    init_state = HAVE_VERSION;
                } else if (code == 0x01) {
                    init_state = WAIT_VERSION;
                }
                init_time = now;
            } else if (time_diff > 200) {
                init_state = HAVE_VERSION; // Give up
            }
            break;
        case HAVE_VERSION:
            wang_cmd(0x06);     // Release codes for every key
            init_state = DONE;
            break;
        case DONE:
        default:
            break;
        }
    }

    if (!uart_available()) {
        return 0;
    }

    uint8_t code = uart_read();
    dprintf("R%02X ", code);

    if (code == 0x36) {
        wang_cmd(0x08);             // Power-on reset
        wait_ms(100);
        wang_cmd(0x06);             // Release codes for every key
        return 0;
    }

    uint8_t row = (code >> 4) & 0x07;
    if (row > 0) {
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
