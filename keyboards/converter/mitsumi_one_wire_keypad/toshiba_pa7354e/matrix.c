
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

#define DATA_DDR DDRD
#define DATA_MASK (1 << 2)
#define DATA_PIN PIND
#define DATA_PORT PORTD

#define POWER_DDR DDRD
#define POWER_MASK (1 << 3)
#define POWER_PORT PORTD
#define POWER_OFF_INTERVAL 20

static bool data_state;         // true = high
static uint16_t data_pulse_start;

// Begin decoding data pulses; should be just about to get pulled up, that is, still low.
static void data_pulse_reset(void) {
    data_state = false;
    data_pulse_start = TCNT3;
}

// 512us: wider than any actual pulse.
#define MAX_PULSE_WIDTH 32

// Wait for a change in the data line and return the width of the pulse, measured from the last change (versus when called).
static uint8_t next_data_pulse(void) {
    bool next_state = !data_state;
    while (true) {
        uint16_t time = TCNT3;
        bool state = (DATA_PIN & DATA_MASK) != 0;
        uint16_t delta = time - data_pulse_start;
        if (state == next_state) {
            data_state = next_state;
            data_pulse_start = time;
            return (uint8_t)delta;
        } else if (delta >= MAX_PULSE_WIDTH) {
            return (uint8_t)delta;
        }
    }
}

typedef enum { BIT_NONE, BIT_ZERO, BIT_ONE, BIT_LONG_ONE } bit_t;
static uint8_t low_pulse, high_pulse;

static bit_t next_data_bit(void) {
    low_pulse = next_data_pulse();
    if (low_pulse >= 5 && low_pulse <= 7) { // ~100us
        high_pulse = next_data_pulse();
        if (high_pulse >= 18 && high_pulse <= 20) { // ~300us
            return BIT_ONE;
        }
        if (high_pulse >= MAX_PULSE_WIDTH) {
            return BIT_LONG_ONE;      // Stays high because keypad is done.
        }
    } else if (low_pulse >= 15 && low_pulse <= 16) { // ~250us
        high_pulse = next_data_pulse();
        if (high_pulse >= 9 && high_pulse <= 10) { // ~150us
            return BIT_ZERO;
        }
    } else {
        high_pulse = 0;             // For debugging.
    }
    return BIT_NONE;
}

static void poll(void) {
  //  debug_enable = true;

  data_pulse_reset();

  uint8_t pulse = next_data_pulse();
  if (pulse > 1) {
    // Still low; connector might be shorted.
    dprint("No pulse start -- shorted?\n");
    return;
  }
  
  pulse = next_data_pulse();
  if (pulse < 6 || pulse > 8) {
    // If no keypad connected, will stay high too long.
    dprint("No pulse -- disconnected?\n");
    return;
  }

  bit_t bit = next_data_bit();
  if (bit != BIT_ZERO) {
    // BIT[_LONG]_ONE is the normal idle response.
    if (bit == BIT_NONE) {
      dprintf("Unrecognized initial bit: %d %d.\n", low_pulse, high_pulse);
    }
    return;
  }
  
  uint8_t scan_code = 0;
  for (uint8_t i = 0; i < 8; i++) {
    bit = next_data_bit();
    if (bit == BIT_ONE) {
      scan_code |= 1 << i;
    } else if (bit != BIT_ZERO) {
      dprintf("Unrecognized bit %d: %d %d.\n", i, low_pulse, high_pulse);
      return;
    }
  }

  dprintf("Scan code: %02X\n", scan_code);

  // Scan codes are the same as XT. / and Enter have a prefix to distinguish from normal keys; we just ignore it.
  if (scan_code == 0xE0) {
    return;
  }

    uint8_t col = scan_code & 0x0F;
    uint8_t row = (scan_code >> 4) & 0x07;
    if ((scan_code & 0x80) != 0) { // Break mask.
      matrix[row] &= ~(1 << col);
    } else {
      matrix[row] |= (1 << col);
    }
}

void matrix_init(void) {
  for (uint8_t i = 0; i < MATRIX_ROWS; i++) matrix[i] = 0;

  POWER_DDR |= POWER_MASK;
  POWER_PORT &= ~POWER_MASK;

  DATA_DDR &= ~DATA_MASK;

#if F_CPU != 16000000
#error Wrong prescalar for clock rate
#endif

  // Configure TCNT3 to count once every 16us, which should be fast enough to distinguish the various pulses.
  TCCR3A = 0;                   // Normal
  TCCR3B = _BV(CS32);           // Prescalar = 256

  matrix_init_quantum();
}

uint8_t matrix_scan(void) {
  static uint32_t last_power_off_time = 0;
  uint32_t now = timer_read32();
  if (now - last_power_off_time < POWER_OFF_INTERVAL) {
    return 0;
  }
  last_power_off_time = now;

  POWER_PORT |= POWER_MASK;     // Turn off.
  DATA_DDR |= DATA_MASK;
  DATA_PORT &= ~DATA_MASK;      // Write data low.
  wait_us(300);
  DATA_DDR &= ~DATA_MASK;
  DATA_PORT |= DATA_MASK;       // Input pullup

  poll();
  
  POWER_PORT &= ~POWER_MASK;    // Turn back on.
  DATA_PORT &= ~DATA_MASK;      // Don't need pullup.

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
