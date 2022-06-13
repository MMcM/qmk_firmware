
#pragma once

#include "config_common.h"

#ifdef VT50H
#define PRODUCT           VT50H keyboard converter
#else
#define PRODUCT           VT50 keyboard converter
#endif

#ifdef VT50H
#define MATRIX_ROWS       10
#else
#define MATRIX_ROWS       8
#endif
#define MATRIX_COLS       8
