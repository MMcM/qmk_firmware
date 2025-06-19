
#include QMK_KEYBOARD_H
#include "keymap_japanese.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/*
 *        +---+---+---+---+---+---+---+---+
 *        |   |   |   |   |   |   |   |   |
 *        +---+---+---+---+---+---+---+---+
 *                                                           +---+---+---+---+
 *                                                           |CLL|CLD|HOM|RST|
 *                                                           +---+---+---+---+
 *   +---+---+---+---+---+---+---+---+---+---+---+---+---+---+     +---+---+
 *   | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 0 | - | ^ | \ |BS |     |INS|DEL|
 * +-+-----------------------------------------------------+-+     +---+---+  
 * |CTL| Q | W | E | R | T | Y | U | I | O | P | @ | [ | _ |     +---+---+---+
 * ++------------------------------------------------------++    |RUP|UP |NXT|
 *  |CAP| A | S | D | F | G | H | J | K | L | ; | : | ] |RET|    +-----------+
 *  +---------------------------------------------------|   |    |LEFT |RIGHT|
 *  |SHIFT| Z | X | C | V | B | N | M | , | . | / |SHIFT+---+    +-----------+
 *  +-----+---+---+---+---+---+---+---+---+---+---+-----+        |RDN|DWN|PRV|
 *           |                              |                    +---+---+---+
 *           +------------------------------+
 */

  [0] = LAYOUT(
    KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8,
    KC_ESC, KC_PRINT_SCREEN, KC_SCROLL_LOCK, KC_PAUSE,
    KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINUS, KC_EQUAL, KC_BACKSLASH, KC_BACKSPACE, KC_INSERT, KC_DELETE,
    KC_LEFT_CTRL, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_GRAVE, KC_LEFT_BRACKET, KC_TAB, KC_HOME, KC_UP, KC_PAGE_UP,
    KC_CAPS_LOCK, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SEMICOLON, KC_QUOTE, KC_RIGHT_BRACKET, KC_ENTER, KC_LEFT, KC_RIGHT,
    KC_LEFT_SHIFT, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMMA, KC_DOT, KC_SLASH, KC_RIGHT_SHIFT, KC_END, KC_DOWN, KC_PAGE_DOWN,
    KC_SPACE
  )
} ;
