
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
    print("\nr/c 01234567\n");
    for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
        print_hex8(row); print(": ");
        print_bin_reverse8(matrix_get_row(row));
        print("\n");
    }
}

static bool enabled;
static uint16_t last_check_time;
#define CHECK_INTERVAL 200
#define RELEASE_INTERVAL 10

static inline void send_cmd(uint8_t cmd) {
    uart_write(cmd);
}

void matrix_init(void) {
    for (uint8_t i = 0; i < MATRIX_ROWS; i++) matrix[i] = 0;

    uart_init(9600);
    // Need odd parity, since keypad does nothing until enabled by a command with just one bit.
#if defined(__AVR__)
    // Only UCSZn has been initialized (to 8-bit). Add parity enabled, odd parity.
    UCSR1C |= _BV(UPM11) | _BV(UPM10);
#elif defined(PROTOCOL_CHIBIOS)
#if defined(MCU_KINETIS)
    // SerialConfig struct only has baud rate. Set 9-bit, parity enable, parity type odd.
    *(SD1.uart.c1_p) |= UARTx_C1_M | UARTx_C1_PE | UARTx_C1_PT;
#else
    // For WB32F, UART_PARITY can be set in config.h for that field of SerialConfig.
    // For others using serial, SerialConfig is populated by UART_CR[1-3] defines.
    // For RP2040, which uses the sio driver, UART_RP_LCR_H is added to uart_sio to allow override.
    // For others using sio, SIO config again has UART_CR[1-3].
#endif
#endif

    enabled = false;
    last_check_time = timer_read();

    matrix_init_kb();
}

uint8_t matrix_scan(void) {
    static bool release_needed = false;
    static uint16_t last_press_time = 0;

    if (uart_available()) {
        uint8_t data = uart_read();
        dprintf("Received: %02X\n", data);

        if (release_needed) {
            // Two presses in very rapid succession.
            for (uint8_t i = 0; i < MATRIX_ROWS; i++) matrix[i] = 0;
            release_needed = false;
        }

        if (enabled) {
            if (data < 32) {
                uint8_t row = data >> 3;
                uint8_t col = data & 7;
                matrix[row] |= (1 << col);
                release_needed = true;
                last_press_time = timer_read();
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
    } else if (release_needed) {
        uint16_t now = timer_read();
        if (now - last_press_time > RELEASE_INTERVAL) {
            // There are no up transitions. Release all after a short interval.
            for (uint8_t i = 0; i < MATRIX_ROWS; i++) matrix[i] = 0;
            release_needed = false;
        }
    }

    matrix_scan_kb();
    return 1;
}
