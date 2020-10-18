
#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/*
 *                         +---+---+---+---+     +---+---+---+---+    +---+---+---+---+
 *                         |Dlg|Set|Lcl|Cop|     |F1 |F2 |F3 |F4 |    |F5 |F6 |F7 |F8 |
 *                         +---+---+---+---+     +---+---+---+---+    +---+---+---+---+
 * +---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+  +---+---+---+---+     +---+
 * |Pag| [ | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 0 | - | = | ] |Rub|  | 7 | 8 | 9 | - |     |Zom|
 * +---------------------------------------------------------------+  +---------------+     +---+
 * | Esc |~ || Q | W | E | R | T | Y | U | I | O | P |` \| BS  |LF |  | 4 | 5 | 6 | , |     |Pan|
 * +--------------------------------------------------------------++  +---------------+     +---+
 *  | Tab |Ctl| A | S | D | F | G | H | J | K | L | ; | ' |Return |   | 1 | 2 | 3 |Ent|     |NVw|
 *  +-+-----------------------------------------------------------+   +-----------|   |     +---+
 *    |Cap|Shift| Z | X | C | V | B | N | M | < | > | / |Shift|Brk|   |   0   | . |   |     |Viw|
 *    +---+-----+---+-------------------------------+---+-----+---+   +-------+---+---+     +---+
 *                  |                               |
 *                  +-------------------------------+
 */
     
  [0] = LAYOUT(
    KC_NUMLOCK, KC_NO, KC_SCROLLLOCK, KC_PSCREEN, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, \
    KC_PGDOWN, KC_LBRACKET, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINUS, KC_EQUAL, KC_RBRACKET, KC_DEL, KC_KP_7, KC_KP_8, KC_KP_9, KC_KP_MINUS, KC_UP,  \
    KC_ESC, KC_GRAVE, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_BSLASH, KC_BSPACE, KC_INS, KC_KP_4, KC_KP_5, KC_KP_6, KC_KP_COMMA, KC_LEFT,  \
    KC_TAB, KC_LCTRL, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCOLON, KC_QUOTE, KC_ENTER, KC_KP_1, KC_KP_2, KC_KP_3, KC_KP_ENTER, KC_RIGHT,  \
    KC_CAPSLOCK, KC_LSHIFT, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMMA, KC_DOT, KC_SLASH, KC_RSHIFT, KC_NO, KC_KP_0, KC_KP_DOT, KC_DOWN, \
    KC_SPACE \
  )
} ;

void encoder_update_user(uint8_t index, bool clockwise) {
  if (index == 0) {
    if (clockwise) {
      tap_code(KC_AUDIO_VOL_UP);
    } else {
      tap_code(KC_AUDIO_VOL_DOWN);
    }
  } else if (index == 1) {
    if (clockwise) {
      tap_code(KC_BRIGHTNESS_UP);
    } else {
      tap_code(KC_BRIGHTNESS_DOWN);
    }
  }
}

#include "tek_led.h"

// Light the LEDs under the righthand keys while they are pressed.
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  keyevent_t event = record->event;
  if (event.key.row == 2 && event.key.col >= 0x8 && event.key.col <= 0xB) {
    uint8_t led = led_for_key((event.key.row << 4) | event.key.col);
    if (led != TEK_LED_NONE) {
      uint32_t extra = led_get_extra();
      if (event.pressed) {
        extra |= ((uint32_t)1 << led);
      } else {
        extra &= ~((uint32_t)1 << led);
      }
      led_set_extra(extra);
    }
  }
  return true;
}
