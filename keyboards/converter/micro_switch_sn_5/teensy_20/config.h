
#pragma once

#include "config_common.h"

#define PRODUCT           Micro Switch SN-series 5-key keypad converter

#define MATRIX_ROWS 1
#define MATRIX_COLS 5

// The Hall effect sensors behave closely enough to a switch to ground.
#define DIRECT_PINS {{ B6, B5, F7, F6, F5 }}

// The stepped black PB up/down keys are sink pulse, so low for less than 50us.
#define DEBOUNCE 0
