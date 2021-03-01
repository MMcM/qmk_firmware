
#include "debug.h"
#include "matrix.h"
#include "print.h"
#include "quantum.h"

#include <avr/io.h>
#include "protocol/serial.h"

#include "tek_led.h"

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

__attribute__((weak))
void encoder_update_user(int8_t index, bool clockwise) {
}

__attribute__((weak))
void encoder_update_kb(int8_t index, bool clockwise) {
    encoder_update_user(index, clockwise);
}

// RESET- idle high
#define RESET_PIN D1

static void reset(void) {
    led_reset();

    setPinOutput(RESET_PIN);
    writePinLow(RESET_PIN);
    wait_us(5);
    writePinHigh(RESET_PIN);
}

void matrix_init(void) {
    for (uint8_t i = 0; i < MATRIX_ROWS; i++) matrix[i] = 0x00;
  
    serial_init();

    reset();

    matrix_init_quantum();
}

#ifndef ENCODER_RESOLUTION
#define ENCODER_RESOLUTION 2
#endif

uint8_t matrix_scan(void) {
    static int8_t encoder_states[2] = { 0, 0 };
    bool encoder_updated = false;

    for (int index = 0; index < 2; index++) {
        if (encoder_states[index] >= ENCODER_RESOLUTION) {
            // Clockwise = right / up.
            encoder_update_kb(index, true);
            encoder_states[index] -= ENCODER_RESOLUTION;
            encoder_updated = true;
        } else if (encoder_states[index] <= -ENCODER_RESOLUTION) {
            encoder_update_kb(index, false);
            encoder_states[index] += ENCODER_RESOLUTION;
            encoder_updated = true;
        }
        if (encoder_updated) {
            break;
        }
    }

    if (!encoder_updated) {
        int16_t data2 = serial_recv2();
        if (data2 < 0) {
            return 0;
        }

        uint8_t code = data2 & 0xFF;
        dprintf("R: %02X\n", code);

        static uint8_t pending_fx = 0;
        if (pending_fx != 0) {
            switch (pending_fx) {
            case 0xF0:
                // The keyboard sends F0 00 after reset; I don't know what the second byte means.
                led_init();
                break;
            case 0xF1:
                encoder_states[0] += (int8_t)code;
                break;
            case 0xF2:
                encoder_states[1] += (int8_t)code;
                break;
            default:
                break;
            }
            pending_fx = 0;
        } else if (code >= 0xF0) {
            pending_fx = code;
        } else {
            uint8_t col = code & 0x0F;
            uint8_t row = (code >> 4) & 0x07;
            if ((code & 0x80) != 0) {
                matrix[row] &= ~(1 << col);
            } else {
                matrix[row] |= (1 << col);
            }
        }
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
