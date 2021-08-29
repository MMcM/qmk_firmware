
#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/*
 *               +---+---+---+---+     +---+---+---+---+     +---+---+---+---+    +---+---+
 *               |RST|GUI|ALT|   |     |ALT|MEN|SCL|NUM|     |F1 |F2 |F3 |F4 |    |F9 |F10|
 *               +---+---+---+---+     +---+---+---+---+     +---+---+---+---+    +---+---+
 *               +---+---+---+---+     +---+       +---+     +---+---+---+---+    +---+---+
 *               |   |CAP|   |   |     |PRT|       |PAU|     |F5 |F6 |F7 |F8 |    |INS|DEL|
 *               +---+---+---+---+     +---+       +---+     +---+---+---+---+    +---+---+
 * +---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+ +---+---+---+ +---+---+---+
 * |ESC| 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 0 | - | = | \ |BS | | 7 | 8 | 9 | |F11|F12|F13|
 * +-----------------------------------------------------------+ +-----------+ +-----------+
 *   |TAB| Q | W | E | R | T | Y | U | I | O | P | ` | [ |DEL|   | 4 | 5 | 6 | |   |UP |PDN|
 *   +-------------------------------------------------------+   +-----------+ +-----------+
 *    |CTL| A | S | D | F | G | H | J | K | L | ; | ' | ] |ENT|  | 1 | 2 | 3 | |LFT|HOM|RGT|
 *    +---------------------------------------------------|   |  +-----------+ +-----------+
 *    |SHIFT| Z | X | C | V | B | N | M | , | . | / |SHIFT+---+  |   0   | . | |   |DWN|PUP|
 *    +---------------------------------------------------+      +-----------+ +-----------+
 *              |           SPACE               |
 *              +-------------------------------+
 */
     
    [0] = LAYOUT(
  KC_NO, KC_LGUI, KC_LALT, KC_NO, KC_RALT, KC_MENU, KC_SLCK, KC_NLCK, KC_F1, KC_F2, KC_F3, KC_F4, KC_F9, KC_F10, \
  KC_NO, KC_LCAP, KC_NO, KC_NO, KC_PSCR, KC_PAUS, KC_F5, KC_F6, KC_F7, KC_F8, KC_INS, KC_DEL, \
  KC_ESC, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINS, KC_EQL, KC_BSLS, KC_BSPC, KC_P7, KC_P8, KC_P9, KC_F11, KC_F12, KC_F13, \
  KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_GRV, KC_LBRC, KC_DEL, KC_P4, KC_P5, KC_P6, KC_NO, KC_UP, KC_PGUP, \
  KC_LCTL, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT, KC_RBRC, KC_ENT, KC_P1, KC_P2, KC_P3, KC_LEFT, KC_HOME, KC_RGHT, \
  KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_RSFT, KC_P0, KC_PDOT, KC_NO, KC_DOWN, KC_PGDN, \
  KC_SPC \
    )
} ;
