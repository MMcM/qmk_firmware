
#pragma once

#include "config_common.h"

#define PRODUCT           HP 2645A keyboard converter

#define MATRIX_ROWS       14
#define MATRIX_COLS       8

#define LOCKING_SUPPORT_ENABLE
#define LOCKING_RESYNC_ENABLE

// BUS on PB<0:7>
#define BUS_PIN PINB
#define BUS_PORT PORTB
#define BUS_DDR DDRB

// BADDR on PD<0:3>
#define BADDR_PORT PORTD
#define BADDR_DDR DDRD
#define BADDR_MASK 0x0F

// READ /COL15 on PD7
#define READ_PORT PORTD
#define READ_DDR DDRD
#define READ_MASK (1<<7)

// COL OUT on PF4
#define COL_OUT_PORT PORTF
#define COL_OUT_DDR DDRF
#define COL_OUT_MASK (1<<4)

// LED OUT on PF5
#define LED_OUT_PORT PORTF
#define LED_OUT_DDR DDRF
#define LED_OUT_MASK (1<<5)

// RESET on PC7
#define RESET_PIN PINC
#define RESET_PORT PORTC
#define RESET_DDR DDRC
#define RESET_MASK (1<<7)

// BEEP on PC6
#define AUDIO_PIN C6
