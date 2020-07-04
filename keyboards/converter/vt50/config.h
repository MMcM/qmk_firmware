
#pragma once

#include "config_common.h"

#define VENDOR_ID         0xFEED
#ifdef VT50H
#define PRODUCT_ID        0x0052
#else
#define PRODUCT_ID        0x050A
#endif
#define DEVICE_VER        1
#define MANUFACTURER      QMK
#ifdef VT50H
#define PRODUCT           VT50H keyboard converter
#define DESCRIPTION       VT50H keyboard converter
#else
#define PRODUCT           VT50 keyboard converter
#define DESCRIPTION       VT50 keyboard converter
#endif

#ifdef VT50H
#define MATRIX_ROWS       10
#else
#define MATRIX_ROWS       8
#endif
#define MATRIX_COLS       8
