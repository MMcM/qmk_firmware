
#include QMK_KEYBOARD_H

enum layers {
  ASCII,
  APL_UNSHIFTED,
  APL_SHIFTED
};

enum user_keycodes {
  LOW_SPEED = SAFE_RANGE,
  APL,
  HALF_DUP,
  ON_LINE,

  OVERSTRIKE
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/*
 *   +---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+
 *   | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 0 | - | = | `|BS |BRK|
 * +-+-----------------------------------------------------------+-+
 * |ESC| Q | W | E | R | T | Y | U | I | O | P | [ | \ | { |LF |HIS|
 * ++-------------------------------------------------------------++
 *  |CTL| A | S | D | F | G | H | J | K | L | ; | ' |RETRN|DEL|PAV|
 *  +---------------------------------------------------+-+---+---+
 *  |SHIFT| Z | X | C | V | B | N | M | , | . | / |SHIFT| [SPD]
 *  +-----+---+-------------------------------+---+-----+
 *    [APL]   |                               |    [DUP]  [ONL]
 *            +-------------------------------+
 */
  [ASCII] = LAYOUT(
    KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINUS, KC_EQUAL, KC_GRAVE, KC_BSPACE, KC_PAUSE, \
    KC_ESC, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_LBRACKET, KC_BSLASH, KC_RBRACKET, OVERSTRIKE, KC_RALT, \
    KC_LCTRL, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCOLON, KC_QUOTE, KC_ENTER, KC_DEL, KC_PGDN, \
    KC_LSHIFT, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMMA, KC_DOT, KC_SLASH, KC_RSHIFT, LOW_SPEED, \
    APL, KC_SPACE, HALF_DUP, ON_LINE \
  ),

/*
 *   +---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+
 *   |   |   |   |   |   |   |   |   |   |   | − | × | ⋄ |   |   |
 * +-+-----------------------------------------------------------+-+
 * |   |   |   |   |   |   |   |   |   |   |   | ← | ⊢ | { |   |   |
 * ++-------------------------------------------------------------++
 *  |   |   |   |   |   |   |   |   |   |   | [ | ] |     |   |   |
 *  +---------------------------------------------------+-+---+---+
 *  |     |   |   |   |   |   |   |   | , | . | / |     | [   ]
 *  +-----+---+-------------------------------+---+-----+
 *    [   ]   |                               |    [   ]  [   ]
 *            +-------------------------------+
 */
  [APL_UNSHIFTED] = LAYOUT(
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, UC(0x2212), UC(0x00D7), UC(0x22C4), _______, _______, \
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, UC(0x2190), UC(0x22A2), UC(0x007B), _______, _______, \
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, UC(0x005B), UC(0x005D), _______, _______, _______, \
    _______, _______, _______, _______, _______, _______, _______, _______, UC(0x002C), UC(0x002E), UC(0x002F), _______, _______, \
    _______, _______, _______, _______ \
  ),

/*
 *   +---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+
 *   | ¨ | ¯ | < | ≤ | = | ≥ | > | ≠ | ∨ | ∧ | + | ÷ | $ |   |   |
 * +-+-----------------------------------------------------------+-+
 * |   | ? | ⍵ | ∊ | ⍴ | ∼ | ↑ | ↓ | ⍳ | ○ | ⋆ | → | ⊣ | } |   |   |
 * ++-------------------------------------------------------------++
 *  |   | ⍺ | ⌈ | ⌊ | _ | ∇ | ∆ | ∘ | ' | ⎕ | ( | ) |     |   |   |
 *  +---------------------------------------------------+-+---+---+
 *  |     | ⊂ | ⊃ | ∩ | ∪ | ⊥ | ⊤ | ∣ | ; | : | \ |     | [   ]
 *  +-----+---+-------------------------------+---+-----+
 *    [   ]   |                               |    [   ]  [   ]
 *            +-------------------------------+
 */
  [APL_SHIFTED] = LAYOUT(
    UC(0x00A8), UC(0x00AF), UC(0x003C), UC(0x2264), UC(0x003D), UC(0x2265), UC(0x003E), UC(0x2260), UC(0x2228), UC(0x2227), UC(0x002B), UC(0x00F7), UC(0x0024), _______, _______, \
    _______, UC(0x003F), UC(0x2375), UC(0x220A), UC(0x2374), UC(0x223C), UC(0x2191), UC(0x2193), UC(0x2373), UC(0x25CB), UC(0x22C6), UC(0x2192), UC(0x22A3), UC(0x007D), _______, _______, \
    _______, UC(0x237A), UC(0x2308), UC(0x230A), UC(0x005F), UC(0x2207), UC(0x2206), UC(0x2218), UC(0x0027), UC(0x2395), UC(0x0028), UC(0x0029), _______, _______, _______, \
    _______, UC(0x2282), UC(0x2283), UC(0x2229), UC(0x222A), UC(0x22A5), UC(0x22A4), UC(0x2223), UC(0x003B), UC(0x003A), UC(0x005C), _______, _______, \
    _______, _______, _______, _______ \
  )
} ;

#define APL_LAYERS ((1 << APL_UNSHIFTED) | (1 << APL_SHIFTED))

static void set_apl_layer(void) {
    uint8_t shifts = matrix_get_row(MATRIX_ROWS - 1);
    layer_state_t old_state = layer_state;
    layer_state_t new_state = layer_state & ~APL_LAYERS;
    if ((shifts & (1 << 4)) != 0) {
        // APL switch on
        if ((shifts & (1 << 0)) == 0) {
            // CTRL not pressed
            if ((shifts & (1 << 1)) != 0) {
                // SHIFT pressed
                new_state |= (1 << APL_SHIFTED);
            } else {
                new_state |= (1 << APL_UNSHIFTED);
            }
        }
    }
    if (old_state != new_state) {
        layer_state_set(new_state);
    }
}

