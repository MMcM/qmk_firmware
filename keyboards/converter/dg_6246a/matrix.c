
#include <avr/io.h>
#include <avr/interrupt.h>
#include "debug.h"
#include "matrix.h"
#include "print.h"
#include "quantum.h"
#include "timer.h"

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

static matrix_row_t matrix[MATRIX_ROWS];

inline
matrix_row_t matrix_get_row(uint8_t row) {
    return matrix[row];
}

static enum {
    INVALID, IDLE, RECEIVING, SENDING
} state = INVALID;

uint8_t led_buzzer_state = 0;

static uint8_t data_in = 0;
static bool data_available = false;
static uint8_t data_out_position = 0;
static bool data_sent = false;

ISR(KBIRQ_VECT) {
    if (state != RECEIVING) {
        return;
    }
    bool rising = (DATA_PIN & KBIRQ_MASK) != 0;
    if (rising) {
        DATA_PORT |= SO_MASK;

        data_out_position = 7;
        state = SENDING;
    } else {
        DATA_PORT &= ~SO_MASK;

        data_available = true;
    }
}

ISR(SCLK_VECT) {
    if (state == INVALID) {
        // Prior to initial reset.
        return;
    }
    uint8_t pin_data = DATA_PIN;
    bool rising = (pin_data & SCLK_MASK) != 0;
    if (rising) {
        if (state == RECEIVING) {
            bool si = ((pin_data & SI_MASK) != 0);
            data_in = (data_in << 1) | (si ? 1 : 0);
        } else if (state == SENDING) {
            if (data_out_position == 0) {
                data_sent = true;
                state = IDLE;
            } else {
                data_out_position--;
            }
        }
    } else {
        if (state == IDLE) {
            state = RECEIVING;
        } else if (state == SENDING) {
            bool so = ((led_buzzer_state & (1 << data_out_position)) != 0);
            if (so) {
                DATA_PORT |= SO_MASK;
            } else {
                DATA_PORT &= ~SO_MASK;
            }
        }
    }
}

void matrix_init(void) {
    for (uint8_t i = 0; i < MATRIX_ROWS; i++) matrix[i] = 0x00;

    DATA_PORT |= SO_MASK;
    DATA_DDR |= SO_MASK;
    RESET_PORT |= RESET_MASK;
    RESET_DDR |= RESET_MASK;

    // Interrupts 0 and 1 on either edge.
    EIMSK |= (1 << INT0) | (1 << INT1);
    EICRA |= (1 << ISC00) | (1 << ISC10);

    matrix_init_quantum();
}

uint8_t matrix_scan(void) {
    static bool ident_received = false;
    uint16_t now = timer_read();
    static uint16_t last_receive_time = 0;
    if (now - last_receive_time > 1000) {
        dprintln("Reset");
        for (uint8_t i = 0; i < MATRIX_ROWS; i++) matrix[i] = 0x00;
        ident_received = false;
        state = IDLE;

        RESET_PORT &= ~RESET_MASK;
        wait_us(10);
        RESET_PORT |= RESET_MASK;

        last_receive_time = now;    // Just so don't reset all the time when unplugged.
    }
    if (data_available) {
        data_available = false;
        last_receive_time = now;

        if (!ident_received) {
          dprintf("Ident %02X\n", data_in);
          ident_received = true;
        } else if (data_in < 0x7F) {
          dprintf("%02X\n", data_in);
          uint8_t row = data_in >> 4;
          uint8_t col = data_in & 0x0F;
          matrix[row] ^= (1 << col);
        }
    }
    if (data_sent) {
        data_sent = false;
        wait_us(50);
        DATA_PORT |= SO_MASK;   // Back to idle.
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
