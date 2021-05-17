
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

static bool enabled;
static uint16_t last_check_time;
#define CHECK_INTERVAL 200

#if defined(__AVR__)
static inline void send_cmd(uint8_t cmd) {
    serial_send(cmd);
}
#elif defined PROTOCOL_CHIBIOS
static void send_cmd(uint8_t cmd) {
    uint8_t buf[1];
    buf[0] = cmd;
    sdWrite(&SD1, buf, 1);
}
#endif

void matrix_init(void) {
    for (uint8_t i = 0; i < MATRIX_ROWS; i++) matrix[i] = 0;

#if defined(__AVR__)
    serial_init();
#elif defined PROTOCOL_CHIBIOS
    palSetPadMode(GPIOB, 16, PAL_MODE_ALTERNATIVE_3); // pin 0 / B16 / RX1 = UART0_RX
    palSetPadMode(GPIOB, 17, PAL_MODE_ALTERNATIVE_3); // pin 1 / B17 / TX1 = UART0_TX

    static const SerialConfig sdcfg = { 9600 };
    sdStart(&SD1, &sdcfg);
    *(SD1.uart.c1_p) |= UARTx_C1_M | UARTx_C1_PE | UARTx_C1_PT; // 9-bit mode, odd parity.
#endif

    enabled = false;
    last_check_time = timer_read();

    matrix_init_quantum();
}

uint8_t matrix_scan(void) {
    debug_enable = true;

    // There are no up transitions.
    for (uint8_t i = 0; i < MATRIX_ROWS; i++) matrix[i] = 0;
    
    uint8_t data;
    bool have_data;

#if defined(__AVR__)
    int16_t data2 = serial_recv2();
    if (data2 < 0) {
        have_data = false;
    } else {
        data = data2 & 0xFF;
        have_data = true;
    }
#elif defined PROTOCOL_CHIBIOS
    msg_t msg = sdGetTimeout(&SD1, TIME_IMMEDIATE);
    if (msg < 0) {
        have_data = false;
    } else {
        data = msg & 0xFF;
        have_data = true;
    }
#endif

    if (have_data) {
        dprintf("Received: %02X\n", data);

        if (enabled) {
            if (data < 32) {
                uint8_t row = data >> 3;
                uint8_t col = data & 7;
                matrix[row] |= (1 << col);
            } else if (data == 0x80) {
                // LED retransmit needed (.flush is called by led_matrix_task, which is called by matrix_scan_quantum).
                extern bool led_retransmit_needed;
                led_retransmit_needed = true;
            } else if (data == 0x81) {
                // LED transmit okay.
            }
        } else {
            if (data == 0x03) {     // Config response
                send_cmd(0x08);     // Enable
                enabled = true;
            } else {
                send_cmd(0x01);     // Reset
            }
        }
    } else if (!enabled) {
        uint16_t now = timer_read();
        if (now - last_check_time > CHECK_INTERVAL) {
            send_cmd(0x06);         // Read configuration
            last_check_time = now;
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
