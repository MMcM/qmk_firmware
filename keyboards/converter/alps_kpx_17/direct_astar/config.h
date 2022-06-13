
#pragma once

#include "config_common.h"
                          
#define PRODUCT           Alps KP-17 keypad converter

#define MATRIX_ROWS       5
#define MATRIX_COLS       4
#define MATRIX_ROW_PINS { D2, D3, D1, D0, D4 }
#define MATRIX_COL_PINS { C6, D7, E6, B4 }
#define UNUSED_PINS
#define DIODE_DIRECTION ROW2COL
#define DEBOUNCE 5
