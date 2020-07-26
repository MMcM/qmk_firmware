
#pragma once

#include "quantum.h"

#define LAYOUT( \
    K_ESC,  K_7, K_8, K_9,  K_MINUS, \
    K_NO,   K_4, K_5, K_6,  K_ENT,   \
    K_DEL,  K_1, K_2, K_3,           \
    K_YES,  K_0,      K_DOT          \
){ { \
   [0b11100] = K_0,     \
   [0b11001] = K_1,     \
   [0b11010] = K_2,     \
   [0b11011] = K_3,     \
   [0b10001] = K_4,     \
   [0b10010] = K_5,     \
   [0b10011] = K_6,     \
   [0b10101] = K_7,     \
   [0b10110] = K_8,     \
   [0b10111] = K_9,     \
   [0b11101] = K_DOT,   \
   [0b11111] = K_MINUS, \
   [0b11110] = K_ENT,   \
   [0b01100] = K_ESC,   \
   [0b10100] = K_NO,    \
   [0b10000] = K_DEL,   \
   [0b11000] = K_YES,   \
} }
