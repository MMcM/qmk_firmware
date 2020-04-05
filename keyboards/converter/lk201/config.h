
#pragma once

// TODO: some problem with GPIO macros
//#include "config_common.h"

#define VENDOR_ID         0xDEC0
#define PRODUCT_ID        0x0201
#define DEVICE_VER        1
#define MANUFACTURER      QMK
#define PRODUCT           LK201 keyboard converter
#define DESCRIPTION       LK201 keyboard converter

#define MATRIX_ROWS       16
#define MATRIX_COLS       16

#define CUSTOM_MATRIX 2
#define DIODE_DIRECTION CUSTOM_MATRIX
#define init_pins() NULL
