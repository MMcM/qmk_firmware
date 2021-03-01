
#include "debug.h"
#include "matrix.h"
#include "print.h"
#include "quantum.h"

#if defined(__AVR__)
#include <avr/io.h>
#include "protocol/serial.h"
#elif defined PROTOCOL_CHIBIOS
#include "hal.h"
#ifndef SD_KEYBOARD
#define SD_KEYBOARD SD3
#endif
#endif

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
    for (uint8_t i = 0; i < MATRIX_ROWS; i++) matrix[i] = 0;

#if defined(__AVR__)
    serial_init();
#elif defined PROTOCOL_CHIBIOS
#if SD_KEYBOARD == SD1
    palSetPadMode(GPIOB, 16, PAL_MODE_ALTERNATIVE_3); // pin 0 / B16 / RX1 = UART0_RX
    palSetPadMode(GPIOB, 17, PAL_MODE_ALTERNATIVE_3); // pin 1 / B17 / TX1 = UART0_TX
#elif SD_KEYBOARD == SD3
    palSetPadMode(GPIOD, 2, PAL_MODE_ALTERNATIVE_3); // pin 7 / D2 / RX3 = UART2_RX
    palSetPadMode(GPIOD, 3, PAL_MODE_ALTERNATIVE_3); // pin 8 / D3 / TX2 = UART2_TX
#else
#error Unknown keyboard serial driver
#endif

    static const SerialConfig sdcfg = { 600 };
    sdStart(&SD_KEYBOARD, &sdcfg);
#if 1
    // TODO: SerialConfig for Kinetis is pretty minimal; it ought to have a way to set these bits.
    // Until then, set 8 bits + odd parity (so, 9 bits total) by hand.
    *(SD_KEYBOARD.uart.c1_p) |= UARTx_C1_M | UARTx_C1_PE | UARTx_C1_PT;
#endif
#endif
  
    matrix_init_quantum();
}

uint8_t dip_sw;

uint8_t matrix_scan(void) {
    uint8_t data;

#if defined(__AVR__)
    int16_t data2 = serial_recv2();
    if (data2 < 0) {
        return 0;
    }
    data = data2 & 0xFF;
#elif defined PROTOCOL_CHIBIOS
    msg_t msg = sdGetTimeout(&SD_KEYBOARD, TIME_IMMEDIATE);
    if (msg < 0) {
        return 0;
    }
    data = msg & 0xFF;
#endif

    static bool config = false;
    if (config) {
        dip_sw = data;
        config = false;
    } else if (data == 110) {
        config = true;
    } else {
        uint8_t col = data & 7;
        uint8_t row = (data >> 3) & 0x0F;
        if ((data & 0x80) == 0) {
            matrix[row] |= 1 << col;
        } else {
            matrix[row] &= ~(1 << col);
        }
    }

    matrix_scan_quantum();
    return 1;
}

void matrix_print(void) {
    print("\nr/c 012345678\n");
    for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
        print_dec(row); print(": ");
        print_bin_reverse8(matrix_get_row(row));
        print("\n");
    }
}

inline
matrix_row_t matrix_get_row(uint8_t row) {
    return matrix[row];
}
