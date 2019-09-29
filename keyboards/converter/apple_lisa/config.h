
#pragma once

#include "config_common.h"

#define VENDOR_ID         0xFEED
#define PRODUCT_ID        0xADD7
#define DEVICE_VER        1
#define MANUFACTURER      QMK
#define PRODUCT           Apple Lisa keyboard converter
#define DESCRIPTION       Apple Lisa keyboard converter
                          
#define MATRIX_ROWS       16
#define MATRIX_COLS       8

// Both Shift keys send the same code, so make COMMAND be both Option keys instead.
#define IS_COMMAND() (get_mods() == MOD_MASK_ALT)
