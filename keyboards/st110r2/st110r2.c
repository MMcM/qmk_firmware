/* Copyright 2018 Yuki Rea <null-src.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "quantum.h"
#include "st110r2.h"
#include "led.h"
#include <stdint.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include <stdbool.h>

#define SLEEP_LED_TIMER_TOP F_CPU/(256*64)

void pwm_timer_init(void) {
  TCCR1B |= _BV(WGM12);
  TCCR1B |= _BV(CS10);
  uint8_t sreg = SREG;
  cli();
  OCR1AH = (SLEEP_LED_TIMER_TOP>>8)&0xff;
  OCR1AL = SLEEP_LED_TIMER_TOP&0xff;
  SREG = sreg;
}

void pwm_timer_enable(void) { TIMSK1 |= _BV(OCIE1A); } 
void pwm_timer_disable(void) { TIMSK1 &= ~_BV(OCIE1A); }

void matrix_init_kb(void) {
  // put your keyboard start-up code here
  // runs once when the firmware starts up
  pwm_timer_init();
  pwm_timer_enable();
  matrix_init_user();
}

void matrix_scan_kb(void) {
  // put your looping keyboard code here
  // runs every cycle (a lot)
  matrix_scan_user();
}

bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
  // put your per-action keyboard code here
  // runs for every action, just before processing by the firmware
  return process_record_user(keycode, record);
}

void led_set_kb(uint8_t usb_led) {
led_set_user(usb_led);
}

