
#include "debug.h"
#include "matrix.h"
#include "print.h"
#include "quantum.h"

#include <avr/io.h>
#include "protocol/serial.h"

#ifdef NMB_TVI_RAW
#include "led.h"
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
    for (uint8_t i = 0; i < MATRIX_ROWS; i++) matrix[i] = 0;

    serial_init();
  
#ifdef RESET_PORT
    RESET_DDR &= ~RESET_MASK;     // Input, pullup.
    RESET_PORT |= RESET_MASK;
#endif

    matrix_init_quantum();
}

#ifndef NMB_TVI_RAW

static const uint8_t PROGMEM shifted[][2] = {
   { '\'', '"' },
   { ',', '<' },
   { '-', '_' },
   { '.', '>' },
   { '/', '?' },
   { '0', ')' },
   { '1', '!' },
   { '2', '@' },
   { '3', '#' },
   { '4', '$' },
   { '5', '%' },
   { '6', '^' },
   { '7', '&' },
   { '8', '*' },
   { '9', '(' },
   { ';', ':' },
   { '=', '+' },
   { '[', ']' },
   { '\\', '|' },
   { '`', '~' },
   { 'a', 'A' },
   { 'b', 'B' },
   { 'c', 'C' },
   { 'd', 'D' },
   { 'e', 'E' },
   { 'f', 'F' },
   { 'g', 'G' },
   { 'h', 'H' },
   { 'i', 'I' },
   { 'j', 'J' },
   { 'k', 'K' },
   { 'l', 'L' },
   { 'm', 'M' },
   { 'n', 'N' },
   { 'o', 'O' },
   { 'p', 'P' },
   { 'q', 'Q' },
   { 'r', 'R' },
   { 's', 'S' },
   { 't', 'T' },
   { 'u', 'U' },
   { 'v', 'V' },
   { 'w', 'W' },
   { 'x', 'X' },
   { 'y', 'Y' },
   { 'z', 'Z' },
   { '{', '}' },
   { 0x88, 0x80 },
   { 0x89, 0x81 },
   { 0x8A, 0x82 },
   { 0x8B, 0x83 },
   { 0x8C, 0x84 },
   { 0x8D, 0x85 },
   { 0x8E, 0x86 },
   { 0x8F, 0x87 },
   { 0x90, 0xA0 },
   { 0x91, 0xA1 },
   { 0x92, 0xA2 },
   { 0x93, 0xA3 },
   { 0x94, 0xA4 },
   { 0x95, 0xA5 },
   { 0x96, 0xA6 },
   { 0x97, 0xA7 },
   { 0x98, 0xA8 },
   { 0x99, 0xA9 },
   { 0x9A, 0xAA },
   { 0xD0, 0xE0 },
   { 0xD1, 0xE1 },
   { 0xD2, 0xE2 },
   { 0xD3, 0xE3 },
   { 0xD4, 0xE4 },
   { 0xD5, 0xE5 },
   { 0xD6, 0xE6 },
   { 0xD7, 0xE7 },
   { 0xD8, 0xE8 },
   { 0xD9, 0xE9 },
   { 0xDA, 0xEA },
   { 0xDB, 0xEB },
   { 0xDC, 0xEC },
   { 0xDD, 0xED },
   { 0xDE, 0xEE },
   { 0xDF, 0xEF },
   { 0xF0, 0xF1 },
   { 0xF2, 0xF3 },
   { 0xF4, 0xF5 },
   { 0xF6, 0xF7 },
   { 0xF8, 0xF9 },
   { 0xFB, 0xFC },
   { 0xFD, 0xFE },
};

static inline uint8_t unshift_code(uint8_t code) {
    if (code < 0x20) {
        code |= 0x40;
    }
    for (uint8_t i = 0; i < sizeof(shifted)/sizeof(shifted[0]); i++) {
        const uint8_t *p_shifted = shifted[i];
        if (code == pgm_read_byte(p_shifted + 1)) {
            return pgm_read_byte(p_shifted + 0);
        }
    }
    return code;
}

typedef enum {
    RECV_SHIFTS,
    RECV_CHAR,
    RETURN_SHIFTS,
    RETURN_CODE,
    ALL_UP
} state_t;

