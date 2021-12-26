
#include "debug.h"
#include "matrix.h"
#include "print.h"
#include "quantum.h"
#include "timer.h"

// In PC/AT mode, pin 1 is clock, pin 2 is data, and pin 3 is reset.
// For Soarer's clock is PD1, data is PD0, and reset is PB7.
// In ADDS mode, pin 1 is the only signal and pin 2 is held low.
// Keep signal at PD1.

#define DATA_PORT PORTD
#define DATA_PIN PIND
#define DATA_DDR DDRD
#define SIGNAL_MASK (1 << 1)
#define LED_MASK (1 << 6)
#define STROBE_INTERVAL_MS 5
#define STROBE_WIDTH_US 100

static enum {
    IDLE, STROBE, RECEIVING, RECEIVED, PROCESSED, ERROR
} state = IDLE;

static uint8_t receive_byte;
static uint8_t receive_bit_count;
static uint16_t receive_bit_start;
static uint16_t error_data;

ISR(INT1_vect) {
    bool pin_state = (DATA_PIN & SIGNAL_MASK) != 0;
    uint16_t count = TCNT3;
    if (state == RECEIVING) {
        if (pin_state) {
            uint16_t width = count - receive_bit_start;
            uint8_t bit;
            if (width >= 5 && width <= 9) {
                bit = 0;        // Short, nominal 28us = 7.
            } else if (width >= 30 && width <= 40) {
                bit = 0x80;     // Long, nominal 142us = 35.5.
            } else {
                error_data = width;
                state = ERROR;
                DATA_PORT |= LED_MASK;
                return;
            }
            // MSB first; somewhat arbitrary but some codes are ASCII this way.
            receive_byte = (receive_byte >> 1) | bit;
            receive_bit_count++;
            if (receive_bit_count == 8) {
                state = RECEIVED;
            }
        } else {
            receive_bit_start = count;
        }
    }
}

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

void matrix_init(void) {
    for (uint8_t i = 0; i < MATRIX_ROWS; i++) matrix[i] = 0;

    DATA_PORT |= SIGNAL_MASK;   // Enable pullup
    DATA_DDR |= LED_MASK;

    // Interrupt 1 on either edge.
    EIMSK |= _BV(INT1);
    EICRA |= _BV(ISC10);

#if F_CPU != 16000000
#error Wrong prescalar for clock rate
#endif

    // Configure TCNT3 to count once every 4us.
    TCCR3A = 0;                     // Normal
    TCCR3B = _BV(CS31) | _BV(CS30); // Prescalar = 64

    matrix_init_quantum();
}

uint8_t matrix_scan(void) {
    static bool clear_needed = false;
    if (clear_needed) {
        // Only four keys send break codes; the rest need to be cleared automatically.
        for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
            if (row == 0) {
                matrix[row] &= (1 << 2) | (1 << 4) | (1 << 5);
            } else if (row == 1) {
                matrix[row] &= (1 << 0xB);
            } else {
                matrix[row] = 0;
            }
        }
        clear_needed = false;
    }

    if (state == RECEIVED) {
        dprintf("%02X\n", receive_byte);
        if (receive_byte >= 0x70) {
            dprintf("out of range\n");
        } else if (receive_byte >= 0x64) {
            // Break code; clear corresponding make code.
            uint8_t make_code;
            switch (receive_byte) {
            case 0x64:
                make_code = 0x1B; // ESC
                break;
            case 0x65:
                make_code = 0x02; // DEL
                break;
            case 0x66:
                make_code = 0x04; // CTRL
                break;
            case 0x67:
                make_code = 0x05; // SHIFT
                break;
            default:
                make_code = 0x00;
                break;
            }
            uint8_t row = make_code >> 4;
            uint8_t col = make_code & 0x0F;
            matrix[row] &= ~(1 << col);
        } else {
            uint8_t row = receive_byte >> 4;
            uint8_t col = receive_byte & 0x0F;
            matrix[row] |= (1 << col);
            clear_needed = true;
        }
        state = PROCESSED;
    } else if (state == ERROR) {
        dprintf("error: %d\n", error_data);
        DATA_PORT &= ~LED_MASK;
        state = IDLE;
    }

    static uint16_t last_time = 0;
    uint16_t now = timer_read();
    if (now - last_time > STROBE_INTERVAL_MS) {
        state = STROBE;
        DATA_DDR |= SIGNAL_MASK;
        DATA_PORT &= ~SIGNAL_MASK;
        wait_us(STROBE_WIDTH_US);
        DATA_PORT |= SIGNAL_MASK;
        DATA_DDR &= ~SIGNAL_MASK;
        receive_byte = 0;
        receive_bit_count = 0;
        state = RECEIVING;
        last_time = now;
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
