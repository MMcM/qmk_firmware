#include "cherry_4060_a.h"

#ifdef LED_MATRIX_ENABLE
const led_matrix g_leds[LED_DRIVER_LED_COUNT] = {
  { { .row = 7, .col = 3 }, { .x = 1, .y = 0 } },
  { { .row = 7, .col = 2 }, { .x = 2, .y = 0 } },
  { { .row = 7, .col = 1 }, { .x = 3, .y = 0 } },
  { { .row = 7, .col = 0 }, { .x = 4, .y = 0 } },
  { { .row = 0, .col = 3 }, { .x = 0, .y = 1 } },
  { { .row = 0, .col = 2 }, { .x = 1, .y = 1 } },
  { { .row = 0, .col = 1 }, { .x = 2, .y = 1 } },
  { { .row = 0, .col = 0 }, { .x = 3, .y = 1 } },
  { { .row = 1, .col = 3 }, { .x = 4, .y = 1 } },
  { { .row = 1, .col = 2 }, { .x = 5, .y = 1 } },
  { { .row = 1, .col = 1 }, { .x = 0, .y = 2 } },
  { { .row = 1, .col = 0 }, { .x = 1, .y = 2 } },
  { { .row = 2, .col = 3 }, { .x = 2, .y = 2 } },
  { { .row = 2, .col = 2 }, { .x = 3, .y = 2 } },
  { { .row = 2, .col = 1 }, { .x = 4, .y = 2 } },
  { { .row = 2, .col = 0 }, { .x = 5, .y = 2 } },
  { { .row = 3, .col = 3 }, { .x = 0, .y = 3 } },
  { { .row = 3, .col = 2 }, { .x = 1, .y = 3 } },
  { { .row = 3, .col = 1 }, { .x = 2, .y = 3 } },
  { { .row = 3, .col = 0 }, { .x = 3, .y = 3 } },
  { { .row = 4, .col = 3 }, { .x = 4, .y = 3 } },
  { { .row = 4, .col = 2 }, { .x = 5, .y = 3 } },
  { { .row = 4, .col = 1 }, { .x = 0, .y = 4 } },
  { { .row = 4, .col = 0 }, { .x = 1, .y = 4 } },
  { { .row = 5, .col = 3 }, { .x = 2, .y = 4 } },
  { { .row = 5, .col = 2 }, { .x = 3, .y = 4 } },
  { { .row = 5, .col = 1 }, { .x = 4, .y = 4 } },
  { { .row = 5, .col = 0 }, { .x = 5, .y = 4 } },
  { { .row = 6, .col = 3 }, { .x = 1, .y = 5 } },
  { { .row = 6, .col = 2 }, { .x = 2, .y = 5 } },
  { { .row = 6, .col = 1 }, { .x = 3, .y = 5 } },
  { { .row = 6, .col = 0 }, { .x = 4, .y = 5 } }
};
#endif
