
#include "debug.h"
#include "matrix.h"
#include "print.h"
#include "ps2.h"
#include "timer.h"

// Note that some space is saved by knowing that there are no overlaps between E0 and E1 prefixed codes or between 8x and E0x.

static matrix_row_t matrix[MATRIX_ROWS];
#define ROW(eprefix, code) ((code>>4) | (eprefix ? 8 : 0))
#define COL(code) (code & 0x0F)

inline
static void matrix_make(bool eprefix, uint16_t code) {
  matrix[ROW(eprefix, code)] |= ((matrix_row_t)1 << COL(code));
}

inline
static void matrix_break(bool eprefix, uint16_t code) {
    matrix[ROW(eprefix, code)] &= ~((matrix_row_t)1 << COL(code));
}

inline
static void matrix_clear(void) {
    for (uint8_t i = 0; i < MATRIX_ROWS; i++) matrix[i] = 0;
}

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
    matrix_clear();

    ps2_host_init();

    matrix_init_quantum();
}

typedef enum {
    NORMAL,
    _F0,
    _E0,
    _E0_F0,
    _E1,
    _E1_F0
} state_t;

uint8_t matrix_scan(void) {
    static state_t state = NORMAL;

    uint8_t code = ps2_host_recv();

    bool sent = false;
    if (!code) return 0;

    switch (state) {
    case NORMAL:
        switch (code) {
        case 0xF0:
            state = _F0;
            break;
        case 0xE0:
            state = _E0;
            break;
        case 0xE1:
            state = _E1;
            break;
        default:
            matrix_make(false, code);
            sent = true;
            break;
        }
        break;
    case _F0:
        matrix_break(false, code);
        sent = true;
        break;
    case _E0:
        switch (code) {
        case 0xF0:
            state = _E0_F0;
            break;
        case 0x12:                  // Sent when Num Lock enabled?
            sent = true;
            break;
        default:
            matrix_make(true, code);
            sent = true;
            break;
        }
        break;
    case _E0_F0:
        switch (code) {
        case 0x12:
            sent = true;
            break;
        default:
            matrix_break(true, code);
            sent = true;
            break;
        }
        break;
    case _E1:
        switch (code) {
        case 0xF0:
            state = _E1_F0;
            break;
        case 0x14:                  // Pause is E1,14,77
            break;
        default:
            matrix_make(true, code);
            sent = true;
            break;
        }
        break;
    case _E1_F0:
        switch (code) {
        case 0x14:
            state = _E1;
            break;
        default:
            matrix_break(true, code);
            sent = true;
            break;
        }
        break;
    }
    if (sent) {
        state = NORMAL;
    }

    dprintf("r%02X%c", code, sent ? '\n' : ' ');
    matrix_scan_quantum();
    return 1;
}

void matrix_print(void) {
    print("\nr/c 0123456789ABCDEF");
    for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
        xprintf("%c%X: ", row < 8 ? ' ' : 'E', row & 0x07);
        print_bin_reverse16(matrix_get_row(row));
        print("\n");
    }
}

inline
matrix_row_t matrix_get_row(uint8_t row) {
    return matrix[row];
}
