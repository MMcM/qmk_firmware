
#include QMK_KEYBOARD_H

#include <keymap_russian.h>

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/*
 * +---+---+---+---+---+   +---+---+---+---+---+   +---+---+---+---+   +---+   +---+   +---+---+---+---+
 * |Ф1 |Ф2 |Ф3 |Ф4 |Ф5 |   |Ф6 |Ф7 |Ф8 |Ф9 |Ф10|   |Ф11|Ф12|Ф13|Ф14|   |Ф15|   |Ф16|   |Ф17|Ф18|Ф19|Ф20|
 * +---+---+---+---+---+   +---+---+---+---+---+   +---+---+---+---+   +---+   +---+   +---+---+---+---+
 * +---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+   +---+---+---+   +---+---+---+---+
 * |{ ||; +|1 !|2 "|3 #|4 ¤|5 %|6 &|7 '|8 (|9 )| 0 |- =|} ↖|   |ЗБ |   |НТ |ВСТ|УДЛ|   |ПФ1|ПФ2|ПФ3|ПФ4|
 *   +-----------------------------------------------------------+-+   +-----------+   +---------------+
 *   |ТАБ|Й J|Ц C|У U|К K|Е E|Н N|Г G|Ш [|Щ ]|З Z|Х H|: *| ~ |ВК |     |ВБР|ПРД|СЛД|   | 7 | 8 | 9 | , |
 * +-+---------------------------------------------------------+-+     +---+---+---+   +---------------+
 * |СУ |ФКС|Ф F|Ы Y|В W|А A|П P|Р R|О O|Л L|Д D|Ж V|Э \|. >| Ъ |           | ↑ |       | 4 | 5 | 6 | - |
 * +-+---------------------------------------------------------+-+     +---+---+---+   +---------------+
 *   |ВР |ЛАТ|Я Q|Ч ¬|С S|М M|И I|Т T|Ь X|Б B|Ю @|, <|/ ?| _ |ВР |     | ← | ↓ | → |   | 1 | 2 | 3 | . |
 *   +-------+---------------------------------------+---+---+---+     +---+---+---+   +---------------+
 *           |КМП|                                   |                                 |   0   | ВВОД  |
 *           +---+-----------------------------------+                                 +-------+-------+
 */
     
  [0] = LAYOUT_ms_7004(
    KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, KC_F13, KC_F14, KC_F15, KC_F16, KC_F17, KC_F18, KC_F19, KC_F20, \
    KC_BSLASH, KC_SCOLON, RU_1, RU_2, RU_3, RU_4, RU_5, RU_6, RU_7, RU_8, RU_9, RU_0, RU_MINS, KC_PLUS, KC_ESC, KC_BSPACE, KC_FIND, KC_INSERT, KC_DELETE, KC_F21, KC_F22, KC_F23, KC_F24, \
    KC_TAB, RU_SHTI, RU_TSE, RU_U, RU_KA, RU_IE, RU_EN, RU_GHE, RU_SHA, RU_SHCH, RU_ZE, RU_HA, KC_COLON, KC_GRAVE, KC_ENTER, KC_SELECT, KC_PGUP, KC_PGDOWN, KC_KP_7, KC_KP_8, KC_KP_9, KC_KP_COMMA, \
    KC_LCTRL, KC_CAPSLOCK, RU_EF, RU_YERU, RU_VE, RU_A, RU_PE, RU_ER, RU_O, RU_EL, RU_DE, RU_ZHE, RU_E, KC_DOT, RU_HARD, KC_UP, KC_KP_4, KC_KP_5, KC_KP_6, KC_KP_MINUS, \
    KC_LSHIFT, KC_INT1, RU_YA, RU_CHE, RU_ES, RU_EM, RU_I, RU_TE, RU_SOFT, RU_BE, RU_YU, KC_COMMA, KC_SLASH, KC_MENU, KC_LEFT, KC_DOWN, KC_RIGHT, KC_KP_1, KC_KP_2, KC_KP_3, KC_KP_DOT, \
    KC_LALT, KC_SPACE, KC_KP_0, KC_KP_ENTER                              \
  )
} ;
