#include "ti_silent_743.h"

void turn_off_led(void) {
    PORTC |= (1 << 7);
}

void turn_on_led(void) {
    PORTC &= ~(1 << 7);
}    
