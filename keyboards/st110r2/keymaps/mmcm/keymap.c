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

#include QMK_KEYBOARD_H
#define _______ KC_TRNS               // Transparent key 
#define xxxxxxx KC_NO                 // Disable key
#define FN_APP LT(1, KC_APP)          // Tap = App Menu | Hold = Function layer 1

#define led_on_helper(port, pin) DDR ## port |=  (1<<pin); PORT ## port |=  (1<<pin)
#define led_on(x) led_on_helper(x)
#define led_off_helper(port, pin) DDR ## port &=  ~(1<<pin); PORT ## port &=  ~(1<<pin)
#define led_off(x) led_off_helper(x)

// LED pin definition 
// L00
#define left_led	B,7
// L01
#define center_led	D,0
// L02
#define right_led	D,1
// L03
#define num_led		B,5
// L04
#define keypad_led	B,4
// L05
#define scroll_led	B,6
// L06
#define fn_led		D,4
// L07
#define ralt_led	D,5
// L08
#define lgui_led	D,6
// L09
#define caps_led	D,7
#define sleep_led	right_led

uint16_t load_animation_counter = 0;
uint16_t unload_animation_counter = 0;

static bool keypad_led_animation = false;
static bool caps_led_animation = false;
static bool fn_led_animation = false;
static bool load_led_animation = false;
static bool unload_led_animation = false;
static bool unload_led_animation_start = false;

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  /* -------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
  // Blank layout template
  ,---------------------------------------------------------------------------------------------------------------------------------------------. 
  | ,-----.     ,-----------------------.  ,-----------------------.  ,-----------------------.  ,-----------------.                            | 
  | |     |     |     |     |     |     |  |     |     |     |     |  |     |     |     |     |  |     |     |     |                            | 
  | `-----'     `-----------------------'  `-----------------------'  `-----------------------'  `-----------------'           O     O     O    | 
  | ,-----------------------------------------------------------------------------------------.  ,-----------------.  ,-----------------------. | 
  | |     |     |     |     |     |     |     |     |     |     |     |     |     |     |     |  |     |     |     |  |     |     |     |     | | 
  | |-----------------------------------------------------------------------------------------|  |-----------------|  |-----------------------| | 
  | |       |     |     |     |     |     |     |     |     |     |     |     |     |         |  |     |     |     |  |     |     |     |     | | 
  | |--------------------------------------------------------------------------------         |  `-----------------'  |------------------     | | 
  | |        |     |     |     |     |     |     |     |     |     |     |     |     |        |                       |     |     |     |     | | 
  | |-----------------------------------------------------------------------------------------|        ,-----.        |-----------------------| | 
  | |           |     |     |     |     |     |     |     |     |     |     |     |           |        |     |        |     |     |     |     | | 
  | |-----------------------------------------------------------------------------------------|  ,-----------------.  |------------------     | | 
  | |      |     |      |     |                             |      |      |      |     |      |  |     |     |     |  |           |     |     | | 
  | `-----------------------------------------------------------------------------------------'  `-----------------'  `-----------------------' | 
  `---------------------------------------------------------------------------------------------------------------------------------------------' 
  [#] LAYOUT(
    _______,        _______,_______,_______,_______,    _______,_______,_______,_______,    _______,_______,_______,_______,   _______,_______,_______,
  
    _______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,   _______,_______,_______,   _______,_______,_______,_______,
    _______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,                   _______,_______,_______,   _______,_______,_______,
    _______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,        _______,                              _______,_______,_______,_______,
    _______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,        _______,           _______,           _______,_______,_______,
    _______,_______,_______,_______,         _______,   _______,   _______,         _______,_______,_______,_______,_______,   _______,_______,_______,   _______,        _______,_______), */
 

 
  /* -------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
  // Base layer
  ,---------------------------------------------------------------------------------------------------------------------------------------------.
  | ,-----.     ,-----------------------.  ,-----------------------.  ,-----------------------.  ,-----------------.                            |
  | | ESC |     | F1  | F2  | F3  | F4  |  | F5  | F6  | F7  | F8  |  | F9  | F10 | F11 | F12 |  | PRS | SCL | PAU |                            |
  | `-----'     `-----------------------'  `-----------------------'  `-----------------------'  `-----------------'           O     O     O    |
  | ,-----------------------------------------------------------------------------------------.  ,-----------------.  ,-----------------------. |
  | |  `  |  1  |  2  |  3  |  4  |  5  |  6  |  7  |  8  |  9  |  0  |  -  |  =  | xxx | BS  |  | INS |HOME | PGU |  | NUM |  /  |  *  |  -  | |
  | |-----------------------------------------------------------------------------------------|  |-----------------|  |-----------------------| |
  | |  TAB  |  Q  |  W  |  E  |  R  |  T  |  Y  |  U  |  I  |  O  |  P  |  [  |  ]  |         |  | DEL | END | PGD |  |  7  |  8  |  9  |     | |
  | |--------------------------------------------------------------------------------    ENT  |  `-----------------'  |------------------  +  | |
  | |  CAPS  |  A  |  S  |  D  |  F  |  G  |  H  |  J  |  K  |  L  |  ;  |  '  |  \  |        |                       |  4  |  5  |  6  |     | |
  | |-----------------------------------------------------------------------------------------|        ,-----.        |-----------------------| |
  | |  SHIFT    |  Z  |  X  |  C  |  V  |  B  |  N  |  M  |  ,  |  .  |  /  | xxx |  SHIFT    |        | UP  |        |  1  |  2  |  3  |     | |
  | |-----------------------------------------------------------------------------------------|  ,-----------------.  |------------------ ENT | |
  | | CTRL | OS  | ALT  | xxx |            SPACE            | xxx  | ALT  | OS   | FN  | CTRL |  |LEFT |DOWN |RIGHT|  |     0     |  .  |     | |
  | `-----------------------------------------------------------------------------------------'  `-----------------'  `-----------------------' |
  `---------------------------------------------------------------------------------------------------------------------------------------------' */
  [0] LAYOUT(
    KC_ESC,          KC_F1,  KC_F2,  KC_F3,  KC_F4,     KC_F5,  KC_F6,  KC_F7,  KC_F8,     KC_F9,  KC_F10,  KC_F11,  KC_F12,   KC_PSCR,KC_SLCK,KC_PAUS,  
  
    KC_GRAVE,KC_1,   KC_2,   KC_3,   KC_4,   KC_5,   KC_6,   KC_7,   KC_8,   KC_9,   KC_0,   KC_MINS,KC_EQL,xxxxxxx,KC_BSPC,   KC_INS, KC_HOME,KC_PGUP,   KC_NLCK,KC_PSLS,KC_PAST,KC_PMNS,
    KC_TAB, KC_Q,   KC_W,   KC_E,   KC_R,   KC_T,   KC_Y,   KC_U,   KC_I,   KC_O,   KC_P,   KC_LBRC,KC_RBRC,                   KC_DEL, KC_END, KC_PGDN,   KC_P7,  KC_P8,  KC_P9,  
    KC_CAPS,KC_A,   KC_S,   KC_D,   KC_F,   KC_G,   KC_H,   KC_J,   KC_K,   KC_L,   KC_SCLN,KC_QUOT,KC_BSLS,         KC_ENT,                              KC_P4,  KC_P5,  KC_P6,  KC_PPLS,  
    KC_LSFT,xxxxxxx,KC_Z,   KC_X,   KC_C,   KC_V,   KC_B,   KC_N,   KC_M,   KC_COMM,KC_DOT, KC_SLSH,xxxxxxx,        KC_RSFT,           KC_UP,             KC_P1,  KC_P2,  KC_P3,  
    KC_LCTL,KC_LGUI,KC_LALT,xxxxxxx,            xxxxxxx,KC_SPC,xxxxxxx,             xxxxxxx,KC_RALT,KC_RGUI,FN_APP, KC_RCTL,   KC_LEFT,KC_DOWN,KC_RGHT,   KC_P0,          KC_PDOT,KC_PENT),

 /* -------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
  // Function layer 1
  ,---------------------------------------------------------------------------------------------------------------------------------------------.
  | ,-----.     ,-----------------------.  ,-----------------------.  ,-----------------------.  ,-----------------.                            |
  | |     |     | PF1 | PF2 |     |     |  |     |     |     |     |  |     |     |     |     |  |     |     |     |                            |
  | `-----'     `-----------------------'  `-----------------------'  `-----------------------'  `-----------------'           O     O     O    |
  | ,-----------------------------------------------------------------------------------------.  ,-----------------.  ,-----------------------. |
  | |     |     |     |     |     |     |     |     |     |     |     |     |     |     |     |  |     |     |     |  |     |     |     |     | |
  | |-----------------------------------------------------------------------------------------|  |-----------------|  |-----------------------| |
  | |       |     |     |     |     |     |     |     |     |     |     |     |     |         |  |     |     |     |  |     |     |     |     | |
  | |--------------------------------------------------------------------------------         |  `-----------------'  |------------------     | |
  | |        |     |     |     |     |     |     |     |     |     |     |     |     |        |                       |     |     |     |     | |
  | |-----------------------------------------------------------------------------------------|        ,-----.        |-----------------------| |
  | |           |     |     |     |     |     |     |     | LR2 |     |     |     |           |        |     |        |     |     |     |     | |
  | |-----------------------------------------------------------------------------------------|  ,-----------------.  |------------------     | |
  | |      |     |      |     |                             |      |      | MENU |     |      |  |     |     |     |  |           |     |     | |
  | `-----------------------------------------------------------------------------------------'  `-----------------'  `-----------------------' |
  `---------------------------------------------------------------------------------------------------------------------------------------------' */
  [1] LAYOUT(
    _______,        _______,_______,_______,_______,    _______,_______,_______,_______,    _______,_______,_______,_______,   _______,_______,_______,
  
    _______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,   _______,_______,_______,   _______,_______,_______,_______,
    _______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,                   _______,_______,_______,   _______,_______,_______,
    _______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,        _______,                              _______,_______,_______,_______,
    _______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,        _______,           _______,           _______,_______,_______,
    _______,_______,_______,_______,         _______,   _______,   _______,         _______,_______,_______,_______,_______,   _______,_______,_______,   _______,        _______,_______),

};

