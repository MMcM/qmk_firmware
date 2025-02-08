
#include "quantum.h"
#include "led.h"

#define LED_DDR DDRC
#define LED_PORT PORTC
#define LED_KANA_MASK (1 << 6)
#define LED_CAPS_MASK (1 << 7)

void led_init_ports(void) {
    LED_DDR |= (LED_KANA_MASK | LED_CAPS_MASK);
    LED_PORT |= (LED_KANA_MASK | LED_CAPS_MASK);
}

void led_update_ports(led_t led_state) {
    if (led_state.caps_lock) {
        LED_PORT &= ~LED_CAPS_MASK;
    } else {
        LED_PORT |= LED_CAPS_MASK;
    }
    if (led_state.kana) {
        LED_PORT &= ~LED_KANA_MASK;
    } else {
        LED_PORT |= LED_KANA_MASK;
    }
}
