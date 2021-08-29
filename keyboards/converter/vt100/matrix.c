
#include <avr/io.h>
#include "debug.h"
#include "matrix.h"
#include "protocol/serial.h"
#include "print.h"

static matrix_row_t matrix[MATRIX_ROWS], incoming_matrix[MATRIX_ROWS];

extern uint8_t vt100_leds;

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

    // Set up AVR timers 1 & 3 to emulate the vertical scan signals used as clocks for the UART.
    DDRB |= (1 << 5);                // B5 is timer 1 channel A
    TCCR1B = _BV(WGM12) | _BV(CS10); // CTC; prescalar = 1
    TCCR1A = _BV(COM1A0); // Toggle on compare match
    OCR1A = 31;  // 32 / 16e6 = 2e-6 toggle = 4us period = LBA3
    DDRC |= (1 << 6);                // C6 is timer 3 channel A
    TCCR3B = _BV(WGM32) | _BV(CS30); // CTC; prescalar = 1
    TCCR3A = _BV(COM3A0); // Toggle on compare match
    OCR3A = 63;  // 64 / 16e6 = 4e-6 toggle = 8us period = LBA4
    // Synchronize counters
    TCNT1 = 0;
    TCNT3 = 6;

    SERIAL_UART_INIT();

    matrix_init_quantum();
}

uint8_t matrix_scan(void) {
    static bool scan_in_progress = false;
    if (scan_in_progress) {
        // TODO: In order to do the speaker properly, we need to transmit here, too.
        if (!SERIAL_UART_RXD_PRESENT) {
            return 0;
        }
        uint8_t data = SERIAL_UART_DATA;
        if (data == 0x7F) {
            for (uint8_t i = 0; i < MATRIX_ROWS; i++) matrix[i] = incoming_matrix[i];
            scan_in_progress = false;
        } else {
            uint8_t col = data & 0x0F;
            uint8_t row = (data >> 4) & 0x07;
            incoming_matrix[row] |= (1 << col);
        }
    } else if (SERIAL_UART_TXD_READY) {
        uint8_t data = vt100_leds & VT100_LED_MASK;
        data |= VT100_START_SCAN;
        SERIAL_UART_DATA = data;
        for (uint8_t i = 0; i < MATRIX_ROWS; i++) incoming_matrix[i] = 0x00;
        scan_in_progress = true;
    }

    matrix_scan_quantum();
    return 1;
}

void matrix_print(void) {
    print("\nr/c 0123456789ABCDEF\n");
    for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
        print_hex4(row); print(":  ");
        print_bin_reverse16(matrix_get_row(row));
        print("\n");
    }
}

inline
matrix_row_t matrix_get_row(uint8_t row) {
    return matrix[row];
}
