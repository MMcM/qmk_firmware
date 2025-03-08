
#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/*
 * +---+---+   +---+---+---+---+---+---+---+---+---+---+---+---+---+------+  +---+---+   +---+---+---+
 * |ATN|SEL|   | ` | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 0 | - | = | BS   |  |DUP|MRK|   |F13|F14|F15|
 * +-------+   +----------------------------------------------------------+  +-------+   +-----------+
 * |ESC|   |   | TAB | Q | W | E | R | T |  Y| U | I | O | P | ! | \ |BTAB|  |INS|DEL|   |F16|F17|F18|
 * +-------+   +------------------------------------------------------+---+  +-------+   +-----------+
 * |BLK|EOF|   | LOCK | A | S | D | F | G | H | J | K | L | ;   ' | { |   |  |UP |DWN|   |F19|F20|F21|
 * +-------+   +------------------------------------------------------|RET|  +-------+   +-----------+
 * |PRT|VOL|   |SHFT| < | Z | X | C | V | B | N | M | , | . | / |SHFT |   |  |LFT|RGT|   |F22|F23|F24|
 * +---+---+   +---+-------------------------------------------------+---++  +---+---+   +---+---+---+
 *                 |RESET|                                    |ALT|ENTER |
 *                 +-----+------------------------------------+---+------+
 */
  [0] = LAYOUT(
    KC_PAUSE, KC_MENU, KC_GRAVE, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINUS, KC_EQUAL, KC_BACKSPACE, KC_PAGE_UP, KC_PAGE_DOWN, KC_F13, KC_F14, KC_F15, \
    KC_ESC, KC_NO, KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_LEFT_BRACKET, KC_RIGHT_BRACKET, KC_BACKSLASH, KC_INS, KC_DEL, KC_F16, KC_F17, KC_F18, \
    KC_HOME, KC_END, KC_LEFT_CTRL, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SEMICOLON, KC_QUOTE, KC_NONUS_BACKSLASH, KC_ENTER, KC_UP, KC_DOWN, KC_F19, KC_F20, KC_F21, \
    KC_PSCR, KC_NO, KC_LEFT_SHIFT, KC_NONUS_HASH, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMMA, KC_DOT, KC_SLASH, KC_RIGHT_SHIFT, KC_LEFT, KC_RIGHT, KC_F22, KC_F23, KC_F24, \
    KC_CAPS_LOCK, KC_SPACE, KC_RIGHT_ALT, KC_RIGHT_GUI
  )
} ;
