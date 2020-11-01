
#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/*
 * +---+---+ +---+----+---+---+---+---+---+---+---+---+---+---+---+---+---+---+........
 * |F1 |F2 | |MTX|PAGE|PRT|PRG|   |ALM|FN1|LPG|RPG|ACK|   |DST|HLP|PRQ|MSQ|MEN|###|###|
 * +-------+ +----------------------------------------------------------------+........
 * |F3 |F4 | |CLR|RSTR| Q | W | E | R | T | Y | U | I | O | P |###| 1 | 2 | 3 |###|###|
 * +-------+ +----------------------------------------------------------------+........
 * |F5 |F6 | |BLK-|BLK+| A | S | D | F | G | H | J | K | L |  ;   | 4 | 5 | 6 |###|###|
 * +-------+ +----------------------------------------------------------------+........
 * |F7 |F8 | |SK-|SK+|ERS| Z | X | C | V | B | N | M | , | . | /  | 7 | 8 | 9 |###|###|
 * +-------+ +----------------------------------------------------------------+........
 * |F9 |F10| |LFT|RGT|NLN| SHIFT |   SPACE   |  END  | ENTER | +  | - | 0 | . |###|###|
 * +---+---+ +---+---+---+-------+-----------+-------+-------+----+---+---+---+........
 */

  [0] = LAYOUT(
    KC_F1, KC_F2, KC_ESC, KC_NO, KC_PSCREEN, KC_PAUSE, KC_NO, KC_NO, KC_LGUI, KC_PGUP, KC_PGDN, KC_HOME, KC_END, KC_NO, KC_HELP, KC_INS, KC_DEL, KC_APP, \
    KC_F3, KC_F4, KC_BSPACE, KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_KP_1, KC_KP_2, KC_KP_3, \
    KC_F5, KC_F6, KC_PGUP, KC_PGDN, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCOLON, KC_KP_4, KC_KP_5, KC_KP_6, \
    KC_F7, KC_F8, KC_UP, KC_DOWN, KC_LCTRL, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMMA, KC_DOT, KC_SLASH, KC_KP_7, KC_KP_8, KC_KP_9, \
    KC_F9, KC_F10, KC_LEFT, KC_RIGHT, KC_LALT, KC_LSHIFT, KC_SPACE, KC_END, KC_ENTER, KC_KP_PLUS, KC_KP_MINUS, KC_KP_0, KC_KP_DOT \
  )
} ;
