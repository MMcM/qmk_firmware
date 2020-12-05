/*
Copyright 2012 Jun Wako <wakojun@gmail.com>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include QMK_KEYBOARD_H

/*
   Type 4
,-------.  ,-----------------------------------------------------------.  ,---------------.
| 01| 03|  | 05| 06| 08| 0A| 0C| 0E| 10| 11| 12| 07| 09| 0B| 58|   42  |  | 15| 16| 17| 62|
|-------|  |-----------------------------------------------------------|  |---------------|
| 19| 1A|  | 1D| 1E| 1F| 20| 21| 22| 23| 24| 25| 26| 27| 28| 29|   2B  |  | 2D| 2E| 2F| 47|
|-------|  |-----------------------------------------------------------|  |---------------|
| 31| 33|  |  35 | 36| 37| 38| 39| 3A| 3B| 3C| 3D| 3E| 3F| 40| 41| 59  |  | 44| 45| 46|   |
|-------|  |------------------------------------------------------     |  |-----------| 7D|
| 48| 49|  |  4C  | 4D| 4E| 4F| 50| 51| 52| 53| 54| 55| 56| 57| 2A|    |  | 5B| 5C| 5D|   |
|-------|  |-----------------------------------------------------------|  |-----------|---|
| 5F| 61|  |   63   | 64| 65| 66| 67| 68| 69| 6A| 6B| 6C| 6D|  6E  |6F |  | 70| 71| 72|   |
|-------|  |-----------------------------------------------------------|  |-----------| 5A|
|   76  |  | 77 | 13| 78 |            79                 |  7A | 43| 0D|  |   5E  | 32|   |
`-------'  `-----------------------------------------------------------'  `---------------'

   Type 5, US, Unix-style
,-------.  ,---,  ,---------------. ,---------------. ,---------------.   ,-----------. ,---------------.
|   76  |  | 0F|  | 05| 06| 08| 0A| | 0C| 0E| 10| 11| | 12| 07| 09| 0B|   | 16| 17| 15| | 2D| 02| 04| 30|
`-------'  `---'  `---------------' `---------------' `---------------'   `-----------' `---------------'
,-------.  ,-----------------------------------------------------------.  ,-----------. ,---------------.
| 01| 03|  | 1D| 1E| 1F| 20| 21| 22| 23| 24| 25| 26| 27| 28| 29| 58| 2A|  | 2C| 34| 60| | 62| 2E| 2F| 47|
|-------|  |-----------------------------------------------------------|  |------------ |---------------|
| 19| 1A|  |  35 | 36| 37| 38| 39| 3A| 3B| 3C| 3D| 3E| 3F| 40| 41| 2B  |  | 42| 4A| 7B| | 44| 45| 46|   |
|-------|  |-----------------------------------------------------------|  `-----------' |-----------| 7D|
| 31| 33|  |  4C  | 4D| 4E| 4F| 50| 51| 52| 53| 54| 55| 56| 57|   59   |                | 5B| 5C| 5D|   |
|-------|  |-----------------------------------------------------------|      ,---.     |-----------|---|
| 48| 49|  |   63   | 64| 65| 66| 67| 68| 69| 6A| 6B| 6C| 6D|    6E    |      | 14|     | 70| 71| 72|   |
|-------|  |-----------------------------------------------------------|  .-----------. |-----------| 5A|
| 5F| 61|  | 77 | 13| 78 |            79                 |  7A | 43| 0D|  | 18| 1B| 1C| |   5E  | 32|   |
`-------'  `-----------------------------------------------------------'  `-----------' `---------------'

Combine the two by adding a LF key to the right of SHIFT.
*/
#define LAYOUT_combined(                                                 \
      K76,    K0F,  K05,K06,K08,K0A,   K0C,K0E,K10,K11,   K12,K07,K09,K0B,  K16,K17,K15,  K2D,K02,K04,K30, \
    K01,K03,  K1D,K1E,K1F,K20,K21,K22,K23,K24,K25,K26,K27,K28,K29,K58,K2A,  K2C,K34,K60,  K62,K2E,K2F,K47, \
    K19,K1A,  K35, K36,K37,K38,K39,K3A,K3B,K3C,K3D,K3E,K3F,K40,K41,   K2B,  K42,K4A,K7B,  K44,K45,K46,K7D, \
    K31,K33,  K4C,  K4D,K4E,K4F,K50,K51,K52,K53,K54,K55,K56,K57,      K59,                K5B,K5C,K5D,     \
    K48,K49,  K63,   K64,K65,K66,K67,K68,K69,K6A,K6B,K6C,K6D,    K6E, K6F,      K14,      K70,K71,K72,K5A, \
    K5F,K61,  K77,K13, K78,             K79,                K7A, K43, K0D,  K18,K1B,K1C,  K5E,    K32      \
) { \
    { KC_NO,  K01 ,  K02 ,  K03 ,  K04 ,  K05 ,  K06 ,  K07  }, \
    {  K08 ,  K09 ,  K0A ,  K0B ,  K0C ,  K0D ,  K0E ,  K0F ,}, \
    {  K10 ,  K11 ,  K12 ,  K13 ,  K14 ,  K15 ,  K16 ,  K17  }, \
    {  K18 ,  K19 ,  K1A ,  K1B ,  K1C ,  K1D ,  K1E ,  K1F  }, \
    {  K20 ,  K21 ,  K22 ,  K23 ,  K24 ,  K25 ,  K26 ,  K27  }, \
    {  K28 ,  K29 ,  K2A ,  K2B ,  K2C ,  K2D ,  K2E ,  K2F  }, \
    {  K30 ,  K31 ,  K32 ,  K33 ,  K34 ,  K35 ,  K36 ,  K37  }, \
    {  K38 ,  K39 ,  K3A ,  K3B ,  K3C ,  K3D ,  K3E ,  K3F  }, \
    {  K40 ,  K41 ,  K42 ,  K43 ,  K44 ,  K45 ,  K46 ,  K47  }, \
    {  K48 ,  K49 ,  K4A , KC_NO,  K4C ,  K4D ,  K4E ,  K4F  }, \
    {  K50 ,  K51 ,  K52 ,  K53 ,  K54 ,  K55 ,  K56 ,  K57  }, \
    {  K58 ,  K59 ,  K5A ,  K5B ,  K5C ,  K5D ,  K5E ,  K5F  }, \
    {  K60 ,  K61 ,  K62 ,  K63 ,  K64 ,  K65 ,  K66 ,  K67  }, \
    {  K68 ,  K69 ,  K6A ,  K6B ,  K6C ,  K6D ,  K6E ,  K6F  }, \
    {  K70 ,  K71 ,  K72 , KC_NO, KC_NO, KC_NO,  K76 ,  K77  }, \
    {  K78 ,  K79 ,  K7A ,  K7B , KC_NO,  K7D , KC_NO, KC_NO }  \
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  LAYOUT_combined(
      KC_HELP,              KC_NO,   KC_F1,KC_F2,KC_F3,KC_F4, KC_F5,KC_F6,KC_F7,KC_F8, KC_F9,KC_F10,KC_F11,KC_F12,   KC_PSCR,KC_SLCK,KC_PAUS,  KC_MUTE,KC_VOLD,KC_VOLU,KC_PWR,
      KC_STOP,   KC_AGAIN,  KC_ESC,KC_1,KC_2,KC_3,KC_4,KC_5,KC_6,KC_7,KC_8,KC_9,KC_0,KC_MINS,KC_EQL,KC_BSLS,KC_GRV,  KC_INS, KC_HOME,KC_PGUP,  KC_NLCK,KC_PSLS,KC_PAST,KC_PMNS,
      KC_MENU,   KC_UNDO,   KC_TAB,  KC_Q,KC_W,KC_E,KC_R,KC_T,KC_Y,KC_U,KC_I,KC_O,KC_P,KC_LBRC,KC_RBRC,  KC_BSPC,    KC_DEL, KC_END, KC_PGDN,  KC_P7,  KC_P8, KC_P9,  KC_PPLS,
      KC_SELECT, KC_COPY,   KC_LCTL,   KC_A,KC_S,KC_D,KC_F,KC_G,KC_H,KC_J,KC_K,KC_L,KC_SCLN,KC_QUOT,     KC_ENT,                               KC_P4,  KC_P5, KC_P6,
      KC_EXECUTE,KC_PASTE,  KC_LSFT,     KC_Z,KC_X,KC_C,KC_V,KC_B,KC_N,KC_M,KC_COMM,KC_DOT,KC_SLSH, KC_RSFT,KC_F14,          KC_UP,            KC_P1,  KC_P2, KC_P3,  KC_PENT,
      KC_FIND,   KC_CUT,    KC_CAPS,KC_LALT,KC_LGUI,            KC_SPC,                     KC_RGUI,KC_APP,KC_RALT,  KC_LEFT,KC_DOWN,KC_RGHT,      KC_P0,     KC_PDOT
                 ),
};
