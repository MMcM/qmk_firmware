
#include "debug.h"
#include "matrix.h"
#include "print.h"
#include "quantum.h"

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

#ifdef LED_PIN
    // Turn on LED until init is complete.
    setPinOutput(LED_PIN);
    writePinHigh(LED_PIN);
#endif

#if 0
    uart_init(2400);
#elif defined PROTOCOL_CHIBIOS
#if 0
    palSetPadMode(GPIOB, 16, PAL_MODE_ALTERNATIVE_3); // pin 0 / B16 / RX1 = UART0_RX
    palSetPadMode(GPIOB, 17, PAL_MODE_ALTERNATIVE_3); // pin 1 / B17 / TX1 = UART0_TX
    palSetPadMode(GPIOD, 2, PAL_MODE_ALTERNATIVE_3); // pin 7 / D2 / RX3 = UART2_RX
    palSetPadMode(GPIOD, 3, PAL_MODE_ALTERNATIVE_3); // pin 8 / D3 / TX3 = UART2_TX
#else
    // With the default _pal_lld_setpadmode (300), the TX line idles at about 2V.
    PORTB->PCR[16] = 0x313;       // UART, PFE, PE, PS
    PORTB->PCR[17] = 0x344;       // UART, DSE, SRE
    PORTD->PCR[2] = 0x313;        // UART, PFE, PE, PS
    PORTD->PCR[3] = 0x344;        // UART, DSE, SRE
#endif
    static const SerialConfig sd1cfg = { 2440 };
    sdStart(&SD1, &sd1cfg);
    *(SD1.uart.c1_p) |= UARTx_C1_PE | UARTx_C1_M; // Even parity, so 9 bits
    *(SD1.uart.s2_p) |= UARTx_S2_RXINV; // Receive inverted
    *(SD1.uart.c3_p) |= UARTx_C3_TXINV; // Transmit inverted
    static const SerialConfig sd3cfg = { 305 };
    sdStart(&SD3, &sd3cfg);
    *(SD3.uart.c1_p) |= UARTx_C1_PE | UARTx_C1_M;
    *(SD3.uart.s2_p) |= UARTx_S2_RXINV;
    *(SD3.uart.c3_p) |= UARTx_C3_TXINV;
#else
#error Need serial support
#endif

    matrix_init_kb();
}

#ifdef PROTOCOL_CHIBIOS
bool uart_available(void) {
    return !sdGetWouldBlock(&SD1);
}

uint8_t uart_read(void) {
    return (uint8_t)sdGet(&SD1);
}

void send_cmd(uint8_t cmd) {
    dprintf("W%02X ", cmd);
    sdPut(&SD3, cmd);
    msg_t check = sdGetTimeout(&SD3, TIME_MS2I(100));
    if (MSG_TIMEOUT == check) {
        dprintf("NO LOOP? ");
        return;
    }
    uint8_t check_cmd = (uint8_t)(check & 0xFF);
    if (check_cmd != cmd) {
        dprintf("L%02X ", check_cmd);
    }
}
#endif

uint8_t matrix_scan(void) {
    // No up transitions, so clear all but shifts.
    for (uint8_t i = 0; i < MATRIX_ROWS - 1; i++) matrix[i] = 0x00;
    matrix[MATRIX_ROWS - 1] &= 0xF0;

    debug_enable = true;

    static enum {
        INIT, START, RESET_SENT, RESET_ACK, NO_REPEAT_SENT, NO_REPEAT_ACK, DONE
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
                send_cmd(0x07);     // Reset
                init_state = RESET_SENT;
                init_time = now;
            }
            break;
        case RESET_ACK:
            send_cmd(0x02);     // Disable auto-repeat
            init_state = NO_REPEAT_SENT;
            init_time = now;
            break;
        case RESET_SENT:
        case NO_REPEAT_SENT:
            if (time_diff > 250) {
                init_state = INIT;
                init_time = now;
            }
            break;
        case NO_REPEAT_ACK:
            init_state = DONE;
            init_time = now;
#ifdef LED_PIN
            writePinLow(LED_PIN);
#endif
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

    if (init_state != DONE) {
        if (code == 0x70) {
            switch (init_state) {
            case RESET_SENT:
                init_state = RESET_ACK;
                break;
            case NO_REPEAT_SENT:
                init_state = NO_REPEAT_ACK;
                break;
            default:
                break;
            }
        }
        return 0;
    }

    if ((code & 0x78) == 0x78) {
        // Set shift states starting with 74.
        uint8_t shifts = (code & 0x07) | ((code & 0x80) >> 4);
        matrix[MATRIX_ROWS - 1] = (matrix[MATRIX_ROWS - 1] & 0xFF0F) | (shifts << 4);
    } else {
        uint8_t col = code & 0x0F;
        uint8_t row = (code >> 4) & 0x07;
        matrix[row] |= 1 << col;
    }

    matrix_scan_kb();
    return 1;
}
