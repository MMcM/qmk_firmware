
#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/*
 * +---+---+---+    +-----+-----+-----+-----+-----+   +-----+-----+-----+-----+-----+  +---+---+---+---+---+
 * |I M|L D|C D|    | F0  | F1  | F2  | F3  | F4  |   | F5  | F6  | F7  | F8  | F9  |  | A | R |S E|A E|H H|
 * +-----------+    +-+---------------------------+---+----------------------------++  +---+---+---+---+---+
 * |C C|U P|M G|      |ESC| 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 0 | - | = | ` | BS |
 * +-----------+      +------------------------------------------------------------+       +---+---+---+---+
 * ||← |S C| →||      | TAB | Q | W | E | R | T | Y | U | I | O | P | [ | ] |  |DEL|       | 7 | 8 | 9 | + |
 * +-----------+   +---+----------------------------------------------------|  |---+       +---------------+
 * |[←]| ↑ |[→]|   |CTR| C  L| A | S | D | F | G | H | J | K | L | ; | ' | RET | \ |       | 4 | 5 | 6 | - |
 * +-----------+   +---------------------------------------------------------------+       +---------------+
 * | ← |N W| → |   |REP| SHIFT | Z | X | C | V | B | N | M | , | . | / | SHIFT |POP|       | 1 | 2 | 3 |   |
 * +-----------+   +---+-------+---+-+------------------------------+--+-------+---+       +-----------|ENT|
 * |[↑]| ↓ |[↓]|                     |                              |                      |    0  | . |   |
 * +---+---+---+                     +------------------------------+                      +-------+---+---+
 */

  [0] = LAYOUT(
    KC_NO, KC_NO, KC_NO, KC_F10, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_AGAIN, KC_NO, KC_NO, KC_PAUSE, KC_HELP, \
    KC_COPY, KC_PASTE, KC_NO, KC_ESC, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINUS, KC_EQUAL, KC_GRAVE, KC_BSPACE, \
    KC_NO, KC_NO, KC_NO, KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_LBRACKET, KC_RBRACKET, KC_DEL, KC_KP_7, KC_KP_8, KC_KP_9, KC_KP_PLUS, \
    KC_HOME, KC_UP, KC_END, KC_LCTRL, KC_LCAP, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCOLON, KC_QUOTE, KC_ENTER, KC_BSLASH, KC_KP_4, KC_KP_5, KC_KP_6, KC_KP_MINUS, \
    KC_LEFT, KC_NO, KC_RIGHT, KC_LALT, KC_LSHIFT, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMMA, KC_DOT, KC_SLASH, KC_RSHIFT, KC_RGUI, KC_KP_1, KC_KP_2, KC_KP_3, \
    KC_PGUP, KC_DOWN, KC_PGDOWN, KC_SPACE, KC_KP_0, KC_KP_DOT, KC_KP_ENTER \
  )
} ;
