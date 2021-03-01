
#include "debug.h"
#include "matrix.h"
#include "print.h"
#include "quantum.h"

#include <avr/io.h>
#include "protocol/serial.h"

#include "led_state.h"

static matrix_row_t matrix[MATRIX_ROWS];
static uint8_t xmit_row, recv_row;

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
    for (uint8_t i = 0; i < MATRIX_ROWS; i++) matrix[i] = 0;

    serial_init();
    serial_send(0x0F);            // Reset counter (no LED on).
    xmit_row = recv_row = 0;

    matrix_init_quantum();
}

uint8_t matrix_scan(void) {
    if (SERIAL_UART_TXD_READY) {
        uint8_t data = 0x10;        // Advance counter.
#ifdef LED_MATRIX_ENABLE
        led_state_t *states = g_led_states[xmit_row];
        for (uint8_t col = 0; col < MATRIX_COLS; col++) {
            if (!update_led_state(states + col)) {
                data |= (1 << col);     // Turn off this LED.
            }
        }
#else
        data |= (1 << MATRIX_COLS) - 1;
#endif
        SERIAL_UART_DATA = data;
        xmit_row++;
        if (xmit_row >= MATRIX_ROWS) {
            xmit_row = 0;             // Wrap around
        }
    }

    while (true) {
        int16_t data = serial_recv2();
        if (data < 0) break;
        matrix[recv_row] = data & 0x0F;
        if ((data & 0x20) == 0 || (recv_row + 1) >= MATRIX_ROWS) {
            recv_row = 0;
        } else {
            recv_row++;
        }
    }

    matrix_scan_quantum();
    return 1;
}

void matrix_print(void) {
    print("\nr/c 01234567\n");
    for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
        print_hex8(row); print(": ");
        print_bin_reverse8(matrix_get_row(row));
        print("\n");
    }
}

inline
matrix_row_t matrix_get_row(uint8_t row) {
    return matrix[row];
}
