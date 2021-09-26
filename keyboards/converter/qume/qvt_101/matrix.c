
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
#define RX_MASK (1 << 2)
#define TX_MASK (1 << 3)

// The MCS-48 transmit loop is 7 cycles long. At 6MHz, that gives a width of 17.5µs, or around 57kbps.
// For a 16MHz AVR, that is 280 instruction cycles.

static int16_t read_byte(void) {
    if ((DATA_PIN & RX_MASK) == 0) {
        return -1;              // Idle low (there is an inverter)
    }
    while ((DATA_PIN & RX_MASK) != 0) {
        // Wait for start bit.
    }
    __builtin_avr_delay_cycles(140); // To center of start bit
    if ((DATA_PIN & RX_MASK) != 0) {
        return -2;
    }
    uint8_t bits = 0;
    uint8_t mask = 1;
    while (true) {
        __builtin_avr_delay_cycles(275);
        if (mask == 0) break;
        if ((DATA_PIN & RX_MASK) == 0) {
            bits |= mask;
        }
        mask <<= 1;
    }
    if ((DATA_PIN & RX_MASK) != 0) {
        return -3;
    }
    return bits;
}

void matrix_init(void) {
    for (uint8_t i = 0; i < MATRIX_ROWS; i++) matrix[i] = 0;

    DATA_DDR |= TX_MASK;
    DATA_PORT |= RX_MASK;       // Enable pullup

    matrix_init_quantum();
}

uint8_t matrix_scan(void) {
    static enum { SCAN, SHIFTED, ALL_UP } state = SCAN;
    static uint8_t shifts;
    static uint8_t code;

    if (state == ALL_UP) {
        // There are no up transitions, so clear everything between codes.
        for (uint8_t i = 0; i < MATRIX_ROWS; i++) matrix[i] = 0;
        state = SCAN;
    } else if (state == SHIFTED) {
        uint8_t col = code & 0x0F;
        uint8_t row = (code >> 4) & 0x07;
        matrix[row] |= (1 << col);
        state = ALL_UP;
    } else {
        int16_t data2 = read_byte();
        if (data2 >= 0) {
            uint8_t data = data2 & 0xFF;
            dprintf("%02X%c", data, data & 0x80 ? '\n' : ' ');
            if ((data & 0x80) == 0) {
                code = data;
            } else {
                shifts = (data >> 4) & 0x03;
                switch (data & 0x0F) {
                    // 0 - auto-repeat
                    // 1 - kbd init
                case 0x02:
                    // Caps Lock pressed; no code byte preceding.
                    matrix[8] = shifts | (1 << 2);
                    state = ALL_UP;
                    break;
                case 0x04:
                    // Initial key press; code byte precedes.
                    matrix[8] = shifts;
                    state = SHIFTED;
                    break;
                default:
                    break;
                }
            }
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
