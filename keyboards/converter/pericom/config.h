
#pragma once

// TODO: some problem with GPIO macros
//#include "config_common.h"

#define VENDOR_ID         0xFEED
#define PRODUCT_ID        0x2506
#define DEVICE_VER        1
#define MANUFACTURER      QMK
#define PRODUCT           Pericom keyboard converter
#define DESCRIPTION       Pericom keyboard converter

#define MATRIX_ROWS       8
#define MATRIX_COLS       16

#define CUSTOM_MATRIX 2
#define DIODE_DIRECTION CUSTOM_MATRIX
#define init_pins() NULL
