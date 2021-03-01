
#include <avr/io.h>
#include <avr/interrupt.h>
#include "debug.h"
#include "matrix.h"
#include "print.h"
#include "quantum.h"

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

// This does debounce, but also accounts for the slow Q1 inverter in the extended keyboard.
static bool key_pressed(void) {
    bool last_state = readPin(KEYACT_PIN);
    while (true) {
        wait_us(50);
        bool state = readPin(KEYACT_PIN);
        if (last_state == state) {
            return !state;
        }
        last_state = state;
    }
}

void matrix_init(void) {
    for (uint8_t i = 0; i < MATRIX_ROWS; i++) matrix[i] = 0x00;

#ifdef __AVR__
    ADDRESS_DDR |= ADDRESS_MASK;
    ADDRESS_PORT |= ADDRESS_MASK;
#else
    setPinOutput(KEYA0_PIN);
    setPinOutput(KEYA1_PIN);
    setPinOutput(KEYA2_PIN);
    setPinOutput(KEYA3_PIN);
    setPinOutput(KEYA4_PIN);
    setPinOutput(KEYA5_PIN);
    setPinOutput(KEYA6_PIN);
#endif

    setPinInputHigh(KEYACT_PIN);

    matrix_init_quantum();
}

uint8_t matrix_scan(void) {
    static uint8_t address = 0;
  
#ifdef __AVR__
    ADDRESS_PORT = address;
#else
    writePin(KEYA0_PIN, (address & (1 << 0)) != 0);
    writePin(KEYA1_PIN, (address & (1 << 1)) != 0);
    writePin(KEYA2_PIN, (address & (1 << 2)) != 0);
    writePin(KEYA3_PIN, (address & (1 << 3)) != 0);
    writePin(KEYA4_PIN, (address & (1 << 4)) != 0);
    writePin(KEYA5_PIN, (address & (1 << 5)) != 0);
    writePin(KEYA6_PIN, (address & (1 << 6)) != 0);
#endif

    bool pressed = key_pressed();
    uint16_t row = matrix[address & 7];
    uint16_t col_bit = 1 << (address >> 3);
    if (pressed != ((row & col_bit) != 0)) {
        matrix[address & 7] ^= col_bit;
    }
  
    address = (address + 1) & ADDRESS_MASK;
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
