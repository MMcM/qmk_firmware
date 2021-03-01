
#include "debug.h"
#include "matrix.h"
#include "print.h"
#include "quantum.h"

#if defined(__AVR__)
#include <avr/io.h>
#include "protocol/serial.h"
#elif defined PROTOCOL_CHIBIOS
#include "hal.h"
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

#ifdef KPX_17S

#define RC(r,c) ((r<<4)|c)

// Each key sends one of two codes, depending on the state of the Num Lock LED.
// This LED is toggled by pressing the corresponding key.
// There is no way to set it sending serial data, so that the TX (to kbd) direction evidently does nothing.
static const uint8_t PROGMEM serial_row_col[128] = {
  [0x41] = RC(1,1),
  [0x79] = RC(1,1),
  [0x5A] = RC(1,2),
  [0x6A] = RC(1,2),
  [0x5B] = RC(1,3),
  [0x6B] = RC(1,3),
  [0x5C] = RC(1,4),
  [0x6C] = RC(1,4),
  [0x56] = RC(2,1),
  [0x66] = RC(2,1),
  [0x57] = RC(2,2),
  [0x67] = RC(2,2),
  [0x58] = RC(2,3),
  [0x68] = RC(2,3),
  [0x5D] = RC(2,4),
  [0x6D] = RC(2,4),
  [0x53] = RC(3,1),
  [0x63] = RC(3,1),
  [0x54] = RC(3,2),
  [0x64] = RC(3,2),
  [0x55] = RC(3,3),
  [0x65] = RC(3,3),
  [0x50] = RC(4,1),
  [0x60] = RC(4,1),
  [0x51] = RC(4,2),
  [0x61] = RC(4,2),
  [0x52] = RC(4,3),
  [0x62] = RC(4,3),
  [0x74] = RC(4,4),
  [0x5F] = RC(5,1),
  [0x6F] = RC(5,1),
  [0x5E] = RC(5,3),
  [0x6E] = RC(5,3),
};

#endif

#ifdef KPX_17P

// Don't use either serial pin, so a single version ought to be able to support serial and parallel.

#define DATA_DDR DDRB
#define DATA_MASK 0xFF
#define DATA_PORT PORTB

#define STATUS_DDR DDRD
#define STATUS_MASK 0x03
#define STATUS_PIN PIND
#define STATUS_PORT PORTD
#define STATUS_SELECT (1 << 0)
#define STATUS_ERROR (1 << 1)

#define TRIGGER_DELAY_US 10

#endif

void matrix_init(void) {
  for (uint8_t i = 0; i < MATRIX_ROWS; i++) matrix[i] = 0;

#ifdef KPX_17S
#if defined(__AVR__)
  serial_init();
#elif defined PROTOCOL_CHIBIOS
  palSetPadMode(GPIOB, 16, PAL_MODE_ALTERNATIVE_3); // pin 0 / B16 / RX1 = UART0_RX
  palSetPadMode(GPIOB, 17, PAL_MODE_ALTERNATIVE_3); // pin 1 / B17 / TX1 = UART0_TX

  static const SerialConfig sdcfg = { 1200 };
  sdStart(&SD1, &sdcfg);
#endif
#endif

#ifdef KPX_17P
  DATA_DDR = DATA_MASK;
  DATA_PORT = DATA_MASK;

  STATUS_DDR &= ~STATUS_MASK;
  STATUS_PORT |= STATUS_MASK;
#endif

  matrix_init_quantum();
}

uint8_t matrix_scan(void) {
#ifdef KPX_17S
  static bool need_all_up = false;
  if (need_all_up) {
    // There are no up transitions, so clear everything between codes.
    for (uint8_t i = 0; i < MATRIX_ROWS; i++) matrix[i] = 0;
    need_all_up = false;
    matrix_scan_quantum();
    return 1;
  }

  uint8_t data;

#if defined(__AVR__)
  int16_t data2 = serial_recv2();
  if (data2 < 0) {
    return 0;
  }
  data = data2 & 0xFF;
#elif defined PROTOCOL_CHIBIOS
  msg_t msg = sdGetTimeout(&SD1, TIME_IMMEDIATE);
  if (msg < 0) {
    return 0;
  }
  data = msg & 0xFF;
#endif

  if (data < 128) {
    const uint8_t *p_row_col = serial_row_col + data;
    uint8_t row_col = pgm_read_byte(p_row_col);
    if (row_col != 0) {
      uint8_t row = (row_col >> 4) - 1;
      uint8_t col = (row_col & 0x0F) - 1;
      matrix[row] |= (1 << col);
      need_all_up = true;
    }
  }
#endif

#ifdef KPX_17P
  static uint8_t scan_col = 0;
  static uint8_t scan_row = 0;

  if (scan_col == 0) {
    // Falling signal on the clear line.
    DATA_PORT = 0xFF;
    wait_us(TRIGGER_DELAY_US);
    DATA_PORT = 0xF3;
    wait_us(TRIGGER_DELAY_US);
    DATA_PORT = 0xF7;
    wait_us(TRIGGER_DELAY_US);
    DATA_PORT = 0xFF;
    wait_us(TRIGGER_DELAY_US);
    scan_row = 0;
  }
  if (scan_row == 0) {
    // Falling signal on counter clock.
    DATA_PORT = 0xFF;
    wait_us(TRIGGER_DELAY_US);
    DATA_PORT = 0xFB;
    wait_us(TRIGGER_DELAY_US);
    DATA_PORT = 0xFF;
    wait_us(TRIGGER_DELAY_US);
    scan_col++;
    if (scan_col > 4) {
      // I think it's a decade counter, so it would also work to count out 5-10 without scanning.
      scan_col = 0;
      return 0;
    }
  }
  scan_row++;
  switch (scan_row) {
  case 1:
    DATA_PORT = 0x4F;
    break;
  case 2:
    DATA_PORT = 0x3F;
    break;
  case 3:
    DATA_PORT = 0x1F;
    break;
  case 4:
    DATA_PORT = 0x2F;
    break;
  case 5:
    DATA_PORT = 0x0F;
    break;
  }
  wait_us(TRIGGER_DELAY_US);
  bool pressed = (STATUS_PIN & STATUS_ERROR) == 0; // No error = key is pressed.

  uint8_t row = scan_row - 1;
  uint8_t col = scan_col - 1;
  if (pressed) {
    matrix[row] |= (1 << col);
  } else {
    matrix[row] &= ~(1 << col);
  }

  if (scan_row == 5) {
    scan_row = 0;
  }
#endif

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
