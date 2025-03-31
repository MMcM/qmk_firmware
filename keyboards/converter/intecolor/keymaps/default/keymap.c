
#include QMK_KEYBOARD_H
#include "keymap_japanese.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/*
 * +---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+   +---+---+   +---+
 * |F0 |F1 |F2 |F3 |F4 |F5 |F6 |F7 |F8 |F9 |F10|F11|F12|F13|F14|UP |F15|   |EPG|ELN|   |RST|
 * +---+---+---+-------------------------------------------------------+   +-------+---+---+
 *             |AUT|FGO|BGO|BLO|2BL|2CH| [ | \ | ] | ^ | _ |LFT|HOM|RGT|   |DCH|ICH|DLN|INL|
 * +---+---+   +-------------------------------------------------------+   +---+---+---+---+
 * |BLK|BLU|   |ESC| 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 0 | - |DWN|BRK|            
 * +-------+   +-------------------------------------------------------+   +---+---+---+---+
 * |RED|MAG|   | TAB | Q | W | E | R | T | Y | U | I | O | P | @  |   |    | 7 | 8 | 9 | / |
 * +-------+   ++-------------------------------------------------|RET|    +---------------+
 * |GRN|CYN|    |CTRL | A | S | D | F | G | H | J | K | L | ; | : |   |    | 4 | 5 | 6 | * |
 * +-------+    +-+---------------------------------------------------+    +---------------+
 * |YEL|WHT|      |SHIFT| Z | X | C | V | B | N | M | , | . | / |SHIFT|    | 1 | 2 | 3 | - |
 * +-------+      +-----+---------------------------------------+-----+    +---------------+
 * |COMMAND|            |LCK|                               |RPT|          | 0 | . | = | + |
 * +-------+            +---+-------------------------------+---+          +---+---+---+---+
 */

  [0] = LAYOUT(
    KC_MENU, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, KC_F13, KC_F14, KC_UP, KC_F15, KC_INSERT, KC_PAGE_UP, QK_BOOTLOADER,
    KC_PRINT_SCREEN, KC_SCROLL_LOCK, KC_NO, KC_NO, KC_NO, KC_NO, KC_LEFT_BRACKET, KC_BACKSLASH, KC_RIGHT_BRACKET, KC_GRAVE, KC_EQUAL, KC_LEFT, KC_HOME, KC_RIGHT, KC_DELETE, KC_PAGE_DOWN, KC_END, QK_DEBUG_TOGGLE,
    KC_F16, KC_F17, KC_ESC, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINUS, KC_DOWN, KC_BACKSPACE,
    KC_F18, KC_F19, KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_GRAVE, KC_ENTER, /*KC_KP_7, KC_KP_8, KC_KP_9, KC_KP_SLASH,*/
    KC_F20, KC_F21, KC_LEFT_CTRL, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SEMICOLON, KC_QUOTE, /*KC_KP_4, KC_KP_5, KC_KP_6,*/ KC_KP_ASTERISK,
    KC_LEFT_GUI, KC_LEFT_ALT, KC_LEFT_SHIFT, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMMA, KC_DOT, KC_SLASH, /*KC_RIGHT_SHIFT, KC_KP_1, KC_KP_2, KC_KP_3, KC_KP_MINUS,*/
    KC_LOCKING_CAPS_LOCK, KC_SPACE, KC_RIGHT_ALT, /*KC_KP_0, KC_KP_DOT,*/ KC_KP_EQUAL, KC_KP_PLUS
  )
} ;
