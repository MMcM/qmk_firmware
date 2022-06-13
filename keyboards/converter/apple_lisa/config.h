
#pragma once

#include "config_common.h"

#define PRODUCT           Apple Lisa keyboard converter

#define MATRIX_ROWS       16
#define MATRIX_COLS       8

// Both Shift keys send the same code, so make COMMAND be both Option keys instead.
#define IS_COMMAND() (get_mods() == MOD_MASK_ALT)
