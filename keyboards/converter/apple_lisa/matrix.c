
#include <avr/io.h>
#include <avr/interrupt.h>
#include "debug.h"
#include "matrix.h"
#include "print.h"
#include "timer.h"
#include "wait.h"

// PD0 (Ring on jack)
#define DATA_PORT PORTD
#define DATA_PIN PIND
#define DATA_DDR DDRD
#define DATA_MASK 0x01

/*
 * The data line is pulled high when idle.
 * Once a millisecond, the computer polls the keyboard by pulling it down for 20us.
 * If the keyboard has a key-press, it responds around 40us after the falling edge of the sync pulse with a stop bit and eight data bits.
 * The stop bit is always low. The data bits are the complement of the scan code plus the high bit set for make (and clear for break).
 * The bits are transferred in the following order: 4,5,6,7,0,1,2,3 (sort of lsb-first, but high nibble first).
 * The bits are 16us wide, except for the make/break bit (the fourth one transferred), which is 30us.
 */

// Pull down data for this long.
#define SYNC_MICROS 20
// If key is pressed, keyboard should respond within 40us of sync, that is, after another 20us.
// Wait for a bit for line to stabilize, then wait a while for stop bit.
#define POST_SYNC_MICROS 10
#define MAX_WAIT_MICROS 100
// Past start bit to middle of first bit.
#define FIRST_BIT_MICROS 23
// Normal bit length.
#define SHORT_BIT_MICROS 15
// From middle of normal to middle of long or vice versa.
#define LONG_BIT_MICROS 23
// From middle of bit to end.
#define LAST_BIT_MICROS 8

static uint8_t poll(void) {
    // Don't poll more than once in the same couple milliseconds.
    static uint16_t last_poll_millis = 0;
    uint16_t now_millis = timer_read();
    if (last_poll_millis == now_millis || last_poll_millis + 1 == now_millis)
        return 0;
    last_poll_millis = now_millis;

    cli();

    DATA_DDR |= DATA_MASK;        // Output
    DATA_PORT &= ~DATA_MASK;      // Low
    wait_us(SYNC_MICROS);
    DATA_DDR &= ~DATA_MASK;       // Input
    DATA_PORT |= DATA_MASK;       // Pull-up
    wait_us(POST_SYNC_MICROS);

    // Don't have a microsecond timer, so just count down (about 8 16MHz cycles / 500ns per loop).
    uint32_t counter = MAX_WAIT_MICROS * 2UL;
    while (DATA_PIN & DATA_MASK) {       // Wait for start bit
        if (--counter == 0) {
            sei();
            return 0;
        }
    }

    uint8_t result = 0;

    wait_us(FIRST_BIT_MICROS);
    if (DATA_PIN & DATA_MASK) result |= 0x10;
    wait_us(SHORT_BIT_MICROS);
    if (DATA_PIN & DATA_MASK) result |= 0x20;
    wait_us(SHORT_BIT_MICROS);
    if (DATA_PIN & DATA_MASK) result |= 0x40;
    wait_us(LONG_BIT_MICROS);
    if (DATA_PIN & DATA_MASK) result |= 0x80;
    wait_us(LONG_BIT_MICROS);
    if (DATA_PIN & DATA_MASK) result |= 0x01;
    wait_us(SHORT_BIT_MICROS);
    if (DATA_PIN & DATA_MASK) result |= 0x02;
    wait_us(SHORT_BIT_MICROS);
    if (DATA_PIN & DATA_MASK) result |= 0x04;
    wait_us(SHORT_BIT_MICROS);
    if (DATA_PIN & DATA_MASK) result |= 0x08;
    wait_us(LAST_BIT_MICROS);

    sei();
    return ~result;
}

static matrix_row_t matrix[MATRIX_ROWS];

inline
static void register_key(uint8_t key) {
    uint8_t col, row;
    col = key & 0x07;
    row = (key >> 3) & 0x0F;
    if (key & 0x80) {
        matrix[row] |=  (1 << col);
    } else {
        matrix[row] &= ~(1 << col);
    }
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
    for (uint8_t i=0; i < MATRIX_ROWS; i++) matrix[i] = 0x00;

    matrix_init_quantum();
}

uint8_t matrix_scan(void) {
    uint8_t code = poll();
    if (code == 0) return 0;

    dprintf("%02X\n", code);

    register_key(code);

    matrix_scan_quantum();
    return 1;
}

void matrix_print(void) {
    print("\nr/c 01234567\n");
    for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
        print_hex8(row); print(": ");
        print_bin_reverse8(matrix_get_row(row));
        print("\n");
    }
}

inline
matrix_row_t matrix_get_row(uint8_t row) {
    return matrix[row];
}
