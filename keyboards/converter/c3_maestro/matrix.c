
#include "debug.h"
#include "matrix.h"
#include "print.h"
#include "quantum.h"

#include "hal.h"

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

    palSetPadMode(GPIOB, 16, PAL_MODE_ALTERNATIVE_3); // pin 0 / B16 / RX1 = UART0_RX
    palSetPadMode(GPIOB, 17, PAL_MODE_ALTERNATIVE_3); // pin 1 / B17 / TX1 = UART0_TX

    static const SerialConfig sdcfg = {
        9600
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

    matrix_init_quantum();
}

uint8_t matrix_scan(void) {
    static enum { IDLE, C1_PREFIX, C0_PREFIX, E1_PREFIX, E0_PREFIX } state = IDLE;
    uint8_t data;

    msg_t msg = sdGetTimeout(&SD1, TIME_IMMEDIATE);
    if (msg < 0) {
        return 0;
    }
    data = msg & 0xFF;

    dprintf("%02X%c", data, data > 0xA0 ? ' ' : '\n');

    if (state == IDLE) {
        switch (data) {
        case 0xC1:
            state = C1_PREFIX;  // Press
            break;
        case 0xC0:
            state = C0_PREFIX;  // Release
            break;
        case 0xE1:
            state = E1_PREFIX;  // ALT press
            break;
        case 0xE0:
            state = E0_PREFIX;  // ALT release
            break;
        }
        // ALT down if ALT prefixed key press, up otherwise.
        if (state == E1_PREFIX) {
            matrix[MATRIX_ROWS - 1] = 1;
        } else {
            matrix[MATRIX_ROWS - 1] = 0;
        }
    } else if (data < 0xA0) {
        uint8_t col = data & 0x0F;
        uint8_t row = (data >> 4) & 0x0F;
        if (state == C1_PREFIX || state == E1_PREFIX) {
            matrix[row] |= (1 << col);
        } else {
            matrix[row] &= ~(1 << col);
        }
        state = IDLE;
    } else {
        state = IDLE;
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