// Animation tables
  static const uint16_t blinking_table[64] PROGMEM = {
    255, 255, 255, 255, 255, 255, 255, 200, 100, 75,  50,  25,  10,  5,   0,   0,
    255, 255, 255, 255, 255, 255, 255, 200, 100, 75,  50,  25,  10,  5,   0,   0,
    255, 255, 255, 255, 255, 255, 255, 200, 100, 75,  50,  25,  10,  5,   0,   0,
    255, 255, 255, 255, 255, 255, 255, 200, 100, 75,  50,  25,  10,  5,   0,   0
  };
  static const uint16_t load_left_table[64] PROGMEM = {
    0,   0,   0,   0,   0,   0,   5,   10,  25,  50,  75,  100, 150, 200, 255, 255, 
    255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
    255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
    255, 255, 255, 255, 255, 255, 255, 255, 200, 100, 75,  50,  25,  10,  5,   0  
  };
  static const uint16_t load_center_table[64] PROGMEM = {
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,  
    0,   0,   0,   0,   0,   0,   5,   10,  25,  50,  75,  100, 150, 200, 255, 255, 
    255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
    255, 255, 255, 255, 255, 255, 255, 255, 200, 100, 75,  50,  25,  10,  5,   0  
  };
  static const uint16_t load_right_table[64] PROGMEM = {
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,  
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,  
    0,   0,   0,   0,   0,   0,   5,   10,  25,  50,  75,  100, 150, 200, 255, 255, 
    255, 255, 255, 255, 255, 255, 255, 255, 200, 100, 75,  50,  25,  10,  5,   0  
  };
  static const uint16_t unload_right_table[64] PROGMEM = {
    200, 100, 75,  50,  25,  10,  5,   0,   0,   0,   0,   0,   0,   0,   0,   0,  
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,  
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,  
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0  
  };
  static const uint16_t unload_center_table[64] PROGMEM = {
    255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
    200, 100, 75,  50,  25,  10,  5,   0,   0,   0,   0,   0,   0,   0,   0,   0,  
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,  
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0  
  };
  static const uint16_t unload_left_table[64] PROGMEM = {
    255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
    255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
    200, 100, 75,  50,  25,  10,  5,   0,   0,   0,   0,   0,   0,   0,   0,   0,  
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0  
  };

