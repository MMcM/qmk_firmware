
#pragma once

#include "quantum.h"

#define LAYOUT( \
    K_1, K_2, K_3, \
    K_4, K_5, K_6, \
    K_7, K_8, K_9, \
    K_STAR, K_0, K_HASH \
){ \
    { K_1, K_2, K_3, }, \
    { K_4, K_5, K_6, }, \
    { K_7, K_8, K_9, }, \
    { K_STAR, K_0, K_HASH } \
}
