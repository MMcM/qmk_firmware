
#include QMK_KEYBOARD_H

// A hand-built reproduction of the circuit using a standard 4x4 telephone type keypad like the decoder was normally for.

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = { {
   [0x1F] = KC_P1,
   [0x1E] = KC_P2,
   [0x1D] = KC_P3,
   [0x1C] = KC_F1,
   [0x1B] = KC_P4,
   [0x1A] = KC_P5,
   [0x19] = KC_P6,
   [0x18] = KC_F2,
   [0x17] = KC_P7,
   [0x16] = KC_P8,
   [0x15] = KC_P9,
   [0x14] = KC_F3,
   [0x13] = KC_PAST,
   [0x12] = KC_P0,
   [0x11] = KC_PENT,
   [0x10] = KC_F4,
  } }
} ;
