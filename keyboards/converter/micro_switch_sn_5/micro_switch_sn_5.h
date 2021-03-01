
#pragma once

#include "quantum.h"

#if MATRIX_COLS == 5
#define LAYOUT(K1, K2, K3, K4, K5) { { K1, K2, K3, K4, K5 } }
#elif MATRIX_COLS == 3
#define LAYOUT(K1, K2, K3, K4, K5) { { K2, K3, K4 } }
#else
#error unsupported number of cols
#endif
