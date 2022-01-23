
#include "debug.h"
#include "matrix.h"
#include "print.h"
#include "quantum.h"

#define SCAN_PORT PORTB
#define SCAN_PIN PINB

#define KBD_PORT PORTD
#define KBD_PIN PIND
#define KBD_DDR DDRD
#define KBD_DATA (1 << 0)
#define KBD_DELAY (1 << 1)
#define KBD_POR (1 << 2)
#define KBD_CLICKER (1 << 3)

#ifndef CLICKER_ENABLE
#define CLICKER_ENABLE 1
#endif
#if CLICKER_ENABLE
#define CLICKER_INTERVAL 50
#endif

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
    for (uint8_t row = 0; row < MATRIX_ROWS; row++) matrix[row] = 0;

    KBD_DDR |= KBD_DELAY | KBD_POR; // Outputs (also starts reset)
    KBD_PORT |= KBD_DATA;           // Enable pullup

    // The IBM 5251 waits .5s according to the manual.
    // There is no need for that long here; all it does is reset the MCU and preset the flip-flop
    wait_us(10);
    KBD_PORT |= KBD_POR;

#if CLICKER_ENABLE
    KBD_DDR |= KBD_CLICKER;
    KBD_PORT |= KBD_CLICKER;    // Idle high.
#endif

    matrix_init_quantum();
}

uint8_t matrix_scan(void) {
#if CLICKER_ENABLE
    static bool clicker_on = false;
    static uint16_t clicker_on_time;

    if (clicker_on && timer_read() - clicker_on_time > CLICKER_INTERVAL) {
        KBD_PORT |= KBD_CLICKER;    // Deactivate
        clicker_on = false;
    }
#endif

    // Only the three shift keys have break codes; clear everything else.
    for (uint8_t row = 0; row < MATRIX_ROWS; row++) matrix[row] &= (1 << 5);
    
    // This could be done with interrupts, but with the delay signal that isn't necessary.
    // The small delay seems to be needed to avoid a very short secondary pulse that would cause a duplicate scan code.
    if ((KBD_PIN & KBD_DATA) == 0) {
        KBD_PORT |= KBD_DELAY;
        uint8_t scan_code = SCAN_PIN;
        wait_us(1);
        KBD_PORT &= ~KBD_DELAY;
        while ((KBD_PIN & KBD_DATA) == 0);

        dprintf("%02X\n", scan_code);

        uint8_t row = scan_code >> 4;
        uint8_t col = scan_code & 0x0F;
        if (col == 4) {
            // All the break codes are x4 for make x5.
            matrix[row] &= ~(1 << (col+1));
        } else {
            matrix[row] |= 1 << col;
        }

#if CLICKER_ENABLE
        // Do not click shift or break.
        if (col != 4 && col != 5 && !clicker_on) {
            KBD_PORT &= ~KBD_CLICKER;    // Activate
            clicker_on = true;
            clicker_on_time = timer_read();
        }
#endif
    }

    matrix_scan_quantum();
    return 1;
}

void matrix_print(void) {
    print("\nr/c 0123456789ABCDEF\n");
    for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
        print_hex16(row); print(": ");
        print_bin_reverse16(matrix_get_row(row));
        print("\n");
    }
}

inline
matrix_row_t matrix_get_row(uint8_t row) {
    return matrix[row];
}
