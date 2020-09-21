
#pragma once

// TODO: some problem with GPIO macros
//#include "config_common.h"

#define VENDOR_ID         0xFEED
#define PRODUCT_ID        0x1700
#define DEVICE_VER        1
#define MANUFACTURER      QMK
#define PRODUCT           Alps KPX-17S keypad converter
#define DESCRIPTION       Alps KPX-17S keypad converter

#define MATRIX_ROWS       5
#define MATRIX_COLS       4

#define KPX_17S

#define CUSTOM_MATRIX 2
#define DIODE_DIRECTION CUSTOM_MATRIX
#define init_pins() NULL
