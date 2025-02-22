#ifdef SERIAL_MOUSE_ENABLE

#include "quantum.h"
#include "uart.h"

static inline void serial_mouse_init(void) {
    uart_init(1200);

    /* Turn on DTR via PC6 by setting T2IN low = space = asserted */ \
#define DTR_PIN C6
    setPinOutput(DTR_PIN);
#if 0
    writePinHigh(DTR_PIN);
    wait_ms(100);
#endif
    writePinLow(DTR_PIN);
}

void keyboard_post_init_kb(void) {
    serial_mouse_init();
    keyboard_post_init_user();
}

extern void serial_mouse_task(void);

void housekeeping_task_kb(void) {
    serial_mouse_task();
}

#endif