// PWM timer
ISR(TIMER1_COMPA_vect) {
  static union {
    uint16_t row;
      struct {
        uint8_t count:8;
        uint8_t duration:1;
        uint8_t index:6;
      } pwm;
  } 
  timer = { .row = 0 };
  timer.row++;

  if (keypad_led_animation) {
    if (timer.pwm.count == 0 && pgm_read_byte(&blinking_table[timer.pwm.index]) != 0 )
      { led_on(keypad_led); }
    if (pgm_read_byte(&blinking_table[timer.pwm.index]) == timer.pwm.count || timer.pwm.count == pgm_read_byte(&blinking_table[timer.pwm.index]))
      { led_off(keypad_led); }
  }
  if (caps_led_animation) {
    if (timer.pwm.count == 0 && pgm_read_byte(&blinking_table[timer.pwm.index]) != 0 )
      { led_on(caps_led); }
    if (pgm_read_byte(&blinking_table[timer.pwm.index]) == timer.pwm.count || timer.pwm.count == pgm_read_byte(&blinking_table[timer.pwm.index]))
      { led_off(caps_led); }
  }
  if (fn_led_animation) {
    if (timer.pwm.count == 0 && pgm_read_byte(&blinking_table[timer.pwm.index]) != 0 )
      { led_on(fn_led); }
    if (pgm_read_byte(&blinking_table[timer.pwm.index]) == timer.pwm.count || timer.pwm.count == pgm_read_byte(&blinking_table[timer.pwm.index]))
      { led_off(fn_led); }
  }
  if (load_led_animation) {
    if (load_animation_counter == 0) {  timer.row = 0; }    
    if (timer.pwm.count == 0 && pgm_read_byte(&load_left_table[timer.pwm.index]) != 0)
      { led_on(left_led); }
    if (timer.pwm.count == pgm_read_byte(&load_left_table[timer.pwm.index]))
      { led_off(left_led); }
    if (timer.pwm.count == 0 && pgm_read_byte(&load_center_table[timer.pwm.index]) != 0)
      { led_on(center_led); }
    if (timer.pwm.count == pgm_read_byte(&load_center_table[timer.pwm.index]))
      { led_off(center_led); }
    if (timer.pwm.count == 0 && pgm_read_byte(&load_right_table[timer.pwm.index]) != 0)
      { led_on(right_led); }
    if (timer.pwm.count == pgm_read_byte(&load_right_table[timer.pwm.index]))
      { led_off(right_led); }
    load_animation_counter++;
    if (load_animation_counter >= 32500) {
      load_animation_counter = 0;
      load_led_animation = false;
      led_off(left_led);
      led_off(center_led);
      led_off(right_led);
    }
  }
  if (unload_led_animation) {
    if (unload_animation_counter == 0) {  timer.row = 0; }    
    if (timer.pwm.count == 0 && pgm_read_byte(&unload_left_table[timer.pwm.index]) != 0)
      { led_on(left_led); }
    if (timer.pwm.count == pgm_read_byte(&unload_left_table[timer.pwm.index]))
      { led_off(left_led); }
    if (timer.pwm.count == 0 && pgm_read_byte(&unload_center_table[timer.pwm.index]) != 0)
      { led_on(center_led); }
    if (timer.pwm.count == pgm_read_byte(&unload_center_table[timer.pwm.index]))
      { led_off(center_led); }
    if (timer.pwm.count == 0 && pgm_read_byte(&unload_right_table[timer.pwm.index]) != 0)
      { led_on(right_led); }
    if (timer.pwm.count == pgm_read_byte(&unload_right_table[timer.pwm.index]))
      { led_off(right_led); }
    unload_animation_counter++;
    if (unload_animation_counter >= 32500) {
      unload_animation_counter = 0;
      unload_led_animation = false;
      led_off(left_led);
      led_off(center_led);
      led_off(right_led);
    }
  }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  return true;
}

