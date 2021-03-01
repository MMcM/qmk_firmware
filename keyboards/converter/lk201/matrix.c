
#include "debug.h"
#include "matrix.h"
#include "print.h"
#include "quantum.h"
#include "timer.h"

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

static inline void send_cmd(uint8_t cmd) {
#if defined(__AVR__)
    serial_send(cmd);
#elif defined PROTOCOL_CHIBIOS
    sdWrite(&SD1, &cmd, 1);
#endif
}

static uint16_t init_time;
static bool init_done = false;

#ifdef MS_7004
static bool keys_up_needed = false;
#endif

void matrix_init(void) {
    for (uint8_t i = 0; i < MATRIX_ROWS; i++) matrix[i] = 0;

#if defined(__AVR__)
    serial_init();
#elif defined PROTOCOL_CHIBIOS
    palSetPadMode(GPIOB, 16, PAL_MODE_ALTERNATIVE_3); // pin 0 / B16 / RX1 = UART0_RX
    palSetPadMode(GPIOB, 17, PAL_MODE_ALTERNATIVE_3); // pin 1 / B17 / TX1 = UART0_TX

    static const SerialConfig sdcfg = { 4800 };
    sdStart(&SD1, &sdcfg);
#endif
  
    init_time = timer_read();
  
    matrix_init_quantum();
}

uint8_t matrix_scan(void) {
    if (!init_done) {
        // Delay init a little bit for serial line to settle down.
        if (timer_read() - init_time > 100) {
#ifndef MS_7004
            send_cmd(0xA7);               // Beep
            send_cmd(0xD3);               // Reinstate defaults
            for (uint8_t div = 1; div <= 14; div++) {
                send_cmd(div << 3 | 0x86);  // Down/up mode
            }
            send_cmd(0xE9);               // Enable LK401 keys
#endif
            init_done = true;
        } else {
            return 0;
        }
    }

#ifdef MS_7004
    if (keys_up_needed) {
        for (uint8_t i = 0; i < MATRIX_ROWS; i++) {
            if (i == 0x0A) {
                matrix[i] &= 0xC000; // Keep AE & AF, the only shifts that send B3.
            } else {
                matrix[i] = 0;
            }
        }
        keys_up_needed = false;
        return 0;
    }
#endif

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

    if (data == 0xB3) {
        // All up
        for (uint8_t i = 0; i < MATRIX_ROWS; i++) matrix[i] = 0;
    } else if ((data >= 0xB4 && data <= 0xBA) || data == 0x7F) {
        // Special codes
    } else {
        uint8_t col = data & 0x0F;
        uint8_t row = (data >> 4) & 0x0F;
#ifndef MS_7004
        matrix[row] ^= (1 << col);  // Toggle key state
#else
        if (data == 0xAE || data == 0xAF) {
            matrix[row] ^= (1 << col); // Shifts toggle
        } else {
            matrix[row] |= (1 << col); // Ordinary keys do not
            keys_up_needed = true;
        }
#endif
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
