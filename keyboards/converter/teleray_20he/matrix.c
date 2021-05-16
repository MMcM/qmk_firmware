
#include "debug.h"
#include "matrix.h"
#include "print.h"
#include "quantum.h"

#if defined(__AVR__)
#include <avr/io.h>
#include "protocol/serial.h"
#elif defined PROTOCOL_CHIBIOS
#include "hal.h"
#endif

static matrix_row_t matrix[MATRIX_ROWS], sticky_matrix[MATRIX_ROWS];

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
    for (uint8_t i = 0; i < MATRIX_ROWS; i++) matrix[i] = sticky_matrix[i] = 0x00;

#if defined(__AVR__)
    // If using hardware UART, an inverter is needed between the keyboard and the RXD1 / TXD1 pins.
    serial_init();
#elif defined PROTOCOL_CHIBIOS
    palSetPadMode(GPIOB, 16, PAL_MODE_ALTERNATIVE_3); // pin 0 / B16 / RX1 = UART0_RX
    palSetPadMode(GPIOB, 17, PAL_MODE_ALTERNATIVE_3); // pin 1 / B17 / TX1 = UART0_TX

    static const SerialConfig sdcfg = {
        4800
        // TODO: SerialConfig for Kinetis is pretty minimal; it ought to have a way to set these bits.
#if 0
        , 0, UARTx_S2_RXINV, UARTx_C3_TXINV
#endif
    };
    sdStart(&SD1, &sdcfg);
#if 1
    // Until then, set polarity registers by hand.
    *(SD1.uart.s2_p) |= UARTx_S2_RXINV;
    *(SD1.uart.c3_p) |= UARTx_C3_TXINV;
#endif
#endif

    matrix_init_quantum();
}

uint8_t matrix_scan(void) {
    // Only a few keys send up transitions; clear the rest.
    for (uint8_t i = 0; i < MATRIX_ROWS; i++) matrix[i] = sticky_matrix[i];

    uint8_t data;

#if defined(__AVR__)
    int16_t data2 = serial_recv2();
    if (data2 < 0) {
        return 0;
    }
    data = data2 & 0xFF;
#elif defined PROTOCOL_CHIBIOS
    msg_t msg = sdGetTimeout(&SD1, TIME_IMMEDIATE);
    if (msg < 0) {
        return 0;
    }
    data = msg & 0xFF;
#endif

    uint8_t row = (data >> 4) & 7;
    uint8_t col = data & 0x0F;
    if (data & 0x80) {
        // The keyboard also sends FA, that is, key up for the last key + 1, all the time. That is harmless.
        matrix[row] &= ~(1 << col);
        sticky_matrix[row] &= ~(1 << col);
    } else {
        matrix[row] |= (1 << col);
        // Can expect up from three upper-right locking keys, both Shifts, and Control.
        if (data == 0x13 || data == 0x14 || data == 0x15 ||
            data == 0x58 || data == 0x63 || data == 0x72) {
            sticky_matrix[row] |= (1 << col);
        }
    }

    matrix_scan_quantum();
    return 1;
}

void matrix_print(void) {
    print("\nr/c 012345678ABCDEF\n");
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
