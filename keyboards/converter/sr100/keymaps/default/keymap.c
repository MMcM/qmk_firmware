
#include QMK_KEYBOARD_H
#include "keymap_japanese.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/*
 *                                                 +-------+-------+       +---+---+---+---+
 *                                                 |  XMIT |  RCV  |       |LCL|B/W|SPC|PRT|
 *                                                 +-------+-------+       +---+---+---+---+
 *                                                                         |PF5|PF6|PF7|PF8|
 *     +----+                                      +---+---+---+---+---+   +---------------+
 *     |HOME|                                      |INC|DLC|LIN|CLR|ERS|   |PF1|PF2|PF3|PF4|
 *     +----+--+---+---+---+---+---+---+---+---+---+-------------------+   +---------------+
 *     | \ | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 0 | - | ^ | ] |PGL|PGR|   | 7 | 8 | 9 | - |
 *     +---------------------------------------------------------------+   +---------------+
 *     | TAB | Q | W | E | R | T | Y | U | I | O | P | @ | [ |   |RLU|     | 4 | 5 | 6 |BTB|
 * +---+-----------------------------------------------------|   |---+     +---------------+
 * |BTB| CAPS | A | S | D | F | G | H | J | K | L | ; | : |RETURN|RLD|     | 1 | 2 | 3 |   |
 * +-----------------------------------------------------------------+     +-----------|TAB|
 * |CTK|  SHIFT | Z | X | C | V | B | N | M | , | . | / |  SHIFT |CTS|     |   0   | . |   |
 * +---+--------+-+------------------------------------------+---+---+     +-------+---+---+
 *                |                                   |  TAB |
 *                +-----------------------------------+------+
 */

  [0] = LAYOUT(
    KC_F11, KC_F12, KC_NUM_LOCK, KC_SCROLL_LOCK, KC_PAUSE, KC_PRINT_SCREEN, 
    KC_F5, KC_F6, KC_F7, KC_F8,
    KC_ESC, KC_INS, KC_DEL, KC_HOME, KC_END, KC_BACKSPACE, KC_F1, KC_F2, KC_F3, KC_F4,
    KC_BACKSLASH, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINUS, KC_EQUAL, KC_RIGHT_BRACKET, KC_PAGE_UP, KC_PAGE_DOWN, KC_KP_7, KC_KP_8, KC_KP_9, KC_KP_MINUS,
    KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_GRAVE, KC_LEFT_BRACKET, KC_UP, KC_KP_4, KC_KP_5, KC_KP_6, KC_KP_PLUS,
    KC_LEFT_ALT, KC_CAPS_LOCK, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SEMICOLON, KC_QUOTE, KC_ENTER, KC_DOWN, KC_KP_1, KC_KP_2, KC_KP_3, KC_KP_ENTER,
    KC_LEFT_CTRL, KC_LEFT_SHIFT, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMMA, KC_DOT, KC_SLASH, KC_RIGHT_SHIFT, KC_RIGHT_CTRL, KC_KP_0, KC_KP_DOT,
    KC_SPACE, KC_RIGHT_GUI
  )
} ;