void matrix_init_user(void) {
  load_led_animation = true;
}

void matrix_scan_user(void) {
}

void led_set_user(uint8_t usb_led) {
  if ((1<<1 & layer_state) != 0) {
    fn_led_animation = true;
  }
  else {
    fn_led_animation = false;
    led_off(fn_led);
  }
  if ((1<<2 & layer_state) != 0 || (1<<3 & layer_state) != 0) {
    if ((1<<2 & layer_state) != 0) {
      keypad_led_animation = true;
    }
    else if ((1<<3 & layer_state) != 0) {
      keypad_led_animation = false;
      led_on(keypad_led);
    }
  }
  else {
    keypad_led_animation = false;
    led_off(keypad_led);
  }
  if ((1<<4 & layer_state) != 0) {
    led_on(lgui_led);
  }
  else {
    led_off(lgui_led);
  }
  if ((1<<5 & layer_state) != 0 || usb_led & (1<<USB_LED_CAPS_LOCK)) {
    if ((1<<5 & layer_state) != 0) {
      caps_led_animation = true;
    }
    else if (usb_led & (1<<USB_LED_CAPS_LOCK)) {
      caps_led_animation = false;
      led_on(caps_led);
      led_on(center_led);
    }
  }
  else {
    caps_led_animation = false;
    led_off(caps_led);
    led_off(center_led);
  }
  if ((1<<6 & layer_state) != 0) {
    unload_led_animation_start = true;
    led_on(left_led);
    led_on(center_led);
    led_on(right_led);
  }
  else if (unload_led_animation_start) {
    unload_led_animation = true;
    unload_led_animation_start = false;
  }
  if (usb_led & (1<<USB_LED_NUM_LOCK)) {
    led_on(num_led);
    led_on(left_led);
  }
  else {
    led_off(num_led);
    led_off(left_led);
  }
  if (usb_led & (1<<USB_LED_SCROLL_LOCK)) {
    led_on(scroll_led);
    led_on(right_led);
  }
  else {
    led_off(scroll_led);
    led_off(right_led);
  }
}
