
#include QMK_KEYBOARD_H
#define AC_FN0 M(0)                          //Test
#define AC_FN1 M(1)                          //Desktop Right
#define AC_FN2 M(2)                          //Desktop Left
#define AC_FN3 M(3)                          //New Explorer On Windows
#define AC_FN4 M(4)                          //Snip Tool Windows
#define AC_FN5 M(5)                          //V-Desktop Up
#define AC_FN6 M(6)                          //Min All
#define AC_FN7 M(7)                          //Paste
#define AC_FN8 M(8)                          //Copy All
#define AC_FN9 M(9)                          //Task Manager
#define AC_FN10 M(10)                        //Double Zero
#define AC_FN11 M(11)                        //BLANK
#define AC_FN12 M(12)                        //BLANK
#define AC_FN13 M(13)                        //BLANK
#define AC_FN14 M(14)                        //BLANK

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt) {
            switch(id) {
            case 0:  {               //TEST
                if (record->event.pressed) {
                      return  MACRO( I(0), T(CAPS), END ) ;
            }else{
                     }
            break;
        }
            case 1: {                 //Desktop Right
               if (record->event.pressed) {
                      return  MACRO( I(0), D(LGUI), D(LCTL), T(RGHT), U(LGUI), U(LCTL), END ) ;
                      }else{
                     }
            break;
        }
            case 2:   {               //Desktop Left
                if (record->event.pressed) {
                      return   MACRO( I(0), D(LGUI), D(LCTL), T(LEFT), U(LGUI), U(LCTL), END ) ;
                      }else{
                     }
            break;
        }
            case 3:   {               //New Explorer
                if (record->event.pressed) {
                      return  MACRO( I(0), D(LGUI), D(E), U(LGUI), U(E), END ) ;
                      }else{
                    }
            break;
        }
            case 4:  {                //Snip Tool
                if (record->event.pressed) {
                      return  MACRO( I(0), D(LGUI), D(LSFT), T(S), U(LGUI), U(LSFT), END ) ;
                      }else{
                     }
            break;
        }
            case 5:    {              //V-Desktop Up
               if (record->event.pressed) {
                      return  MACRO( I(0), D(LGUI), T(TAB), U(LGUI), END ) ;
                      }else{
                     }
            break;
        }
            case 6:   {               //Min All
                if (record->event.pressed) {
                      return MACRO( I(0), D(LGUI), T(D), U(LGUI), END ) ;
                      }else{
                    }
            break;
        }
            case 7:  {                // Paste All
                if (record->event.pressed) {
                      return MACRO( I(0), T(F2), D(LCTL), T(V), U(LCTL), END ) ;
                      }else{
                    }
            break;
        }
            case 8:  {                //Copy All
                if (record->event.pressed) {
                      return  MACRO( I(0), T(F2), D(LCTL), T(A), T(C), U(LCTL), END ) ;
                      }else{
                   }
            break;
        }
            case 9:  {                //Task Manager
                if (record->event.pressed) {
                      return  MACRO( I(0), D(LSFT), D(LCTL), T(ESC), U(LSFT), U(LCTL), END ) ;
                      }else{
                    }
            break;
        }
            case 10:   {               //Double Zero
                if (record->event.pressed) {
                      return  MACRO( I(0), T(P0), T(P0), END ) ;
                      }else{
                    }
            break;
        }
                      
            case 11:   {               //Blank
               if (record->event.pressed) {
                      return  MACRO( D(T), U(T), END ) ;
                      }else{
                    }
            break;
        }
                case 12:   {               //Blank
                   if (record->event.pressed) {
                          return  MACRO( D(T), U(T), END ) ;
                          }else{
                        }
                break;
            }            case 13:   {               //Blank
                if (record->event.pressed) {
                       return  MACRO( D(T), U(T), END ) ;
                       }else{
                     }
             break;
         }            case 14:   {               //Blank
             if (record->event.pressed) {
                    return  MACRO( D(T), U(T), END ) ;
                    }else{
                  }
          break;
      }
            }
        return MACRO_NONE;
    };

    enum combos {
        LSFT_F1,
        LSFT_F2,
        LSFT_F3,
        LSFT_F4,
        LSFT_F5,
        LSFT_F6,
        LSFT_F7,
        LSFT_F8,
        LSFT_F9,
        LSFT_F10,
        LSFT_F11,
        LSFT_F12,
    };

    const uint16_t PROGMEM LSFTF1_combo[] = {KC_LSFT, DM_PLY1, COMBO_END};
    const uint16_t PROGMEM LSFTF2_combo[] = {KC_LSFT, DM_PLY2, COMBO_END};
    const uint16_t PROGMEM LSFTF3_combo[] = {KC_LSFT, AC_FN11, COMBO_END};
    const uint16_t PROGMEM LSFTF4_combo[] = {KC_LSFT, AC_FN12, COMBO_END};
    const uint16_t PROGMEM LSFTF5_combo[] = {KC_LSFT, AC_FN8, COMBO_END};
    const uint16_t PROGMEM LSFTF6_combo[] = {KC_LSFT, AC_FN7, COMBO_END};
    const uint16_t PROGMEM LSFTF7_combo[] = {KC_LSFT, AC_FN4, COMBO_END};
    const uint16_t PROGMEM LSFTF8_combo[] = {KC_LSFT, AC_FN3, COMBO_END};
    const uint16_t PROGMEM LSFTF9_combo[] = {KC_LSFT, AC_FN2, COMBO_END};
    const uint16_t PROGMEM LSFTF10_combo[] = {KC_LSFT, AC_FN1, COMBO_END};
    const uint16_t PROGMEM LSFTF11_combo[] = {KC_LSFT, KC_ESC, COMBO_END};
    const uint16_t PROGMEM LSFTF12_combo[] = {KC_LSFT, AC_FN9, COMBO_END};

    combo_t key_combos[COMBO_COUNT] = {
        [LSFT_F1] = COMBO(LSFTF1_combo, KC_F1),
        [LSFT_F2] = COMBO(LSFTF1_combo, KC_F2),
        [LSFT_F3] = COMBO(LSFTF1_combo, KC_F3),
        [LSFT_F4] = COMBO(LSFTF1_combo, KC_F4),
        [LSFT_F5] = COMBO(LSFTF1_combo, KC_F5),
        [LSFT_F6] = COMBO(LSFTF1_combo, KC_F6),
        [LSFT_F7] = COMBO(LSFTF1_combo, KC_F7),
        [LSFT_F8] = COMBO(LSFTF1_combo, KC_F8),
        [LSFT_F9] = COMBO(LSFTF1_combo, KC_F9),
        [LSFT_F10] = COMBO(LSFTF1_combo, KC_F10),
        [LSFT_F11] = COMBO(LSFTF1_combo, KC_F11),
        [LSFT_F12] = COMBO(LSFTF1_combo, KC_F12),

    };
    
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    LAYOUT(
                   KC_NO,KC_NO,KC_NO,KC_MPLY,KC_F14,KC_F13,KC_F15,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,                                                                                               \
                   DM_PLY1,DM_PLY2, AC_FN11, AC_FN12, AC_FN8, AC_FN7, AC_FN4, AC_FN3, AC_FN2,AC_FN1,KC_ESC,AC_FN9,        KC_DEL,KC_INS,KC_HOME,         KC_VOLD,KC_VOLU,KC_MUTE,              \
                   KC_GRV,                                                                                                                                                                     \
                   KC_LGUI,KC_1,KC_2,KC_3,KC_4,KC_5,KC_6,KC_7,KC_8,KC_9,KC_0,KC_MINS,KC_EQL,KC_JYEN,KC_BSPC,              KC_END,KC_VOLD,KC_VOLD,        KC_NLCK,KC_PSLS,KC_PAST,KC_PMNS,      \
                   KC_TAB,KC_Q,KC_W,KC_E,KC_R,KC_T,KC_Y,KC_U,KC_I,KC_O,KC_P,KC_LBRC,KC_RBRC,MO(2),                        MO(1),KC_PGUP,KC_PGDN,         KC_P7,KC_P8,KC_P9,KC_PPLS,            \
                   KC_LALT,KC_A,KC_S,KC_D,KC_F,KC_G,KC_H,KC_J,KC_K,KC_L,KC_SCLN,KC_QUOT,KC_NUHS,KC_ENT,                                                  KC_P4,KC_P5,KC_P6,KC_PCMM,            \
                   KC_LSFT,KC_NUBS,KC_Z,KC_X,KC_C,KC_V,KC_B,KC_N,KC_M,KC_COMM,KC_DOT,KC_SLSH,KC_RO,KC_RSFT,                       KC_UP,                 KC_P1,KC_P2,KC_P3,KC_PENT,            \
                   KC_CAPS,KC_BSLS,KC_LALT,KC_MHEM,KC_SPC,KC_HENK,KC_KANA,KC_MNXT,KC_RGUI,KC_NO,KC_MPRV,                  KC_LEFT,KC_DOWN,KC_RGHT,       KC_NO,KC_P0,KC_PDOT,KC_PEQL           \
    ),
    LAYOUT(
                   KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,                                                                                                    \
                   DM_REC1,DM_REC2,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,RESET,KC_NO,                               KC_NO,KC_NO,KC_NO,         KC_NO,KC_NO,KC_NO,                    \
                   KC_NO,                                                                                                                                                                      \
                   KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,             KC_NO,KC_NO,KC_NO,             KC_NO,KC_NO,KC_NO,KC_NO,              \
                   KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,                   KC_NO,KC_NO,KC_NO,             KC_NO,KC_VOLU,KC_NO,KC_NO,            \
                   KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,                                                  KC_MPRV,KC_MPLY,KC_MNXT,KC_NO,        \
                   KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,                          AC_FN5,                 KC_NO,KC_VOLD,KC_NO,KC_NO,            \
                   KC_NO,KC_NO,KC_NO,KC_NO,DEBUG,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,                                     AC_FN2,AC_FN6,AC_FN1,          KC_NO,KC_NO,KC_NO,KC_NO               \
    ),
    LAYOUT(
                   KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,                                                                                                    \
                   KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,                                   KC_NO,KC_NO,KC_NO,         KC_NO,KC_NO,KC_NO,                    \
                   KC_NO,                                                                                                                                                                      \
                   KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,             KC_NO,KC_NO,KC_NO,             KC_NO,KC_NO,KC_NO,KC_NO,              \
                   KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,                   KC_NO,KC_NO,KC_NO,             KC_NO,KC_NO,KC_NO,KC_NO,              \
                   KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,                                                  KC_NO,KC_NO,KC_NO,KC_NO,              \
                   KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,                           KC_NO,                 KC_NO,KC_NO,KC_NO,KC_NO,              \
                   KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,                                     KC_NO,KC_NO,KC_NO,             KC_NO,KC_NO,KC_NO,KC_NO               \
    ),
};

