/* Copyright 2021 RaoulDuke-Esq
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include QMK_KEYBOARD_H

enum layers {
    _BASE,
    _ALT
};

enum macros {
    M_0 = SAFE_RANGE,
    M_1, M_2, M_3, M_4, M_5, M_6, M_7, M_8, M_9, M_10, M_11, M_12, M_13, M_14,
    M_1X, M_2X, M_3X, M_4X, M_5X, M_6X, M_7X, M_8X, M_9X, M_10X, M_11X, M_12X, M_13X, M_14X,
    M_P1, M_P2, M_P3, M_P4, M_P5, M_P6,
    M_P1X, M_P2X, M_P3X, M_P4X, M_P5X,
    M_S1, M_S2, M_S3, M_S4, M_S5,
};

/*
 * +---+   +---+---+---+---+---+---+---+---+---+---+
 * |ESC|   |F1 |F2 |F3 |F4 |F5 |F6 |F7 |F8 |F9 |F10|
 * +---+   +---+---+---+---+---+---+---+---+---+---+
 * +---+---+---+---+---+               +---+---+---+   +---+---+---+---+---+---+   +---+---+---+
 * |HLP|MEN|MUT|ISL|   |               |S1 |S2 |SVU|   |P1 |P2 |P3 |P4 |P5 |PVU|   |CRL|CHL|CAN|
 * +-------------------+               +-------|   |   +-------------------|   |   +-----------+
 * |ALT|PTX|DTX|ITX|   |               |S3 |S4 |   |   |P1X|P2X|P3X|P4X|P5X|   |   |PHONETX|CFN|
 * +---+---+---+---+---+               +---+---+---+   +---+---+---+---+---+---+   +-------+---+
 * +-------+---+---+---+---+---+---+---+---+   +---+---+---+       +---+---+---+   +---+---+---+
 * |MOD SEL|VLD|VLU|MMT|MMD|CFN|MFN|MHS|PVT|   |ARS|ECL|EDC|       |ALR|PLS|MRB|   | 1 | 2 | 3 |
 * +-------+---+---+---+---+---+---+---+---+   +---+---+---+       +---+---+---+   +-----------+
 * +---+---+---+---+---+---+---+   +---+---+---+---+---+---+---+                   | 4 | 5 | 6 |
 * |M1 |M2 |M3 |M4 |M5 |M6 |M7 |   |M1X|M2X|M3X|M4X|M5X|M6X|M7X|   +---+---+---+   +-----------+
 * +---------------------------+   +---------------------------+   |HOM|UP |PUP|   | 7 | 8 | 9 |
 * |M8 |M9 |M10|M11|M12|M13|M14|   |M8X|M9X|10X|11X|12X|13X|14X|   +-----------+   +-----------+
 * +---+---+---+---+---+---+---+   +---+---+---+---+---+---+---+   |LFT|HSC|RGT|   | * | 0 | # |
 *                         +-----------+                           +-----------+   +-----------+
 *                         |SELECTED TX|                           |END|DWN|PDN|   |CLR| ENTER |
 *                         +-----------+                           +---+---+---+   +---+-------+
 */

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_BASE] = LAYOUT(
    KC_ESC,         KC_F1,  KC_F2,  KC_F3,  KC_F4,  KC_F5,  KC_F6,  KC_F7,  KC_F8,  KC_F9,  KC_F10, \

    KC_HELP,KC_MENU,KC_A,   KC_B,   KC_C,                                   M_S1,   M_S2,   M_S5,           M_P1,   M_P2,   M_P3,   M_P4,   M_P5,   M_P6,           KC_G,   KC_H,   KC_I ,  \
   MO(_ALT),KC_PSCR,KC_D,   KC_E,   KC_F,                                   M_S3,   M_S4,                   M_P1X,  M_P2X,  M_P3X,  M_P4X,  M_P5X,                  KC_J,           KC_K,   \

    KC_L,           KC_VOLD,KC_VOLU,KC_MUTE,KC_M,   KC_N,   KC_O,   KC_P,   KC_Q,           KC_R,   KC_S,   KC_T,                   KC_U,   KC_V,   KC_W,           KC_P1,  KC_P2,  KC_P3,  \
                                                                                                                                                                    KC_P4,  KC_P5,  KC_P6,  \
    M_1,    M_2,    M_3,    M_4,    M_5,    M_6,    M_7,            M_1X,   M_2X,   M_3X,   M_4X,   M_5X,   M_6X,   M_7X,           KC_HOME,KC_UP,  KC_PGUP,        KC_P7,  KC_P8,  KC_P9,  \
    M_8,    M_9,    M_10,   M_11,   M_12,   M_13,   M_14,           M_8X,   M_9X,   M_10X,  M_11X,  M_12X,  M_13X,  M_14X,          KC_LEFT,KC_SLCK,KC_RGHT,        KC_PAST,KC_P0,  KC_PPLS,\
                                                    KC_Z,                                                                           KC_END, KC_DOWN,KC_PGDN,        KC_PDOT,KC_PENT         \
),
  [_ALT] = LAYOUT(
    QK_BOOT,        KC_F11, KC_F12, KC_F13, KC_F14, KC_F15, KC_F16, KC_F17, KC_F18, KC_F19, KC_F20, \

    _______,_______,_______,_______,DEBUG,                                  KC_F21, KC_F22, _______,        _______,_______,_______,_______,_______,_______,        _______,_______,_______,\
    _______,_______,_______,_______,_______,                                KC_F23, KC_F24,                 _______,_______,_______,_______,_______,                _______,        _______,\

    _______,        _______,_______,_______,_______,_______,_______,_______,_______,        _______,_______,_______,                _______,_______,_______,        _______,_______,_______,\
                                                                                                                                                                    _______,_______,_______,\
    _______,_______,_______,_______,_______,_______,_______,        _______,_______,_______,_______,_______,_______,_______,        _______,_______,_______,        _______,_______,_______,\
    _______,_______,_______,_______,_______,_______,_______,        _______,_______,_______,_______,_______,_______,_______,        _______,_______,_______,        _______,_______,_______,\
                                                    _______,                                                                        _______,_______,_______,        _______,_______         \
  )
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        switch (keycode) {
        case M_1:
            SEND_STRING("M1\n");
            break;
        case M_2:
            SEND_STRING("M2\n");
            break;
        case M_3:
            SEND_STRING("M3\n");
            break;
        case M_4:
            SEND_STRING("M4\n");
            break;
        case M_5:
            SEND_STRING("M5\n");
            break;
        case M_6:
            SEND_STRING("M6\n");
            break;
        case M_7:
            SEND_STRING("M7\n");
            break;
        case M_8:
            SEND_STRING("M8\n");
            break;
        case M_9:
            SEND_STRING("M9\n");
            break;
        case M_10:
            SEND_STRING("M10\n");
            break;
        case M_11:
            SEND_STRING("M11\n");
            break;
        case M_12:
            SEND_STRING("M12\n");
            break;
        case M_13:
            SEND_STRING("M13\n");
            break;
        case M_14:
            SEND_STRING("M14\n");
            break;
        case M_1X:
            SEND_STRING("M1X\n");
            break;
        case M_2X:
            SEND_STRING("M2X\n");
            break;
        case M_3X:
            SEND_STRING("M3X\n");
            break;
        case M_4X:
            SEND_STRING("M4X\n");
            break;
        case M_5X:
            SEND_STRING("M5X\n");
            break;
        case M_6X:
            SEND_STRING("M6X\n");
            break;
        case M_7X:
            SEND_STRING("M7X\n");
            break;
        case M_8X:
            SEND_STRING("M8X\n");
            break;
        case M_9X:
            SEND_STRING("M9X\n");
            break;
        case M_10X:
            SEND_STRING("M10X\n");
            break;
        case M_11X:
            SEND_STRING("M11X\n");
            break;
        case M_12X:
            SEND_STRING("M12X\n");
            break;
        case M_13X:
            SEND_STRING("M13X\n");
            break;
        case M_14X:
            SEND_STRING("M14X\n");
            break;
        case M_P1:
            SEND_STRING("P1\n");
            break;
        case M_P2:
            SEND_STRING("P2\n");
            break;
        case M_P3:
            SEND_STRING("P3\n");
            break;
        case M_P4:
            SEND_STRING("P4\n");
            break;
        case M_P5:
            SEND_STRING("P5\n");
            break;
        case M_P6:
            SEND_STRING("P6\n");
            break;
        case M_P1X:
            SEND_STRING("P1X\n");
            break;
        case M_P2X:
            SEND_STRING("P2X\n");
            break;
        case M_P3X:
            SEND_STRING("P3X\n");
            break;
        case M_P4X:
            SEND_STRING("P4X\n");
            break;
        case M_P5X:
            SEND_STRING("P5X\n");
            break;
        case M_S1:
            SEND_STRING("S1\n");
            break;
        case M_S2:
            SEND_STRING("S2\n");
            break;
        case M_S3:
            SEND_STRING("S3\n");
            break;
        case M_S4:
            SEND_STRING("S4\n");
            break;
        case M_S5:
            SEND_STRING("S5\n");
            break;
        }
    }
    return true;
}
