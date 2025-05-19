
#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/*
 *   +----+  +---+---+---+---+  +---+---+---+---+  +---+---+---+---+  +---+---+---+---+  +----+
 *   |HELP|  | 1 | 2 | 3 | 4 |  | 5 | 6 | 7 | 8 |  | 9 |10 |11 |12 |  |13 |14 |15 |16 |  |CANC|
 *   +----+  +---+---+---+---+  +---+---+---+---+  +---+---+---+---+  +---+---+---+---+  +----+
 *
 * +---+---+---+---+---+---+---+---+---+---+---+---+---+--------+  +---+---+---+  +---+---+---+---+
 * |ESC| 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 0 | - | = |BACK SPC|  |EXE|INS|PRV|  | + | - | x |DTB|
 * +------------------------------------------------------------+  |   |-------+  +---------------+
 * | TAB | Q | W | E | R | T | Y | U | I | O | P |[ ]| ] |GL |  |  |   |DEL|NXT|  | 7 | 8 | 9 |PRT|
 * +------------------------------------------------------------+  +---+---+---+  +---------------+
 * | LOCK | A | S | D | F | G | H | J | K | L | ; | ' | RETURN  |      |UP |      | 4 | 5 | 6 |ERS|
 * +------------------------------------------------------------+  +---+---+---+  +---------------+
 * | SHIFT  | Z | X | C | V | B | N | M | , | . | / | SHIFT | \ |  |LFT|HOM|RGT|  | 1 | 2 | 3 |RET|
 * +--+-----------------------------------------------+---------+  +---+---+---+  +-----------|   |
 *    | ` |CTL|                                   |2ND|                |DWN|      |   0   | . |   |
 *    +---+---+-----------------------------------+---+                +---+      +-------+---+---+
 */

  [0] = LAYOUT(
    KC_HELP, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, KC_F13, KC_F14, KC_F15, KC_NUM_LOCK, KC_SCROLL_LOCK, \
    KC_ESC, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINUS, KC_EQUAL, KC_BACKSPACE, KC_EXECUTE, KC_INSERT, KC_PAGE_UP, KC_KP_PLUS, KC_KP_MINUS, KC_BACKSLASH, KC_GRAVE, \
    KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_LEFT_BRACKET, KC_RIGHT_BRACKET, KC_RIGHT_BRACKET, KC_DELETE, KC_PAGE_DOWN, KC_KP_7, KC_KP_8, KC_KP_9, KC_KP_ASTERISK, \
    KC_CAPS_LOCK, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SEMICOLON, KC_QUOTE, KC_ENTER, KC_UP, KC_KP_4, KC_KP_5, KC_KP_6, KC_CLEAR, \
    KC_LEFT_SHIFT, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMMA, KC_DOT, KC_SLASH, KC_RIGHT_SHIFT, KC_BACKSLASH, KC_LEFT, KC_HOME, KC_RIGHT, KC_KP_1, KC_KP_2, KC_KP_3, KC_KP_ENTER, \
    KC_GRAVE, KC_LEFT_CTRL, KC_SPACE, KC_RIGHT_ALT, KC_DOWN, KC_KP_0, KC_KP_DOT
  )
} ;
