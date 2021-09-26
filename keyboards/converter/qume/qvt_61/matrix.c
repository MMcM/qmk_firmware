
#include "debug.h"
#include "matrix.h"
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

#define DATA_PORT PORTD
#define DATA_PIN PIND
#define DATA_DDR DDRD
#define SIGNAL_MASK (1 << 0)
#define STROBE_MASK (1 << 1)

#if 1
// Teensy
#define LED_PORT PORTD
#define LED_DDR DDRD
#define LED_MASK (1 << 6)
#else
// Arduino, Pro Micro, etc.
#define LED_PORT PORTC
#define LED_DDR DDRC
#define LED_MASK (1 << 7)
#endif

static enum {
    IDLE, STARTING, RECEIVING
} receive_state = IDLE;

ISR(INT0_vect) {
    if (receive_state != RECEIVING) {
        // Must see fall and then rise.
        // If the MCS-48 interrupt timing works out, this can all happen during the low strobe interval.
        bool state = (PIND & (1 << 0)) != 0;
        if (receive_state == IDLE) {
            if (!state) {
                receive_state = STARTING;
            }
        } else {
            if (state) {
                receive_state = RECEIVING;
                LED_PORT |= LED_MASK;
            }
        }
    }
}

static uint16_t timer_high = 0;

static inline uint32_t read_timer(void) {
    return ((uint32_t)timer_high << 16) | (uint32_t)TCNT3;
}

SIGNAL(TIMER3_OVF_vect) {
    timer_high++;
}

void matrix_init(void) {
    for (uint8_t i = 0; i < MATRIX_ROWS; i++) matrix[i] = 0;

    DATA_DDR |= STROBE_MASK;
    DATA_PORT |= SIGNAL_MASK;   // Enable pullup
    LED_DDR |= LED_MASK;
    LED_PORT &= ~LED_MASK;

    // Interrupt 0 on either edge.
    EIMSK |= _BV(INT0);
    EICRA |= _BV(ISC00);

    // Configure TCNT3 to count once every 16us. Strobe every 32 ticks or half a millisecond. About 1900 baud.
    TCCR3A = 0;                 // Normal
    TCCR3B = _BV(CS32);         // Prescalar = 256
    TIMSK3 |= _BV(TOIE3);       // Enable overflow interrupt

    matrix_init_quantum();
}

#define matrix_shifts matrix[MATRIX_ROWS - 1]
#define CAPS_SHIFT (1 << 0)
#define CTRL_SHIFT (1 << 1)
#define LEFT_SHIFT (1 << 2)
#define RIGHT_SHIFT (1 << 3)

static bool process_receive_byte(uint8_t data) {
    static bool receiving_shifts = false;
    bool non_shift_down = false;

    if ((data & 0x0F) == 0) {
        if (receiving_shifts) {
            matrix_shifts = data >> 4;
            receiving_shifts = false;
        } else {
            switch (data) {
            case 0x40:
                receiving_shifts = true;
                break;
            case 0x70:
                matrix_shifts |= CAPS_SHIFT; // Caps lock on
                matrix_shifts &= ~CTRL_SHIFT; // Ctrl up w/ caps
                break;
            case 0xB0:
                matrix_shifts |= CTRL_SHIFT; // Ctrl down
                break;
            case 0x30:
                matrix_shifts &= ~(CAPS_SHIFT | CTRL_SHIFT); // Caps lock off and/or ctrl up
                break;
            case 0xF0:
                matrix_shifts |= (CAPS_SHIFT | CTRL_SHIFT); // Ctrl down w/ caps
                break;
            case 0x50:
                matrix_shifts |= LEFT_SHIFT; // Left shift down
                break;
            case 0x90:
                matrix_shifts |= RIGHT_SHIFT; // Right shift down
                break;
            case 0xD0:
                matrix_shifts |= (LEFT_SHIFT | RIGHT_SHIFT); // Both shift down (magic key)
                break;
            case 0x10:
                matrix_shifts &= ~(LEFT_SHIFT | RIGHT_SHIFT); // Shift(s) up
                break;
            case 0xC0:          // Auto-repeat.
            default:
                break;
            }
        }
    } else if ((data & 1) == 0) {
        uint8_t row = (data >> 5) & 0x07;
        uint8_t col = (data >> 1) & 0x0F;
        matrix[row] |= (1 << col);
        non_shift_down = true;
    }

    dprintf("%02X%c", data, receiving_shifts ? ' ' : '\n');

    return non_shift_down;
}

#define STROBE_INTERVAL_TICKS 32
#define STROBE_WIDTH_USEC 64

uint8_t matrix_scan(void) {
    static bool all_up_needed = false;

    if (all_up_needed) {
        // No up transitions for regular keys.
        for (uint8_t i = 0; i < MATRIX_ROWS - 1; i++) matrix[i] = 0;
        all_up_needed = false;
    } else {
        static uint32_t last_strobe_time = 0;
        uint16_t now = read_timer();
        if (now - last_strobe_time > STROBE_INTERVAL_TICKS) {
            static uint8_t receive_count = 0;
            static uint8_t receive_byte = 0;
            if (receive_state == RECEIVING) {
                if ((DATA_PIN & SIGNAL_MASK) != 0) {
                    receive_byte |= (1 << receive_count);
                }
                receive_count++;
                if (receive_count >= 8) {
                    all_up_needed = process_receive_byte(receive_byte);
                    receive_state = IDLE;
                    receive_count = 0;
                    receive_byte = 0;
                    LED_PORT &= ~LED_MASK;
                }
            }
            DATA_PORT &= ~STROBE_MASK;
            wait_us(STROBE_WIDTH_USEC);
            DATA_PORT |= STROBE_MASK;
            last_strobe_time = now;
        }
    }

    matrix_scan_quantum();
    return 1;
}

void matrix_print(void) {
    print("\nr/c 0123456789ABCDEF");
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
