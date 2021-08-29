
#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/*
 *   +---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+   +---+---+---+---+
 *   |F1 |F2 |F3 |F4 |F5 |F6 |F7 |F8 |F9 |F10|F11|F12|F13|F14|F15|F16|   |CE |PAG|SET|SND|
 *   +---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+   +---+---+---+---+
 *   +----+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+  +---+---+---+---+
 *   |LESC| 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 0 | - | = | ` | \ |BS |  |CHR|LIN|PAG|TAB|
 *   +----------------------------------------------------------------+  +---------------+
 *   | TAB  | Q | W | E | R | T | Y | U | I | O | P | [ | ] |   |CLR |   | 7 | 8 | 9 | - |
 *   +------------------------------------------------------|   |----+   +---------------+
 *   |CTL|CAP| A | S | D | F | G | H | J | K | L | ; | ' |RETURN|BRK |   | 4 | 5 | 6 | + |
 *   +---------------------------------------------------------------+   +---------------+
 *   |BTB|SHIFT| Z | X | C | V | B | N | M | , | . | / |SHIFT|LF |DEL|   | 1 | 2 | 3 |ENT|
 *   +---------------------------------------------------------------+   +-----------|   |
 *   |RST|PRT|FCN|                                   |DWN|UP |LFT|RGH|   |   0   | . |   |
 *   +---+---+---+-----------------------------------+---+---+---+---+   +-------+-------+
 *
 */
     
  [0] = LAYOUT(
    KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, KC_F13, KC_F14, KC_F15, KC_F16, KC_F17, KC_F18, KC_F19, KC_F20, \
    KC_ESC, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINUS, KC_EQUAL, KC_GRAVE, KC_BSLASH, KC_BSPACE, KC_NUMLOCK, KC_KP_SLASH, KC_KP_ASTERISK, KC_TAB, \
    KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_LBRACKET, KC_RBRACKET, KC_HOME, KC_KP_7, KC_KP_8, KC_KP_9, KC_KP_MINUS, \
    KC_LCTRL, KC_CAPSLOCK, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCOLON, KC_QUOTE, KC_ENTER, KC_PAUSE, KC_KP_4, KC_KP_5, KC_KP_6, KC_KP_PLUS, \
    KC_PRIOR, KC_LSHIFT, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMMA, KC_DOT, KC_SLASH, KC_RSHIFT, KC_SEPARATOR, KC_DEL, KC_KP_1, KC_KP_2, KC_KP_3, KC_KP_ENTER, \
    KC_STOP, KC_PSCREEN, KC_LALT, KC_SPACE, KC_DOWN, KC_UP, KC_LEFT, KC_RIGHT, KC_KP_0, KC_KP_DOT \
    )
} ;
