#pragma once

#include "config_common.h"

/* USB Device descriptor parameter */
#define PRODUCT_ID      0x0161
#define DEVICE_VER      0x0001

/* key matrix pins */
#define MATRIX_ROW_PINS { A2, A1, A0, B8 }
#define MATRIX_COL_PINS { B7, B6, B5, B4 }
#define UNUSED_PINS

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION COL2ROW

/* Set 0 if debouncing isn't needed */
#define DEBOUNCE 5
