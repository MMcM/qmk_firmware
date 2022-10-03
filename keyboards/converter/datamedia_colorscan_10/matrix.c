
#include <avr/io.h>
#include "debug.h"
#include "gpio.h"
#include "matrix.h"
#include "print.h"
#include "timer.h"
#include "wait.h"

#define BIT_WIDTH 2500
#define NO_DATA 0xFF
#define START_BIT (1 << 0)
#define STOP_BIT (1 << 13)

static uint16_t poll(uint16_t send_data) {
    setPinOutput(DATA_PIN);
    writePinLow(DATA_PIN);
    wait_us(BIT_WIDTH);
    for (uint8_t i = 0; i < 11; i++) {
        if (send_data & (1 << i)) {
            writePinLow(DATA_PIN);
        } else {
            writePinHigh(DATA_PIN);
        }
        wait_us(BIT_WIDTH);
    }
    setPinInputHigh(DATA_PIN);
    wait_us(BIT_WIDTH / 2);
    if (readPin(DATA_PIN)) {
        return NO_DATA;
    }
    uint16_t recv_data = 0;
    for (uint8_t i = 1; i < 14; i++) {
        wait_us(BIT_WIDTH);
        if (readPin(DATA_PIN)) {
            recv_data |= (1 << i);
        }
    }
    return recv_data;
}

static matrix_row_t matrix[MATRIX_ROWS];

extern uint8_t color_10_leds;

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

static uint16_t start_time;

void matrix_init(void) {
    for (uint8_t i = 0; i < MATRIX_ROWS; i++) matrix[i] = 0x00;

    setPinInputHigh(DATA_PIN);
    start_time = timer_read();

    matrix_init_quantum();
}

uint8_t matrix_scan(void) {
    static enum { INIT, POLL, SHIFT, CODE, ALL_UP } state = INIT;
    static uint16_t recv_data = 0;

    if (state == INIT) {
        if (timer_read() - start_time > 1000) {
            poll(0x11F);        // Beep & flash LEDs, since this is a long time.
            state = POLL;
        }
    } else if (state == POLL) {
        extern uint8_t color_10_leds;
        recv_data = poll(color_10_leds);
        if (recv_data != NO_DATA) {
            if (((recv_data & START_BIT) != 0) ||
                ((recv_data & STOP_BIT) == 0)) {
                dprintln("Framing error");
            } else {
                dprintf("%03X\n", (recv_data >> 1) & 0xFFF);
                state = SHIFT;
            }
        }
    } else if (state == SHIFT) {
        matrix[MATRIX_ROWS - 1] = (recv_data >> 8) & 0x1F;
        state = CODE;
    } else if (state == CODE) {
        uint8_t row = (recv_data >> 5) & 0x07;
        uint8_t col = (recv_data >> 1) & 0x0F;
        if (row < MATRIX_ROWS) {
            matrix[row] |= (1 << col);
        }
        state = ALL_UP;
    } else if (state == ALL_UP) {
        // There are no up transitions, so clear everything between codes.
        for (uint8_t i = 0; i < MATRIX_ROWS; i++) matrix[i] = 0;
        state = POLL;
    }
    
    matrix_scan_quantum();
    return 1;
}

void matrix_print(void) {
    print("\nr/c 0123456789ABCDEF\n");
    for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
        print_hex4(row); print(":  ");
        print_bin_reverse16(matrix_get_row(row));
        print("\n");
    }
}

inline
matrix_row_t matrix_get_row(uint8_t row) {
    return matrix[row];
}
