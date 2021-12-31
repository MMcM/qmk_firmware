
#include <avr/io.h>
#include <avr/interrupt.h>
#include "debug.h"
#include "matrix.h"
#include "print.h"
#include "timer.h"

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

#define QUEUE_SIZE 16
static uint8_t code_queue[QUEUE_SIZE];
static uint8_t code_queue_in, code_queue_out;

static inline void queue_clear(void) {
    code_queue_in = code_queue_out = 0;
}

static inline bool queue_is_empty(void) {
    return (code_queue_in == code_queue_out);
}

static inline bool queue_is_full(void) {
    // One entry wasted to be able to check this easily.
    return (((code_queue_in + 1) % QUEUE_SIZE) == code_queue_out);
}

static inline uint8_t queue_remove(void) {
    uint8_t entry = code_queue[code_queue_out];
    code_queue_out = (code_queue_out + 1) % QUEUE_SIZE;
    return entry;
}

static inline void queue_add(uint8_t entry) {
    code_queue[code_queue_in] = entry;
    code_queue_in = (code_queue_in + 1) % QUEUE_SIZE;
}

#define STROBE_PORT PORTD
#define STROBE_PIN PIND
#define STROBE_MASK (1 << 0)
#define DATA_PIN PINB

ISR(INT0_vect) {
    uint8_t data = DATA_PIN;
    if (!queue_is_full()) {
      queue_add(data);
    }
}

void matrix_init(void) {
    for (uint8_t i = 0; i < MATRIX_ROWS; i++) matrix[i] = 0x00;

    STROBE_PORT |= STROBE_MASK; // Enable pull-up.
  
    // Interrupt 0 on falling edge of strobe.
    EIMSK |= (1 << INT0);
    EICRA |= (1 << ISC01);

    matrix_init_quantum();
}

uint8_t matrix_scan(void) {
    static enum { IDLE, KEYBOARD_CODE, MOUSE_X, MOUSE_Y } state = IDLE;
    static uint16_t last_time = 0;
    static uint8_t cmd;
    
    uint16_t now = timer_read();
    if (queue_is_empty()) {
        if (state != IDLE && now - last_time > 10000) {
            dprintf("Timeout sync error\n");
            state = IDLE;
        }
    } else if (state == IDLE) {
        cmd = queue_remove();
        dprintf("%02X ", cmd);
        if (cmd & 0x80) {
            if (cmd & 0x08) {
                state = MOUSE_X;
            } else {
                state = KEYBOARD_CODE;
            }
            last_time = now;
        } else {
            dprintf("missing prefix\n");
        }
    } else if (state == KEYBOARD_CODE) {
        uint8_t code = queue_remove();
        dprintf("%02X\n", code);
        uint8_t row = code >> 4;
        uint8_t col = code & 0x0F;
        if (row < MATRIX_ROWS) {
            if (cmd & 0x40) {
                // Upstroke (break).
                matrix[row] &= ~(1 << col);
            } else {
                matrix[row] |= (1 << col);
            }
        }
        state = IDLE;
    } else if (state == MOUSE_X) {
        uint8_t x = queue_remove();
        dprintf("%02X ", x);
        state = MOUSE_Y;
        last_time = now;
    } else if (state == MOUSE_Y) {
        // Ignore mouse for now; not clear on some details.
        uint8_t y = queue_remove();
        dprintf("%02X\n", y);
        state = IDLE;
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
