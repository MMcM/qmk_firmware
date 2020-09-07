
#pragma once

// TODO: some problem with GPIO macros
//#include "config_common.h"

#define VENDOR_ID         0xFEED
#define PRODUCT_ID        0x1518
#define DEVICE_VER        1
#define MANUFACTURER      QMK
#define PRODUCT           CTM keyboard converter
#define DESCRIPTION       CTM keyboard converter

#define MATRIX_ROWS       14
#define MATRIX_COLS       8

#define CUSTOM_MATRIX 2
#define DIODE_DIRECTION CUSTOM_MATRIX
#define init_pins() NULL
