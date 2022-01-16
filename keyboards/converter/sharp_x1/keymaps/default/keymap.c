
#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/*
 * +-----+-----+-----+-----+-----++---+---++---+---+               +---+---+---+---+
 * | F1  | F2  | F3  | F4  | F5  ||RUP|RDN||HLP|CPY|               |CLR| / | * | - |
 * +-----+-----+-----+-----+-----++---+---++---+---+               +---+---+---+---+
 * +---+---+---+---+---+---+---+---+---+---+---+---+---+---+-----+ +---+---+---+---+
 * |ESC| 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 0 | - | ^ | ¥ |BRK  | | 7 | 8 | 9 | + |
 * +-------------------------------------------------------------+ +---------------+
 * |H TAB| Q | W | E | R | T | Y | U | I | O | P | @ | [ |INS|   | | 4 | 5 | 6 | = |
 * +---------------------------------------------------------|   | +---------------+
 * | CTRL | A | S | D | F | G | H | J | K | L | ; | : | ] |RETURN| | 1 | 2 | 3 | . |
 * +-------------------------------------------------------------+ +---------------+
 * |  SHIFT | Z | X | C | V | B | N | M | , | . | / |   |  SHIFT | | 0 | , |UP |RET|
 * +------+-----------------------------------------------+------+ +-----------|   |
 *        |GPH|CAP|           SPACE               |KAN|XFR|        |LFT|RGT|DWN|   |
 *        +---+---+-------------------------------+---+---+        +---+---+---+---+
 */

  [0] = LAYOUT(
    KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_PGUP, KC_PGDN, KC_HELP, KC_PSCR,                                 KC_NLCK, KC_PSLS, KC_PAST, KC_PMNS,
    KC_ESC, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINS, KC_EQL, KC_JYEN, KC_PAUS, KC_P7, KC_P8, KC_P9, KC_PPLS,
    KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_GRV, KC_LBRC, KC_BSPC,          KC_P4, KC_P5, KC_P6, KC_PEQL,
    KC_LCTRL, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT, KC_RBRC, KC_ENT,     KC_P1, KC_P2, KC_P3, KC_PDOT,
    KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_RO, KC_RSFT,           KC_P0, KC_PCMM, KC_UP, KC_PENT,
    KC_LALT, KC_LCAP, KC_SPACE, KC_KANA, KC_APP,                                                           KC_LEFT, KC_RIGHT, KC_DOWN
  )
} ;
