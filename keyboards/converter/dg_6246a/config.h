
#pragma once

#include "config_common.h"

#define PRODUCT           DG 6246A keyboard converter

#define MATRIX_ROWS       8
#define MATRIX_COLS       16

#define DATA_DDR DDRD
#define DATA_PIN PIND
#define DATA_PORT PORTD
#define KBIRQ_MASK (1 << 0)
#define SCLK_MASK (1 << 1)
#define SI_MASK (1 << 2)
#define SO_MASK (1 << 3)
#define KBIRQ_VECT INT0_vect
#define SCLK_VECT INT1_vect

#define RESET_DDR DDRC
#define RESET_PORT PORTC
#define RESET_MASK (1 << 7)
