
#pragma once

#include "config_common.h"

#define PRODUCT           Geac 8340 keyboard converter
                          
#define MATRIX_ROWS       8
#define MATRIX_COLS       16

// PIN_ADDR and PIN_CLOCK directly control the serial-to-parallel shift register U3 (74LS164).
// The last bit into the SR (QA) selects one of two demultiplexers U1 and U2 (74LS156),
// roughly the left and ride sides of the keyboard.
// The previous three bits (QB, QC, QD) are the select lines for both demuxes.
// These four bits drive exactly one column in the matrix low and the rest high.
// The first bit (QH) into the SR is not connected, but must be accounted for in serial output.
// The next three bits (QE, QF, QG) are the select lines for the multiplexer U4 (74LS251).
// They read one row of the matrix.
// PIN_KEY is the inverting output of the mux (W). It is high if the switch is closed at the selected position.
// The clock line also drives the mux's gate, so the output is hi-Z when not active.
// A pull-up resistor is therefore inappropriate; a pull-down resistor could be added, but isn't really necessary.
// The choice of key codes and the row and column designations are arbitrary, provided that all 127 patterns are checked.
// This gives codes that (roughly) correspond to the physical layout of keys.
// The remaining output gives the state of the jumper J2, which has a pull-up.

#define PIN_ADDR D3
#define PIN_CLOCK D0
#define PIN_KEY D2
#define PIN_J2 D1

#define KEY_ADDR(row, col) ((row << 1) | (col << 4))
