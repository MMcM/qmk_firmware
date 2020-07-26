
#pragma once

#include "config_common.h"

#define VENDOR_ID         0xFEED
#define PRODUCT_ID        0xC085
#define DEVICE_VER        1
#define MANUFACTURER      QMK
#define PRODUCT           Atari CX85 keypad converter
#define DESCRIPTION       Atari CX85 keypad converter
                          
#define MATRIX_ROWS       1
#define MATRIX_COLS       32

// Not needed for real CX85, where the decoder chip does it, but may be for simpler hardware.
#define DEBOUNCE 5
