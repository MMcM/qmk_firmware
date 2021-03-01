
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

typedef enum {
    DATA, SWITCH, PAGE_BOOK, DBG
} strobe_t;

typedef struct {
    strobe_t strobe;
    uint8_t data;
} queue_entry_t;
#define QUEUE_SIZE 16
static queue_entry_t char_queue[QUEUE_SIZE];
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

static inline queue_entry_t queue_remove(void) {
    queue_entry_t entry = char_queue[char_queue_out];
    char_queue_out = (char_queue_out + 1) % QUEUE_SIZE;
    return entry;
}

static inline void queue_add(strobe_t strobe, uint8_t data) {
    char_queue[char_queue_in].strobe = strobe;
    char_queue[char_queue_in].data = data;
    char_queue_in = (char_queue_in + 1) % QUEUE_SIZE;
}

#define DATA_DDR DDRB
#define DATA_PIN PINB

#define STROBE_DDR DDRD
#define STROBE_PIN PIND
#define STROBE_PORT PORTD
#define STROBE_DATA (1 << 0)
#define STROBE_SWITCH (1 << 1)
#define STROBE_PAGE_BOOK (1 << 2)
#define STROBE_DBG (1 << 3)
#define STROBE_MASK (STROBE_DATA|STROBE_SWITCH|STROBE_PAGE_BOOK|STROBE_DBG)

ISR(INT0_vect) {
    if (!queue_is_full()) {
        queue_add(DATA, DATA_PIN);
    }
}

ISR(INT1_vect) {
    if (!queue_is_full()) {
        queue_add(SWITCH, DATA_PIN);
    }
}

ISR(INT2_vect) {
    if (!queue_is_full()) {
        queue_add(PAGE_BOOK, DATA_PIN);
    }
}

ISR(INT3_vect) {
    if (!queue_is_full()) {
        queue_add(DBG, 0);
    }
}

void matrix_init(void) {
    for (uint8_t i = 0; i < MATRIX_ROWS; i++) matrix[i] = 0;
  
    DATA_DDR = 0;
    STROBE_DDR &= ~STROBE_MASK;
    STROBE_PORT |= STROBE_MASK;   // Open collector: enable pull-ups.

    // Interrupts 0-3 on falling edges.
    EIMSK |= (1 << INT0) | (1 << INT1) | (1 << INT2) | (1 << INT3);
    EICRA |= (1 << ISC01) | (1 << ISC11) | (1 << ISC11) | (1 << ISC11);

    matrix_init_quantum();
}

uint8_t matrix_scan(void) {
    static enum { SCAN, CODE, SHIFT, SHIFTED, ALL_UP } state = SCAN;
    static uint16_t shifts;
    static uint8_t code;

    if (state == ALL_UP) {
        // There are no up transitions, so clear everything between codes.
        for (uint8_t i = 0; i < MATRIX_ROWS; i++) matrix[i] = 0;
        state = SCAN;
    } else if (state == SHIFT) {
        matrix[0] = shifts;
        state = SHIFTED;
    } else if (state == SHIFTED) {
        uint8_t col = code & 0x0F;
        uint8_t row = (code >> 4) & 0x0F;
        matrix[row] |= (1 << col);
        state = ALL_UP;
    } else if (!queue_is_empty()) {
        queue_entry_t entry = queue_remove();
        if (debug_enable) {
            const char *strobe;
            switch (entry.strobe) {
            case DATA:
                strobe = "DSTB";
                break;
            case SWITCH:
                strobe = "SWSTB";
                break;
            case PAGE_BOOK:
                strobe = "PBSTB";
                break;
            case DBG:
                strobe = "DBG";
                break;
            default:
                strobe = "???";
                break;
            }
            xprintf("%s %02X\n", strobe, entry.data);
        }
        switch (entry.strobe) {
        case DATA:
            if (state == CODE && entry.data == 0) {
                // Some action keys send this right away; maybe to inhibit auto-repeat?
                break;
            }
            code = entry.data;
            state = CODE;
            break;
        case SWITCH:
            shifts = (shifts & 0xFF00) | entry.data;
            break;
        case PAGE_BOOK:
            shifts = (shifts & 0x00FF) | (entry.data << 8);
            if (state == CODE) {
                state = SHIFT;          // Only do this once per code, even if strobed multiple times.
            }
            break;
        case DBG:
            debug_enable = true;
            break;
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
