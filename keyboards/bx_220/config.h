#pragma once

#include "config_common.h"

#define PRODUCT           BX-220 keyboard converter

#define MATRIX_ROWS 8
#define MATRIX_COLS 14

#define MATRIX_ROW_PINS { E1, C0, C1, C2, C3, C4, C5, C6 }
#define MATRIX_COL_PINS { B4, B3, B2, B1, B0, E7, E6, F6, F5, F4, F1, F0, A1, A0 }
#define UNUSED_PINS
#define DIODE_DIRECTION ROW2COL

#define DEBOUNCE 5
#define MATRIX_HAS_GHOST

#define NLEDS 4
#define LED_PINS { C1, C2, C3, C0 }
#define LED_STROBE_PIN D6