const uint16_t PROGMEM overstrikes[] = {
    0x0027, 0x002E, 0x0021,     // ' . !
    0x0027, 0x2395, 0x235E,     // ' ⎕ ⍞
    0x22C6, 0x00A8, 0x2363,     // ⋆ ¨ ⍣
    0x22C6, 0x25CB, 0x235F,     // ⋆ ○ ⍟
    0x002C, 0x2212, 0x236A,     // , − ⍪
    0x2212, 0x002F, 0x233F,     // − / ⌿
    0x2212, 0x005C, 0x2340,     // − \ ⍀
    0x2212, 0x2223, 0x026B,     // − ∣ ɫ
    0x2212, 0x25CB, 0x2296,     // − ○ ⊖
    0x003A, 0x2395, 0x2360,     // : ⎕ ⍠
    0x003D, 0x005F, 0x2261,     // = _ ≡
    0x003D, 0x2395, 0x2338,     // = ⎕ ⌸
    0x005C, 0x25CB, 0x2349,     // \ ○ ⍉
    0x005F, 0x2206, 0x2359,     // _ ∆ ⍙
    0x005F, 0x220A, 0x2377,     // _ ∊ ⍷
    0x005F, 0x2260, 0x2262,     // _ ≠ ≢
    0x005F, 0x2282, 0x2286,     // _ ⊂ ⊆
    0x005F, 0x2373, 0x2378,     // _ ⍳ ⍸
    0x005F, 0x2375, 0x2379,     // _ ⍵ ⍹
    0x005F, 0x237A, 0x2376,     // _ ⍺ ⍶
    0x2223, 0x2206, 0x234B,     // ∣ ∆ ⍋
    0x2223, 0x2207, 0x2352,     // ∣ ∇ ⍒
    0x2223, 0x2282, 0x00A2,     // ∣ ⊂ ¢
    0x2223, 0x25CB, 0x233D,     // ∣ ○ ⌽
    0x223C, 0x00A8, 0x2368,     // ∼ ¨ ⍨
    0x223C, 0x2207, 0x236B,     // ∼ ∇ ⍫
    0x223C, 0x2227, 0x2372,     // ∼ ∧ ⍲
    0x223C, 0x2228, 0x2371,     // ∼ ∨ ⍱
    0x00A8, 0x2207, 0x2362,     // ¨ ∇ ⍢
    0x00A8, 0x2218, 0x2364,     // ¨ ∘ ⍤
    0x00A8, 0x25CB, 0x2365,     // ¨ ○ ⍥
    0x00F7, 0x2395, 0x2339,     // ÷ ⎕ ⌹
    0x2218, 0x2229, 0x235D,     // ∘ ∩ ⍝
    0x2218, 0x22A4, 0x2355,     // ∘ ⊤ ⍕
    0x2218, 0x22A5, 0x234E,     // ∘ ⊥ ⍎
    0x22A4, 0x22A5, 0x2336,     // ⊤ ⊥ ⌶
    0x22C4, 0x2395, 0x233A,     // ⋄ ⎕ ⌺
};

static uint16_t get_overstrike(uint16_t u1, uint16_t u2) {
    for (uint8_t i = 0; i < sizeof(overstrikes)/sizeof(overstrikes[0]); i += 3) {
        uint16_t o1 = pgm_read_word(overstrikes + i);
        uint16_t o2 = pgm_read_word(overstrikes + i + 1);
        if (((u1 == o1) && (u2 == o2)) || ((u1 == o2) && (u2 == o1))) {
            return pgm_read_word(overstrikes + i + 2);
        }
    }
    return 0;
}

void keyboard_post_init_user(void) {
    unicode_config.input_mode = UC_LNX;
    turn_off_led();
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    static uint16_t last_unicode = 0;
    static bool last_unicode_overstrike = false;
    
    switch (keycode) {
    case LOW_SPEED:
        unicode_config.input_mode = UC_WINC;
        break;
    case APL:
    case KC_LCTRL:
    case KC_LSHIFT:
        set_apl_layer();
        break;
    case HALF_DUP:
        break;
    case ON_LINE:
        if (record->event.pressed) {
            turn_on_led();
        } else {
            turn_off_led();
        }
        break;

    case OVERSTRIKE:
        if (last_unicode != 0) {
            last_unicode_overstrike = true;
            PORTD |= (1 << 6);
        }
        break;
    default:
        if (record->event.pressed) {
            if (last_unicode_overstrike) {
                last_unicode_overstrike = false;
                PORTD &= ~(1 << 6);
                if (keycode >= QK_UNICODE && keycode <= QK_UNICODE_MAX) {
                    uint16_t overstrike = get_overstrike(last_unicode, keycode & 0x7FFF);
                    dprintf("Overstrike: %04X %04X %04X\n", last_unicode, keycode, overstrike);
                    if (overstrike != 0) {
                        tap_code(KC_BSPACE);
                        unicode_input_start();
                        register_hex(overstrike);
                        unicode_input_finish();
                        return false;
                    }
                }
            }
            if (keycode >= QK_UNICODE && keycode <= QK_UNICODE_MAX) {
                last_unicode = keycode & 0x7FFF;
            } else {
                last_unicode = 0;
            }
        }
        break;
    }

    return true;
}
