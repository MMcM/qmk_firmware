
#include QMK_KEYBOARD_H

// The Cardco Keycard Numeric Keypad presents the same protocol to the Joystick port:
// A key number in the direction bits and the trigger at the same time.
// It does this without any components other than diodes, so debounce is needed,
// but otherwise the same matrix works.

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = { {
   [0x18] = KC_P7,
   [0x17] = KC_P8,
   [0x16] = KC_P9,
   [0x12] = KC_PAST,
   [0x1B] = KC_P4,
   [0x1A] = KC_P5,
   [0x19] = KC_P6,
   [0x13] = KC_PSLS,
   [0x1E] = KC_P1,
   [0x1D] = KC_P2,
   [0x1C] = KC_P3,
   [0x14] = KC_PMNS,
   [0x11] = KC_PDOT,
   [0x1F] = KC_P0,
   [0x10] = KC_PENT,
   [0x15] = KC_PPLS,
  } }
} ;
