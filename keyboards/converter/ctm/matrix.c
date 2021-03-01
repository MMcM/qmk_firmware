
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

/**
 * Keys are divided into three sections: the main typewriter keys, the space bar, and the rest (function keys).
 * Within each section, codes are just assigned top-to-bottom, left-to-right.
 * The overall order is function (1 - 53), space (54), main (55 - 103).
 * Then come the shifted versions, but in the order main (104 - 152, shifting 55 - 103), space (153 shifting 54),
 * function (154 - 206, shifting 1 - 53).
 */
static uint8_t unshift(uint8_t code) {
    if (code <= 103) {
        return code;
    } else if (code <= 152) {
        return code - 49;
    } else if (code == 153) {
        return 54;
    } else if (code <= 206) {
        return code - 153;
    } else {
        return code;
    }
}

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

    // RESET- (pin 2) idle high
#if defined(__AVR__)
    setPinOutput(D0);
    writePinLow(D0);
    _delay_us(10);
    writePinHigh(D0);
#elif defined PROTOCOL_CHIBIOS
#if 0
    setPinOutput(C5);
#else
    // With the default _pal_lld_setpadmode (300), the RESET line idles at about 2V, which confuses the 6801.
    PORTD->PCR[0] = 0x144;        // GPIO, DSE, SRE
#endif
    writePinLow(D0);
    writePinHigh(C5);
    static const GPTConfig gpt4cfg = {
        1000000, // 1 MHz
        NULL     // No callback
    };
    gptStart(&GPTD4, &gpt4cfg);
    gptPolledDelay(&GPTD4, 10);   // 10us
    writePinHigh(D0);
    writePinLow(C5);
#endif

#if defined(__AVR__)
    // If using software serial, SERIAL_SOFT_LOGIC_NEGATIVE should be set.
    // If using hardware UART, an inverter is needed between the keyboard and the RXD1 / TXD1 pins.
    serial_init();
#elif defined PROTOCOL_CHIBIOS
#if 0
    palSetPadMode(GPIOB, 16, PAL_MODE_ALTERNATIVE_3); // pin 0 / B16 / RX1 = UART0_RX
    palSetPadMode(GPIOB, 17, PAL_MODE_ALTERNATIVE_3); // pin 1 / B17 / TX1 = UART0_TX
#else
    // With the default _pal_lld_setpadmode (300), the TX line idles at about 2V, which confuses the 6801.
    PORTB->PCR[16] = 0x313;       // UART, PFE, PE, PS
    PORTB->PCR[17] = 0x344;       // UART, DSE, SRE
#endif

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
#endif

    matrix_init_quantum();
}

uint8_t matrix_scan(void) {
    static enum { SCAN, CTRL, SHIFT, CODE, ALL_UP } state = SCAN;
    static uint8_t shifts;
    static uint8_t code;

    if (state == ALL_UP) {
        // There are no up transitions, so clear everything between codes.
        for (uint8_t i = 0; i < MATRIX_ROWS; i++) matrix[i] = 0;
        shifts = 0;
        state = SCAN;
    } else if (state == CODE) {
        uint8_t col = code & 0x07;
        uint8_t row = (code >> 3) & 0x0F;
        matrix[row] |= (1 << col);
        state = ALL_UP;
    } else if (state == SHIFT) {
        matrix[MATRIX_ROWS - 1] |= shifts;
        state = CODE;
    } else {
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

        dprintf("%d\n", data);

#if defined(__AVR__)
        serial_send(1);
#elif defined PROTOCOL_CHIBIOS
        uint8_t one[1] = { 1 };
        sdWrite(&SD1, one, 1);
#endif

        if (data == 0) {
            // Ignore.
        } else if (data <= 103) {
            // Normal unshifted.
            code = data;
            state = state == CTRL ? SHIFT : CODE;
        } else if (data <= 206) {
            // SHIFT-ed.
            code = unshift(data);
            shifts |= 1 << 0;
            state = SHIFT;
        } else if (data == 253) {
            // CTRL prefix.
            shifts |= 1 << 1;
            state = CTRL;
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
