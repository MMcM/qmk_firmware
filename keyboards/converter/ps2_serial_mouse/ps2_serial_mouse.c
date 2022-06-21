
#include "ps2_serial_mouse.h"
#include <avr/io.h>
#include "quantum.h"

#ifdef SERIAL_MOUSE_ENABLE

#include "serial_mouse.h"

void keyboard_post_init_kb(void) {
    serial_mouse_init();
    keyboard_post_init_user();
}

void housekeeping_task_kb(void) {
    serial_mouse_task();
}

#endif
