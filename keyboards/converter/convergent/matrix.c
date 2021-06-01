
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

static matrix_row_t matrix[MATRIX_ROWS], incoming_matrix[MATRIX_ROWS];

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

#if defined(__AVR__)
    // If using software serial, SERIAL_SOFT_LOGIC_NEGATIVE should be set.
    // If using hardware UART, an inverter is needed between the keyboard and the RXD1 / TXD1 pins.
    serial_init();
#elif defined PROTOCOL_CHIBIOS
#if 0
    palSetPadMode(GPIOB, 16, PAL_MODE_ALTERNATIVE_3); // pin 0 / B16 / RX1 = UART0_RX
    palSetPadMode(GPIOB, 17, PAL_MODE_ALTERNATIVE_3); // pin 1 / B17 / TX1 = UART0_TX
#else
    // With the default _pal_lld_setpadmode (300), the TX line idles at about 2V.
    PORTB->PCR[16] = 0x313;       // UART, PFE, PE, PS
    PORTB->PCR[17] = 0x344;       // UART, DSE, SRE
#endif

    static const SerialConfig sdcfg = {
        1200
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

    // INIT- (pin 2) idle high
    wait_ms(10);
#if 0
    setPinOutput(D0);
#else
    // With the default _pal_lld_setpadmode (300), the RESET line idles at about 2V.
    PORTD->PCR[0] = 0x144;        // GPIO, DSE, SRE
#endif
    writePinLow(D0);
    wait_us(100);
    writePinHigh(D0);

    matrix_init_quantum();
}

uint8_t matrix_scan(void) {
    static enum { IDLE, SCANNING, FE_SEEN, B0_SEEN } state = IDLE;
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

    debug_enable = true;
    dprintf("%02X\n", data);

    if (data == 0xFE) {
        state = FE_SEEN;
        return 0;
    }
    if (state == FE_SEEN) {
        if (data == 0xB0) {
            state = B0_SEEN;
        }
        return 0;
    }
    if (state == B0_SEEN) {
#if defined(__AVR__)
        serial_send(0x92);
#elif defined PROTOCOL_CHIBIOS
        xprintf("C3 %02X\n", *(SD1.uart.c3_p));
        uint8_t buf[1] = { 0x92 };
        sdWrite(&SD1, buf, 1);
#endif
        state = IDLE;
        xprintf("Layout id %02X\n", data);
        return 0;
    }
    if (state == IDLE) {
        // Start of update: clear updated matrix.
        for (uint8_t i = 0; i < MATRIX_ROWS; i++) incoming_matrix[i] = 0x00;
        state = SCANNING;
    }
    if (data != 0xC0) {
        // C0 indicates an empty report, that is, the end bit with a special unused code.
        uint8_t col = data & 0x07;
        uint8_t row = (data >> 3) & 0x0F;
        incoming_matrix[row] |= (1 << col);
    }
    if (data & 0x80) {
        // End of update: transfer updated matrix.
        for (uint8_t i = 0; i < MATRIX_ROWS; i++) matrix[i] = incoming_matrix[i];
        state = IDLE;
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
