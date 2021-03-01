
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

/*
 *
 * 
 */
static matrix_row_t matrix[MATRIX_ROWS];

inline
matrix_row_t matrix_get_row(uint8_t row) {
    return matrix[row];
}

void matrix_init(void) {
    for (uint8_t i = 0; i < MATRIX_ROWS; i++) matrix[i] = 0x00;

    BUS_DDR = BUS_PORT = 0x00;    // Floating.

    BADDR_DDR |= BADDR_MASK;      // Output, low.
    BADDR_PORT &= ~BADDR_MASK;

    READ_DDR |= READ_MASK;        // Output, high.
    READ_PORT |= READ_MASK;

    COL_OUT_DDR |= COL_OUT_MASK;  // Output, low.
    COL_OUT_PORT |= COL_OUT_MASK;

    LED_OUT_DDR |= LED_OUT_MASK;  // Output, low.
    LED_OUT_PORT |= LED_OUT_MASK;

    RESET_DDR &= ~RESET_MASK;     // Input, pullup.
    RESET_PORT |= RESET_MASK;

    matrix_init_quantum();
}

uint8_t matrix_scan(void) {
    // QMK thinks of 14 rows by 8 columns. HP thinks of 14 columns of 8 keys each.
    static uint8_t position = 0;

    // Will need 200ns to get through column decoders, so do this early on.
    BADDR_PORT = (BADDR_PORT & ~BADDR_MASK) | position;

    if (position < 14) {
        BUS_DDR = 0xFF;
        BUS_PORT = matrix[position];
        COL_OUT_PORT |= COL_OUT_MASK;
        asm("nop\n\t"); // 7475 latch needs 20ns; one cycle at 16MHz is 62.5ns.
        COL_OUT_PORT &= ~COL_OUT_MASK;
        BUS_DDR = BUS_PORT = 0x00;
        READ_PORT &= ~READ_MASK;
        wait_us(5);               // Too short and neighboring columns interfere.
        uint8_t keys = ~BUS_PIN;
        READ_PORT |= READ_MASK;
        matrix[position] = keys;
    } else if (position == 15) {
        static uint8_t last_switches = 1; // Impossible value; bit 0 isn't connected.
        uint8_t switches = ~BUS_PIN;
        if (last_switches != switches) {
            if (debug_enable) {
                if (switches & (1<<7)) { // Schematic seems to have this backwards.
                    print("FULL");
                } else {
                    print("HALF");
                }
                print(", ");
                if (switches & (1<<4)) {
                    print("EVEN");
                }
                else if (switches & (1<<5)) {
                    print("NONE");
                }
                else {
                    print("ODD");
                }
                print(", ");
                switch (switches & (7<<1)) {
                case 0<<1:
                    print("EXT");
                    break;
                case 1<<1:
                    print("110");
                    break;
                case 2<<1:
                    print("150");
                    break;
                case 3<<1:
                    print("300");
                    break;
                case 4<<1:
                    print("1200");
                    break;
                case 5<<1:
                    print("2400");
                    break;
                case 6<<1:
                    print("4800");
                    break;
                case 7<<1:
                    print("9600");
                    break;
                default:
                    break;
                }
                print("\n");
            }
            // TODO: What could these usefully do?
            last_switches = switches;
        }
    } else {
        // In case pushed while booted, don't loop resetting.
        static bool reset_ever_up = false;
        bool reset_down = (RESET_PIN & RESET_MASK) == 0;
        if (!reset_down) {
            reset_ever_up = true;
        } else if (reset_ever_up) {
            reset_keyboard();
        }
    }
    wait_us(60);           // Complete scan around once a millisecond.
    position = (position + 1) % 16;
  
    matrix_scan_quantum();
    return 1;
}

void matrix_print(void) {
    print("\nr/c  01234567\n");
    for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
        // HP documentation uses octal.
        xprintf("%02o: ", row);
        print_bin_reverse8(matrix_get_row(row));
        print("\n");
    }
}
