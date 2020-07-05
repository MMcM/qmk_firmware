
#pragma once

// TODO: including this causes "error: expected identifier before '(' token" errors
//#include "config_common.h"

#define VENDOR_ID       0xFEED
#define PRODUCT_ID      0x0000
#define DEVICE_VER      0x0001
#define MANUFACTURER    Omron
#define PRODUCT         QMK for Omron turbo
#define DESCRIPTION     QMK for laptop keyboard with Turbo button and Omron switches

#define MATRIX_ROWS 12
#define MATRIX_COLS 8

#define DIODE_DIRECTION COL2ROW
#define MATRIX_ROW_PINS { C2, C1, D6, D5, B2, B3, B1, B0, C0, D1, D3, C3 }
#define MATRIX_COL_PINS { B16, B17, D0, A1, A2, D7, D4, D2 }
//#define DIRECT_PINS { { C6 }, { C7 } }
#define UNUSED_PINS

#define DEBOUNCE 5
