
#include QMK_KEYBOARD_H

#include "layout_description.h"

/*
 * Layout descriptions:
 *
 * Up to 4 layouts mapping 128 key codes for one key set can be defined.
 * These descriptions are used to match the layouts to keyboard-like devices.
 * In particular, note how there are two different mappings for the keyword-specific keyset #2,
 * with some keycode overlap.
 */
const layout_description_t PROGMEM layout_descriptions[MATRIX_ROWS/8] = {
  { .keyset = 1 },
  { .keyset = 2, .device_id = 0x30 },
  { .keyset = 2, .device_id = 0xE0 },
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = {

/*
 * 46021 (keycode Set 1):
 *
 * +---+---+ +----+----+----+----+---+---+----+----+----+----+ +---+---+   +---+---+---+---+
 * |Rst|Stp| | f1 | f2 | f3 | f4 |Men|Usr| f5 | f6 | f7 | f8 | |C l|C d|   |   |   |   |   |
 * +---+---+ +----+----+----+----+---+---+----+----+----+----+ +---+---+   +---+---+---+---+
 * +----+---+---+---+---+---+---+---+---+---+---+---+---+------+---+---+   +---+---+---+---+
 * | `  | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 0 | - | = |Backsp|I l|D l|   | * | / | + | - |
 * +-------------------------------------------------------------------+   +---------------+
 * | Tab  | Q | W | E | R | T | Y | U | I | O | P | [ | ] | \  |I c|D c|   | 7 | 8 | 9 |Ent|
 * +-------------------------------------------------------------------+   +---------------+
 * |Cap|Ctl| A | S | D | F | G | H | J | K | L | ; | ' |Return |Hom|Prv|   | 4 | 5 | 6 | , |
 * +-------------------------------------------------------------------+   +---------------+
 * |ESC|Shift| Z | X | C | V | B | N | M | , | . | / |Shift|Sel|Up |Nxt|   | 1 | 2 | 3 |   |
 * +---+-----+---------------------------------------+-----+-----------+   +-----------| T |
 * |Prt|     |Ext|                               |Ext|     |Lft|Dwn|Rgt|   |   0   | . |   |
 * +---+     +---+-------------------------------+---+     +---+---+---+   +-------+---+---+
 *
 */
SUB_LAYOUT_46021( \
  KC_BRK, KC_STOP, KC_F1, KC_F2, KC_F3, KC_F4, KC_MENU, KC_SYSREQ, KC_F5, KC_F6, KC_F7, KC_F8, KC_CLEAR, KC_CLEAR_AGAIN, KC_F9, KC_F10, KC_F11, KC_F12, \
  KC_GRAVE, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINUS, KC_EQUAL, KC_BSPACE, KC_PASTE, KC_CUT, KC_KP_ASTERISK, KC_KP_SLASH, KC_KP_PLUS, KC_KP_MINUS, \
  KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_LBRACKET, KC_RBRACKET, KC_BSLASH, KC_INSERT, KC_DELETE, KC_KP_7, KC_KP_8, KC_KP_9, KC_KP_ENTER, \
  KC_CAPS, KC_LCTL, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCOLON, KC_QUOTE, KC_ENTER, KC_HOME, KC_PGUP, KC_KP_4, KC_KP_5, KC_KP_6, KC_KP_COMMA, \
  KC_ESC, KC_LSHIFT, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMMA, KC_DOT, KC_SLASH, KC_RSHIFT, KC_EXSEL, KC_UP, KC_PGDN, KC_KP_1, KC_KP_2, KC_KP_3, KC_TAB, \
  KC_PSCREEN, KC_LALT, KC_SPACE, KC_RALT, KC_LEFT, KC_DOWN, KC_RIGHT, KC_KP_0, KC_KP_DOT \
),

/*
 *
 * 46086 (keycode Set 2):
 *
 *     +---+---+---+---+
 *     |   |   |   |   |
 * +---+---------------+---+
 * |   |   |   |   |   |   |
 * +---+---------------+---+
 * |   |   |   |   |   |   |
 * +---+---------------+---+
 * |   |   |   |   |   |   |
 * +---+---------------+---+
 * |   |   |   |   |   |   |
 * +---+---------------+---+
 *     |   |   |   |   |
 *     +---+---+---+---+
 *
 */
SUB_LAYOUT_46086( \
  KC_AUDIO_VOL_UP, KC_AUDIO_VOL_DOWN, KC_AUDIO_MUTE, BL_TOGG, \
  KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, \
  KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, \
  KC_F13, KC_F14, KC_F15, KC_F16, KC_F17, KC_F18, \
  KC_F19, KC_F20, KC_F21, KC_F22, KC_F23, KC_F24, \
  KC_MEDIA_PREV_TRACK, KC_MEDIA_PLAY_PAUSE, KC_MEDIA_STOP, KC_MEDIA_NEXT_TRACK \
),

/*
 * 98203 (keycode Set 2):
 *
 *         +---+---+---+---+---+   +---+---+   +---+---+---+           +---+---+---+---+
 *         |k0 |k1 |k2 |k3 |k4 |   |dwn|up |   |I L|D L|RCL|           |EDT|ALP|GRP|STP|
 *         +---+---+---+---+---+   +---+---+   +---+---+---+           +---+---+---+---+
 *         +---+---+---+---+---+   +---+---+   +---+---+---+           +---+---+---+---+
 *         |k5 |k6 |k7 |k8 |k9 |   |lft|rgt|   |I C|D C|C E|           |C L|RSL|PRT|CIO|
 *         +---+---+---+---+---+   +---+---+   +---+---+---+           +---+---+---+---+
 * +---+---+---+---+---+---+---+---+---+---+---+---+---+---+  +-----+  +---+---+---+---+
 * |CTL| 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 0 | - | = |BS |  |PAUSE|  | E | ( | ) | ^ |
 * +-------------------------------------------------------+  +-----+  +---------------+
 * | TAB | Q | W | E | R | T | Y | U | I | O | P | [ | ] | |  | RUN |  | 7 | 8 | 9 | / |
 * +------------------------------------------------------ |  +-----+  +---------------+
 * |CAPS LK| A | S | D | F | G | H | J | K | L | ; | ' |ENT|  |CONT |  | 4 | 5 | 6 | * |
 * +-------------------------------------------------------+  +-----+  +---------------+
 * | SHIFT   | Z | X | C | V | B | N | M | , | . | / |SHIFT|           | 1 | 2 | 3 | - |
 * +---------+---+-------------------------------+---+-----+  +-----+  +---------------+
 *               |                               |            |EXECU|  | 0 | . | , | + |
 *               +-------------------------------+            +-----+  +---+---+---+---+
 *
 */
SUB_LAYOUT_98203( \
  KC_ESC, KC_F1, KC_F2, KC_F3, KC_F4, KC_DOWN, KC_UP, KC_PASTE, KC_CUT, KC_NO, KC_HOME, KC_END, KC_PGUP, KC_PGDN, \
  KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_LEFT, KC_RIGHT, KC_INSERT, KC_DELETE, KC_CLEAR, KC_CLEAR_AGAIN, KC_NO, KC_PSCREEN, KC_NO, \
  KC_LCTL, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINUS, KC_EQUAL, KC_BSPACE, KC_PAUS, KC_KP_ENTER, KC_LPRN, KC_RPRN, KC_CIRC, \
  KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_LBRC, KC_RBRC, KC_RGUI, KC_KP_7, KC_KP_8, KC_KP_9, KC_KP_SLASH, \
  KC_CAPS, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCOLON, KC_QUOTE, KC_ENTER, KC_RALT, KC_KP_4, KC_KP_5, KC_KP_6, KC_KP_ASTERISK, \
  KC_LSHIFT, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMMA, KC_DOT, KC_SLASH, KC_KP_1, KC_KP_2, KC_KP_3, KC_KP_MINUS, \
  KC_SPACE, KC_EXEC, KC_KP_0, KC_KP_DOT, KC_KP_COMMA, KC_KP_PLUS \
),

  SUB_LAYOUT_EMPTY()

  }
};

void encoder_update_user(uint8_t index, bool clockwise) {
  xprintf("Encoder %d %s\n", index, clockwise ? "+" : "-");
  if (index == 0) { /* First encoder */
    if (clockwise) {
      tap_code(KC_AUDIO_VOL_UP);
    } else {
      tap_code(KC_AUDIO_VOL_DOWN);
    }
  }
}
