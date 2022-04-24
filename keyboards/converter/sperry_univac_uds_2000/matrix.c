
#include "debug.h"
#include "matrix.h"
#include "print.h"
#include "quantum.h"

#include <avr/io.h>

#define QUEUE_SIZE 16
static uint8_t char_queue[QUEUE_SIZE];
static uint8_t char_queue_in, char_queue_out;

static inline void queue_clear(void) {
    char_queue_in = char_queue_out = 0;
}

static inline bool queue_is_empty(void) {
    return (char_queue_in == char_queue_out);
}

static inline bool queue_is_full(void) {
    // One entry wasted to be able to check this easily.
    return (((char_queue_in + 1) % QUEUE_SIZE) == char_queue_out);
}

static inline uint8_t queue_remove(void) {
    uint8_t code = char_queue[char_queue_out];
    char_queue_out = (char_queue_out + 1) % QUEUE_SIZE;
    return code;
}

static inline void queue_add(uint8_t code) {
    char_queue[char_queue_in] = code;
    char_queue_in = (char_queue_in + 1) % QUEUE_SIZE;
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

#define DATA_DDR DDRB
#define DATA_PIN PINB
#define DATA_PORT PORTB
#define DATA_MASK 0xF7
#define DATA_SHIFT 1

#define CONTROL_DDR DDRD
#define CONTROL_PIN PIND
#define CONTROL_PORT PORTD
#define CLEAR_MASK (1 << 0)
#define STROBE_MASK (1 << 1)

ISR(INT1_vect) {
    uint8_t scan_code = DATA_PIN >> DATA_SHIFT;
    if (!queue_is_full()) {
        queue_add(scan_code);
    }
}

void matrix_init(void) {
    for (uint8_t row = 0; row < MATRIX_ROWS; row++) matrix[row] = 0;

    DATA_DDR = 0x00;
    DATA_PORT = DATA_MASK;

    CONTROL_DDR |= CLEAR_MASK;
    CONTROL_PORT |= (CLEAR_MASK | STROBE_MASK);

    // Interrupt 1 on rising edge.
    EIMSK = _BV(INT1);
    EICRA = _BV(ISC11) | _BV(ISC10);

    matrix_init_quantum();
}

uint8_t matrix_scan(void) {
    debug_enable = true;

    // Only the 5 keys in these 2 rows send up transitions.
    for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
        if (row != 6 && row != 7) {
            matrix[row] = 0;
        }
    }

    if (!queue_is_empty()) {
        uint8_t code = queue_remove();
        dprintf("%02X\n", code);
        uint8_t row = code & 0xF;
        uint8_t col = code >> 4;
        if (row == 6 || row == 7) {
            if (col & 4) {
                matrix[row] |= (1 << (col & ~4));
            } else {
                matrix[row] &= ~(1 << col);
            }
        } else if (row > 7) {
            if (row > 13) {
                matrix[row - 6] |= (1 << col);
            }
        } else {
          matrix[row] |= (1 << col);
        }
    }

    matrix_scan_quantum();
    return 1;
}

void matrix_print(void) {
    print("\nr/c 01234567\n");
    for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
        print_hex8(row > 7 ? row + 6 : row); print(": ");
        print_bin_reverse8(matrix_get_row(row));
        print("\n");
    }
}

inline
matrix_row_t matrix_get_row(uint8_t row) {
    return matrix[row];
}
