
#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/*
 *   +---+---+---+---+---+     +---+---+---+---+---+     +---+ +---+           +---+  +---+
 *   |FK1|FK2|FK3|FK4|FK5|     |EXP|BSP|SPC|CLR|RCL|     |NUM| |STP|           |LOD|  |REW|
 *   +---+---+---+---+---+     +---+---+---+---+---+     +---+ +---+           +---+  +---+
 *   +---+---+---+---+---+                                                            +---+
 *   |FK6|FK7|FK8|FK9|F10|                                                            |CPY|
 *   +---+---+---+---+---+                                                            +---+
 * +---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+   +---+---+---+  +---+
 * |PAG| [ | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 0 | : | - | ] |BS |   | ( |EXP| ) |  | ^ |
 * +-+------------------------------------------------------------++   +-----------+  +---+
 *   |ESC| ^ | Q | W | E | R | T | Y | U | I | O | P | @ |LF |RETN|    | 7 | 8 | 9 |  | / |
 *   +--------------------------------------------------------|   |    +-----------+  +---+
 *    |TAB|CTL| A | S | D | F | G | H | J | K | L | ; | \ |RUB|   |    | 4 | 5 | 6 |  | * |
 *    +-----------------------------------------------------------+    +-----------+  +---+
 *    |TTY|SHIFT| Z | X | C | V | B | N | M | , | . | / |SHIFT|BRK|    | 1 | 2 | 3 |  | - |
 *    +---+-----+---+-------------------------------+---+-----+---+    +-----------+  +---+
 *                  |             SPACE             |                  |   0   | . |  | + |
 *                  +-------------------------------+                  +-----------+  +---+
 * 
 */

  [0] = LAYOUT(
    KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, 
    KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_NO,
    KC_HOME, KC_LEFT_BRACKET, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINUS, KC_EQUAL, KC_RIGHT_BRACKET, KC_BACKSPACE, KC_LEFT_PAREN, KC_KP_ENTER, KC_RIGHT_PAREN, KC_CIRCUMFLEX,
    KC_ESC, KC_QUOTE, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_GRAVE, KC_PAGE_DOWN, KC_ENTER, KC_KP_7, KC_KP_8, KC_KP_9, KC_KP_SLASH,
    KC_TAB, KC_LEFT_CTRL, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SEMICOLON, KC_BACKSLASH, KC_DEL, KC_KP_4, KC_KP_5, KC_KP_6, KC_KP_ASTERISK,
    KC_LOCKING_CAPS_LOCK, KC_LEFT_SHIFT, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMMA, KC_DOT, KC_SLASH, /*KC_RIGHT_SHIFT,*/ KC_PAUSE, KC_KP_1, KC_KP_2, KC_KP_3, KC_KP_MINUS,
    KC_SPACE, KC_KP_0, KC_KP_DOT, KC_KP_PLUS)
} ;
