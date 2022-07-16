
#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/*
 * +---+---+---+---+  +---+---+---+---+---+---+---+---+---+---+---+---+---+-------+  +---+---+---+---+
 * |   |   |   |   |  |   | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 0 | - | = |BACK SP|  |   |   |   |   |
 * +---------------+  +-----------------------------------------------------------+  +---------------+
 * |   |WRD|IN |SKP|  | TAB | Q | W | E | R | T | Y | U | I | O | P | ½ | RE|TURN |  | 7 | 8 | 9 |   |
 * |UP |-----------+  +------------------------------------------------------|    +  +-----------|ENT|
 * |   |LIN|OUT|HLD|  | LOCK | A | S | D | F | G | H | J | K | L | ; | ' |   |    |  | 4 | 5 | 6 |   |
 * +---------------+  +-----------------------------------------------------------+  +---------------+
 * |TSK|PAR|PRT|ADJ|  | SH|IFT | Z | X | C | V | B | N | M | , | . | / |  SHI|FT  |  | 1 | 2 | 3 | - |
 * +---------------+  +-----------------------------------------------------------+  +---------------+
 * |STP|PAG| DOWN  |  |MOV|ERS|   |CODE |        SPACE          |CODE |   |ERS|PRG|  |   0   | . | , |
 * +---+---+-------+  +---+---+   +-----+-----------------------+-----+   +---+---+  +-------+---+---+
 *
 * NOTE: TAB covers 2 switches, RETURN 3, and each SHIFT 2. If the standard keycaps are present, these need to be KC_NO. If some switches have separate keycaps, they can have their own codes.
 */
  [0] = LAYOUT(
    KC_ESC, KC_F1, KC_F2, KC_F3,         KC_NO, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINUS, KC_EQUAL, KC_BSPACE,            KC_NLCK, KC_F4, KC_F5, KC_F6,
    KC_UP, KC_INS, KC_HOME, KC_PGUP,     KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_LBRACKET, KC_NO, KC_ENTER,            KC_KP_7, KC_KP_8, KC_KP_9, KC_KP_ENTER,
           KC_DEL, KC_END, KC_PGDN,      KC_CAPSLOCK, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCOLON, KC_QUOTE, KC_NO,               KC_KP_4, KC_KP_5, KC_KP_6,
    KC_APP, KC_SCRL, KC_PSCR, KC_PAUS,   KC_LSHIFT, KC_NO, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMMA, KC_DOT, KC_SLASH, KC_NO, KC_RSHIFT,    KC_KP_1, KC_KP_2, KC_KP_3, KC_KP_MINUS,
    KC_LEFT, KC_RGHT, KC_DOWN,           KC_LCTRL, KC_LGUI, KC_LALT, KC_SPACE, KC_RALT, KC_RGUI, KC_RCTRL,                                            KC_KP_0, KC_KP_DOT, KC_KP_COMMA
  )
} ;
