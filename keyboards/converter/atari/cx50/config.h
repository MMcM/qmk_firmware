
#pragma once

#include "config_common.h"

#define VENDOR_ID         0xFEED
#define PRODUCT_ID        0xC050
#define DEVICE_VER        1
#define MANUFACTURER      QMK
#define PRODUCT           Atari CX50 keypad converter
#define DESCRIPTION       Atari CX50 keypad converter
                          
#define MATRIX_ROWS       4
#define MATRIX_COLS       3
#define MATRIX_ROW_PINS { B0, B1, B2, B3 }
#define MATRIX_COL_PINS { F1, F0, D0 }
#define UNUSED_PINS
#define DIODE_DIRECTION COL2ROW
#define DEBOUNCE 5