uint8_t matrix_scan(void) {
    debug_enable = true;

    static bool reset_ever_up = false;
    bool reset_down = (RESET_PIN & RESET_MASK) == 0;
    if (!reset_down) {
        reset_ever_up = true;
    } else if (reset_ever_up) {
        reset_keyboard();
    }

    static state_t state = RECV_SHIFTS;
    static uint8_t shifts = 0;
    static uint8_t code = 0;
    static uint16_t shifts_recv_time = 0;
    int16_t data;
    uint8_t row;
    uint8_t col;

    switch (state) {
    case RECV_SHIFTS:
        data = serial_recv2();
        if (data < 0) {
            break;
        }
        shifts = data & 0xFF;
        shifts_recv_time = timer_read();
        state = RECV_CHAR;
        break;

    case RECV_CHAR:
        if (timer_elapsed(shifts_recv_time) > 100) {
            state = RECV_SHIFTS;
            break;
        }
        data = serial_recv2();
        if (data < 0) {
            break;
        }
        code = data & 0xFF;
        dprintf("%02X %02X\n", shifts, code);
        if (shifts) {
            code = unshift_code(code);
        }
        state = RETURN_SHIFTS;
        break;

    case RETURN_SHIFTS:
        for (uint8_t i = 0; i < 8; i++) {
            // One bit at a time so protocol's breaking into separate reports works.
            if (((shifts & (1 << i)) != 0) && ((matrix[0] & (1 << i)) == 0)) {
                matrix[0] |= (1 << i);
                break;
            }
        }
        if (matrix[0] == shifts) {
            state = RETURN_CODE;
        }
        break;

    case RETURN_CODE:
        col = code & 0x0F;
        row = (code >> 4) & 0x0F;
        matrix[row] |= (1 << col);
        state = ALL_UP;
        break;

    case ALL_UP:
        // There are no up transitions, so clear everything between codes.
        for (uint8_t i = 0; i < MATRIX_ROWS; i++) matrix[i] = 0;
        state = RECV_SHIFTS;
        break;
    }

    matrix_scan_quantum();
    return 1;
}

#else

// Takes a following byte
#define CMD_5 0x05
// Set and clear a flag
#define CMD_6 0x06
#define CMD_7 0x07
// Responds with FF + some flags
#define CMD_ID 0x08             
// Two byte shift + ASCII
#define CMD_COOKED 0x09
// One byte make / break code
#define CMD_RAW 0xA
// + 3 low bits: middle one is Caps Lock
#define CMD_LEDS 0x10

// The keyboard is not always enabled for input, so to keep commands from getting lost, send them constantly.
#define XMIT_PERIOD_MILLIS 10

static uint8_t mode_cmd = CMD_RAW;
static uint8_t led_cmd = CMD_LEDS;

uint8_t matrix_scan(void) {
    debug_enable = true;

    int16_t data = serial_recv2();
    if (data >= 0) {
        uint8_t code = data & 0xFF;
        dprintf("%02X\n", code);
        // It is possible that the keyboard hasn't yet received the raw mode command.
        // It is better to lose characters than to generate garbage, so suppress 00 + xx, which means unshifted ASCII (or shift key press / release).
        static bool suppress = false;
        if (code == 0x00) {
            suppress = true;
        } else if (suppress) {
            suppress = false;
        } else {
            uint8_t row = (code >> 4) & 0x07;
            uint8_t col = code & 0x0F;
            if (code & 0x80) {
                matrix[row] &= ~(1 << col);
            } else {
                matrix[row] |= (1 << col);
            }
        }
    };

    static uint16_t last_xmit_time = 0;
    uint16_t now = timer_read();
    if (now - last_xmit_time > XMIT_PERIOD_MILLIS) {
        static bool mode = false;
        mode = !mode;
        serial_send(mode ? mode_cmd : led_cmd);
        last_xmit_time = now;
    }

    matrix_scan_quantum();
    return 1;
}

void led_set(uint8_t usb_led) {
    uint8_t cmd = CMD_LEDS;
    if (usb_led & (1<<USB_LED_CAPS_LOCK))
        cmd |= (1 << 1);
    led_cmd = cmd;
}

#endif

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
