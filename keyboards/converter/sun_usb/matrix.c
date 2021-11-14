/*
Copyright 2012 Jun Wako <wakojun@gmail.com>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include QMK_KEYBOARD_H

#if defined(__AVR__)
#include "protocol/serial.h"
#elif defined PROTOCOL_CHIBIOS
#include "hal.h"
#endif

/*
 * Matrix Array usage:
 *
 * ROW: 16(4bits)
 * COL:  8(3bits)
 *
 *    8bit wide
 *   +---------+
 *  0|00 ... 07|
 *  1|08 ... 0F|
 *  :|   ...   |
 *  :|   ...   |
 *  E|70 ... 77|
 *  F|78 ... 7F|
 *   +---------+
 */
static uint8_t matrix[MATRIX_ROWS];
#define ROW(code)      ((code>>3)&0xF)
#define COL(code)      (code&0x07)

static bool is_modified = false;

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
uint8_t matrix_rows(void)
{
    return MATRIX_ROWS;
}

inline
uint8_t matrix_cols(void)
{
    return MATRIX_COLS;
}

void matrix_init(void)
{
    /* DDRD |= (1<<6); */
    /* PORTD |= (1<<6); */
    debug_enable = true;

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

    // initialize matrix state: all keys off
    for (uint8_t i=0; i < MATRIX_ROWS; i++) matrix[i] = 0x00;

    /* // wait for keyboard coming up */
    /* // otherwise LED status update fails */
    /* print("Reseting "); */
    /* while (1) { */
    /*     print("."); */
    /*     while (serial_recv()); */
    /*     serial_send(0x01); */
    /*     _delay_ms(500); */
    /*     if (serial_recv() == 0xFF) { */
    /*         _delay_ms(500); */
    /*         if (serial_recv() == 0x04) */
    /*             break; */
    /*     } */
    /* } */
    /* print(" Done\n"); */

    /* PORTD &= ~(1<<6); */

    matrix_init_quantum();
    return;
}

#if defined(__AVR__)
#define sun_recv serial_recv
#elif defined PROTOCOL_CHIBIOS
static inline uint8_t sun_recv(void) {
    msg_t msg = sdGetTimeout(&SD1, TIME_IMMEDIATE);
    if (msg < 0) {
        return 0;
    }
    return msg & 0xFF;
}
#endif

uint8_t matrix_scan(void)
{
    uint8_t code;
    code = sun_recv();
    if (!code) return 0;

    debug_hex(code); debug(" ");

    switch (code) {
        case 0xFF:  // reset success: FF 04
            print("reset: ");
            wait_ms(500);
            code = sun_recv();
            xprintf("%02X\n", code);
            if (code == 0x04) {
                // LED status
                led_set(host_keyboard_leds());
            }
            return 0;
        case 0xFE:  // layout: FE <layout>
            print("layout: ");
            wait_ms(500);
            xprintf("%02X\n", sun_recv());
            return 0;
        case 0x7E:  // reset fail: 7E 01
            print("reset fail: ");
            wait_ms(500);
            xprintf("%02X\n", sun_recv());
            return 0;
        case 0x7F:
            // all keys up
            for (uint8_t i=0; i < MATRIX_ROWS; i++) matrix[i] = 0x00;
            return 0;
    }

    if (code&0x80) {
        // break code
        if (matrix_is_on(ROW(code), COL(code))) {
            matrix[ROW(code)] &= ~(1<<COL(code));
        }
    } else {
        // make code
        if (!matrix_is_on(ROW(code), COL(code))) {
            matrix[ROW(code)] |=  (1<<COL(code));
        }
    }

    matrix_scan_quantum();
    return code;
}

bool matrix_is_modified(void)
{
    return is_modified;
}

inline
bool matrix_has_ghost(void)
{
    return false;
}

inline
bool matrix_is_on(uint8_t row, uint8_t col)
{
    return (matrix[row] & (1<<col));
}

inline
uint8_t matrix_get_row(uint8_t row)
{
    return matrix[row];
}

void matrix_print(void)
{
    print("\nr/c 01234567\n");
    for (uint8_t row = 0; row < matrix_rows(); row++) {
        print_hex8(row); print(": ");
        print_bin_reverse8(matrix_get_row(row));
        print("\n");
    }
}
