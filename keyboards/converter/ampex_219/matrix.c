
#include "debug.h"
#include "matrix.h"
#include "print.h"
#include "quantum.h"

#include <avr/io.h>

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

#define DATA_PORT PORTD
#define DATA_PIN PIND
#define DATA_DDR DDRD
#define DATA_MASK (1 << 0)

#define BIT_TIME_MICROS 724
#define STROBE_PERIOD_MILLIS 5
#define STROBE_TIME_MICROS 10

typedef union {
    uint16_t as_short;
    struct {
        unsigned stop_bit: 1;
        unsigned scan_code: 8;
        unsigned shifts: 3;
        unsigned start_bit: 1;
    };
} frame_t;

void matrix_init(void) {
    for (uint8_t i = 0; i < MATRIX_ROWS; i++) matrix[i] = 0;
  
    DATA_DDR &= ~DATA_MASK;
    DATA_PORT |= DATA_MASK;

    matrix_init_quantum();
}

uint8_t matrix_scan(void) {
    static frame_t frame;
    static enum { SCAN, SHIFT, CODE, ALL_UP } state = SCAN;

    if (state == ALL_UP) {
        // There are no up transitions, so clear everything between codes.
        for (uint8_t i = 0; i < MATRIX_ROWS; i++) matrix[i] = 0;
        state = SCAN;
    } else if (state == SHIFT) {
        matrix[7] = frame.shifts;
        state = CODE;
    } else if (state == CODE) {
        uint8_t col = frame.scan_code & 0x0F;
        uint8_t row = (frame.scan_code >> 4) & 0x0F;
        matrix[row] |= (1 << col);
        state = ALL_UP;
    } else if ((DATA_PIN & DATA_MASK) == 0) {
        frame.as_short = 0;
        wait_us(BIT_TIME_MICROS / 2);

        uint16_t mask = 1 << 12;
        while (true) {
            if ((DATA_PIN & DATA_MASK) != 0) {
                frame.as_short |= mask;
            }
            mask >>= 1;
            if (mask == 0) {
                break;
            }
            wait_us(BIT_TIME_MICROS);
        }

        if (frame.start_bit != 0 || frame.stop_bit != 1) {
            dprintf("Framing error: %X\n", frame.as_short);
        } else {
            dprintf("%d + %02X\n", frame.shifts, frame.scan_code);
            if ((frame.scan_code & 0x80) == 0) {
                state = SHIFT;
            }
        }
    } else {
        static uint16_t strobe_time = 0;
        uint16_t now = timer_read();
        if (now - strobe_time > STROBE_PERIOD_MILLIS) {
            DATA_PORT &= ~DATA_MASK;
            wait_us(STROBE_TIME_MICROS);
            DATA_PORT |= DATA_MASK;
            strobe_time = now;
        }
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
