
#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/*
 * +---+   +----+----+----+----+----+----+----+----+----+----+----+----+   +---+---+---+---+---+
 * | x |   | F1 | F2 | F3 | F4 | F5 | F6 | F7 | F8 | F9 |F10 |F11 |F12 |   |<- |-[]|EML|LGT|STP|
 * +---+   +----+----+----+----+----+----+----+----+----+----+----+----+   +---+---+---+---+---+
 * +---+   +---+---+---+---+---+---+---+---+---+---+---+---+---+-------+   +---+---+---+---+---+
 * |FA |   |O- | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 0 | o | = | |<--  |   |LFT|DWN|HOM|UP |RGT|
 * +---+   +-----------------------------------------------------------+   +-------------------+
 * |FB |   | ->| | A | Z | E | R | T | Y | U | I | O | P |.. | ' | |<- |   |   | 7 | 8 | 9 |   |
 * +---+   +-----------------------------------------------------------+   | - |-----------|TRN|
 * |FC |   |/^ | ^ | Q | S | D | F | G | H | J | K | L | M | % | & |   |   |   | 4 | 5 | 6 |   |
 * +---+   +-------------------------------------------------------|RET|   +-------------------+
 * |REP|   |  ^  | < | W | X | C | V | B | N | , | ; | : | ! |  ^  |   |   |   | 1 | 2 | 3 |   |
 * +---+   +-----+---+-+-------------------------------+-+---+-----+---+   |., |---+---+---|ENT|
 *                     |                               |                   |   | 0 |00 |000|   |
 *                     +-------------------------------+                   +---+---+---+---+---+
 */

  [0] = LAYOUT(
    KC_ESC, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, KC_WWW_BACK, KC_PRINT_SCREEN, KC_MAIL, KC_SCROLL_LOCK, KC_PAUSE, \
    KC_NUM_LOCK, KC_GRAVE, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINUS, KC_EQUAL, KC_BACKSPACE, KC_LEFT, KC_DOWN, KC_HOME, KC_UP, KC_RIGHT, \
    KC_MENU, KC_TAB, KC_A, KC_Z, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_LEFT_BRACKET, KC_RIGHT_BRACKET, KC_DELETE, KC_KP_MINUS, KC_KP_7, KC_KP_8, KC_KP_9, KC_KP_PLUS, \
    KC_LEFT_ALT, KC_LEFT_CTRL, KC_LOCKING_CAPS_LOCK, KC_Q, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_M, KC_SEMICOLON, KC_QUOTE, KC_ENTER, KC_KP_4, KC_KP_5, KC_KP_6, \
    KC_LEFT_GUI, KC_LEFT_SHIFT, KC_NONUS_BACKSLASH, KC_W, KC_X, KC_C, KC_V, KC_B, KC_N, KC_COMMA, KC_DOT, KC_SLASH, KC_NONUS_HASH, KC_RIGHT_SHIFT, KC_KP_DOT, KC_KP_1, KC_KP_2, KC_KP_3, /*KC_KP_ENTER,*/ \
    KC_SPACE, KC_KP_0, KC_KP_0, KC_KP_ENTER \
  )
} ;
