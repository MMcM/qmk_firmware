
#pragma once

#if defined(HP_2621)
#define PRODUCT_ID        0x2621
#define PRODUCT           HP 2621 keyboard converter
#elif defined(HP_2622)
#define PRODUCT_ID        0x2622
#define PRODUCT           HP 2622 keyboard converter
#else
#define PRODUCT_ID        0x2620
#define PRODUCT           HP 262x keyboard converter
#endif

#define MATRIX_ROWS       8
#define MATRIX_COLS       16
