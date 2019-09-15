
#pragma once

#include "config_common.h"

#define VENDOR_ID       0xFEED
#define PRODUCT_ID      0x0000
#define DEVICE_VER      0x000A
#define MANUFACTURER    NMB
#define PRODUCT         111262
#define DESCRIPTION     QMK for NMB 111262 keyboard

#define MATRIX_ROWS 8
#define MATRIX_COLS 8

// J1 - 16-pin: row 7-0 followed by col 7-0.
// Just wire around a Teensy 2.0.
#define MATRIX_ROW_PINS { D2, D1, D0, B7, B3, B2, B1, B0 }
#define MATRIX_COL_PINS { B5, B6, F7, F6, F5, F4, F1, F0 }
#define UNUSED_PINS

#define DEBOUNCE 5

#define MATRIX_HAS_GHOST
