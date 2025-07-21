
#include "debug.h"
#include "matrix.h"
#include "print.h"
#include "quantum.h"

#include "uart.h"

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

inline
matrix_row_t matrix_get_row(uint8_t row) {
  return matrix[row];
}

void matrix_print(void) {
  print("\nr/c 01234567\n");
  for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
    print_hex8(row); print(": ");
    print_bin_reverse8(matrix_get_row(row));
    print("\n");
  }
}

#ifdef KPX_17S

#define RC(r,c) ((r<<4)|c)

// Each key sends one of two codes, depending on the state of the Num Lock LED.
// This LED is toggled by pressing the corresponding key.
// There is no way to set it sending serial data, so that the TX (to kbd) direction evidently does nothing.
static const uint8_t PROGMEM serial_row_col[128] = {
  [0x41] = RC(0,0),
  [0x79] = RC(0,0),
  [0x5A] = RC(0,1),
  [0x6A] = RC(0,1),
  [0x5B] = RC(0,2),
  [0x6B] = RC(0,2),
  [0x5C] = RC(0,3),
  [0x6C] = RC(0,3),
  [0x56] = RC(1,0),
  [0x66] = RC(1,0),
  [0x57] = RC(1,1),
  [0x67] = RC(1,1),
  [0x58] = RC(1,2),
  [0x68] = RC(1,2),
  [0x5D] = RC(1,3),
  [0x6D] = RC(1,3),
  [0x53] = RC(2,0),
  [0x63] = RC(2,0),
  [0x54] = RC(2,1),
  [0x64] = RC(2,1),
  [0x55] = RC(2,2),
  [0x65] = RC(2,2),
  [0x50] = RC(3,0),
  [0x60] = RC(3,0),
  [0x51] = RC(3,1),
  [0x61] = RC(3,1),
  [0x52] = RC(3,2),
  [0x62] = RC(3,2),
  [0x74] = RC(3,3),
  [0x5F] = RC(4,0),
  [0x6F] = RC(4,0),
  [0x5E] = RC(4,2),
  [0x6E] = RC(4,2),
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
  uart_init(1200);
#endif

#ifdef KPX_17P
  DATA_DDR = DATA_MASK;
  DATA_PORT = DATA_MASK;

  STATUS_DDR &= ~STATUS_MASK;
  STATUS_PORT |= STATUS_MASK;
#endif

  matrix_init_kb();
}

uint8_t matrix_scan(void) {
#ifdef KPX_17S
  static bool need_all_up = false;
  if (need_all_up) {
    // There are no up transitions, so clear everything between codes.
    for (uint8_t i = 0; i < MATRIX_ROWS; i++) matrix[i] = 0;
    need_all_up = false;
    matrix_scan_kb();
    return 1;
  }

  if (!uart_available()) {
    return 0;
  }
  uint8_t data = uart_read();
  if (data < 128) {
    const uint8_t *p_row_col = serial_row_col + data;
    uint8_t row_col = pgm_read_byte(p_row_col);
    if (row_col != 0) {
      uint8_t row = row_col >> 4;
      uint8_t col = row_col & 0x0F;
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

  matrix_scan_kb();
  return 1;
}
