
#pragma once

// TODO: including this causes "error: expected identifier before '(' token" errors
//#include "config_common.h"

#define VENDOR_ID         0xFEED
#define PRODUCT_ID        0xD010
#define DEVICE_VER        1
#define MANUFACTURER      QMK
#define PRODUCT           Track House standard IIe tender keypad converter
#define DESCRIPTION       Track House standard IIe tender keypad converter

#define MATRIX_ROWS 5
#define MATRIX_COLS 8
#define MATRIX_COL_PINS { B16, B17, D0, A1, D4, D2, C6, C7 }
#define MATRIX_ROW_PINS { A2, D7, D3, C3, C4 }
#define UNUSED_PINS
#define DIODE_DIRECTION COL2ROW
