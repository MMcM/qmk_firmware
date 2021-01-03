
#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/*
 * +---+
 * |A/C|
 * +---+
 * |PB↑|
 * +---+
 * |S/F|
 * +---+
 * |PB↓|
 * +---+
 * |B/D|
 * +---+
 */
  [0] = LAYOUT(
    KC_MEDIA_PLAY_PAUSE, KC_AUDIO_VOL_UP, KC_AUDIO_MUTE, KC_AUDIO_VOL_DOWN, KC_MEDIA_STOP
  )
};
