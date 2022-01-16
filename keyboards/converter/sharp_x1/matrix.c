
#include "debug.h"
#include "matrix.h"
#include "print.h"
#include "quantum.h"

/*
 * ASCII codes (not matrix indices, for which see sharp_x1.h).
 *
 * Base:
 * +-----+-----+-----+-----+-----++---+---++---+---+               +---+---+---+---+
 * |*71  |*72  |*73  |*74  |*75  ||*EC|*EB||*E2|*E1|               |*0B|*2F|*2A|*2D|
 * +-----+-----+-----+-----+-----++---+---++---+---+               +---+---+---+---+
 * +---+---+---+---+---+---+---+---+---+---+---+---+---+---+-----+ +---+---+---+---+
 * |1B |31 |32 |33 |34 |35 |36 |37 |38 |39 |30 |2D |5E |5C |13   | |*37|*38|*39|*2B|
 * +-------------------------------------------------------------+ +---------------+
 * |09   |71 |77 |65 |72 |74 |79 |75 |69 |6F |70 |40 |5B |08 |   | |*34|*35|*36|*3D|
 * +---------------------------------------------------------|   | +---------------+
 * |      |61 |73 |64 |66 |67 |68 |6A |6B |6C |3B |3A |5D |0D    | |*31|*32|*33|*2E|
 * +-------------------------------------------------------------+ +---------------+
 * |        |7A |78 |63 |76 |62 |6E |6D |2C |2E |2F |5F |        | |*30|*2C|*1E|*0D|
 * +------+-----------------------------------------------+------+ +-----------|   |
 *        |   |   |20                             |   |*E8|        |*1D|*1C|*1F|   |
 *        +---+---+-------------------------------+---+---+        +---+---+---+---+
 *
 * Shift:
 * +-----+-----+-----+-----+-----++---+---++---+---+               +---+---+---+---+
 * |*76  |*77  |*78  |*79  |*7A  ||*EC|*EB||*E2|*E1|               |*0C|*2F|*2A|*2D|
 * +-----+-----+-----+-----+-----++---+---++---+---+               +---+---+---+---+
 * +---+---+---+---+---+---+---+---+---+---+---+---+---+---+-----+ +---+---+---+---+
 * |1B |21 |22 |23 |24 |25 |26 |27 |28 |29 |30 |3D |7E |7C |03   | |*37|*38|*39|*2B|
 * +-------------------------------------------------------------+ +---------------+
 * |09   |51 |57 |45 |52 |54 |59 |55 |49 |4F |50 |60 |7B |12 |   | |*34|*35|*36|*3D|
 * +---------------------------------------------------------|   | +---------------+
 * |      |41 |53 |44 |46 |47 |48 |4A |4B |4C |2B |2A |7D |0D    | |*31|*32|*33|*2E|
 * +-------------------------------------------------------------+ +---------------+
 * |        |5A |58 |43 |56 |42 |4E |4D |3C |3E |3F |5F |        | |*30|*2C|*1E|*0D|
 * +------+-----------------------------------------------+------+ +-----------|   |
 *        |   |   |20                             |   |*E8|        |*1D|*1C|*1F|   |
 *        +---+---+-------------------------------+---+---+        +---+---+---+---+
 *
 * Kana Mode A (JIS X 0201):
 * +-----+-----+-----+-----+-----++---+---++---+---+               +---+---+---+---+
 * |*71  |*72  |*73  |*74  |*75  ||*EC|*EB||*E2|*E1|               |*0B|*2F|*2A|*2D|
 * +-----+-----+-----+-----+-----++---+---++---+---+               +---+---+---+---+
 * +---+---+---+---+---+---+---+---+---+---+---+---+---+---+-----+ +---+---+---+---+
 * |1B |C7 |CC |B1 |B3 |B4 |B5 |D4 |D5 |D6 |DC |CE |CD |B0 |13   | |*37|*38|*39|*2B|
 * +-------------------------------------------------------------+ +---------------+
 * |09   |C0 |C3 |B2 |BD |B6 |DD |C5 |C6 |D7 |BE |DE |DF |08 |   | |*34|*35|*36|*3D|
 * +---------------------------------------------------------|   | +---------------+
 * |      |C1 |C4 |BC |CA |B7 |B8 |CF |C9 |D8 |DA |B9 |D1 |0D    | |*31|*32|*33|*2E|
 * +-------------------------------------------------------------+ +---------------+
 * |        |C2 |B8 |BF |CB |BA |D0 |D3 |C8 |D9 |D2 |DB |        | |*30|*2C|*1E|*0D|
 * +------+-----------------------------------------------+------+ +-----------|   |
 *        |   |   |20                             |   |*E8|        |*1D|*1C|*1F|   |
 *        +---+---+-------------------------------+---+---+        +---+---+---+---+
 *
 * Shift Kana:
 * +-----+-----+-----+-----+-----++---+---++---+---+               +---+---+---+---+
 * |*76  |*77  |*78  |*79  |*7A  ||*EC|*EB||*E2|*E1|               |*0C|*2F|*2A|*2D|
 * +-----+-----+-----+-----+-----++---+---++---+---+               +---+---+---+---+
 * +---+---+---+---+---+---+---+---+---+---+---+---+---+---+-----+ +---+---+---+---+
 * |1B |C7 |CC |A7 |A9 |AA |AB |AC |AD |AE |A6 |CE |CD |B0 |03   | |*37|*38|*39|*2B|
 * +-------------------------------------------------------------+ +---------------+
 * |09   |C0 |C3 |A8 |BD |B6 |DD |C5 |C6 |D7 |BE |DE |A2 |12 |   | |*34|*35|*36|*3D|
 * +---------------------------------------------------------|   | +---------------+
 * |      |C1 |C4 |BC |CA |B7 |B8 |CF |C9 |D8 |DA |B9 |A3 |0D    | |*31|*32|*33|*2E|
 * +-------------------------------------------------------------+ +---------------+
 * |        |AF |B8 |BF |CB |BA |D0 |D3 |A4 |A1 |A5 |A0 |        | |*30|*2C|*1E|*0D|
 * +------+-----------------------------------------------+------+ +-----------|   |
 *        |   |   |20                             |   |*E8|        |*1D|*1C|*1F|   |
 *        +---+---+-------------------------------+---+---+        +---+---+---+---+
 *
 * Kana Mode B:
 * +-----+-----+-----+-----+-----++---+---++---+---+               +---+---+---+---+
 * |*71  |*72  |*73  |*74  |*75  ||*EC|*EB||*E2|*E1|               |*0B|*2F|*2A|*2D|
 * +-----+-----+-----+-----+-----++---+---++---+---+               +---+---+---+---+
 * +---+---+---+---+---+---+---+---+---+---+---+---+---+---+-----+ +---+---+---+---+
 * |1B |B1 |B2 |B3 |B4 |B5 |C5 |C6 |C7 |C8 |C9 |D7 |D8 |D9 |13   | |*37|*38|*39|*2B|
 * +-------------------------------------------------------------+ +---------------+
 * |09   |B6 |B7 |B8 |B9 |BA |CA |CB |CC |CD |CE |DA |DB |08 |   | |*34|*35|*36|*3D|
 * +---------------------------------------------------------|   | +---------------+
 * |      |B8 |BC |BD |BE |BF |CF |D0 |D1 |D2 |D3 |DE |DF |0D    | |*31|*32|*33|*2E|
 * +-------------------------------------------------------------+ +---------------+
 * |        |C0 |C1 |C2 |C3 |C4 |D4 |D5 |D6 |DC |A6 |DD |        | |*30|*2C|*1E|*0D|
 * +------+-----------------------------------------------+------+ +-----------|   |
 *        |   |   |20                             |   |*E8|        |*1D|*1C|*1F|   |
 *        +---+---+-------------------------------+---+---+        +---+---+---+---+
 *
 * Shift Kana:
 * +-----+-----+-----+-----+-----++---+---++---+---+               +---+---+---+---+
 * |*76  |*77  |*78  |*79  |*7A  ||*EC|*EB||*E2|*E1|               |*0C|*2F|*2A|*2D|
 * +-----+-----+-----+-----+-----++---+---++---+---+               +---+---+---+---+
 * +---+---+---+---+---+---+---+---+---+---+---+---+---+---+-----+ +---+---+---+---+
 * |1B |A7 |A8 |A9 |AA |AB |C5 |C6 |C7 |C8 |C9 |D7 |D8 |A0 |03   | |*37|*38|*39|*2B|
 * +-------------------------------------------------------------+ +---------------+
 * |09   |B6 |B7 |B8 |B9 |BA |CA |CB |CC |CD |CE |DA |A2 |12 |   | |*34|*35|*36|*3D|
 * +---------------------------------------------------------|   | +---------------+
 * |      |B8 |BC |BD |BE |BF |CF |D0 |D1 |D2 |D3 |B0 |A3 |0D    | |*31|*32|*33|*2E|
 * +-------------------------------------------------------------+ +---------------+
 * |        |C0 |C1 |AF |C3 |C4 |AC |AD |AE |A4 |A1 |A5 |        | |*30|*2C|*1E|*0D|
 * +------+-----------------------------------------------+------+ +-----------|   |
 *        |   |   |20                             |   |*E8|        |*1D|*1C|*1F|   |
 *        +---+---+-------------------------------+---+---+        +---+---+---+---+
 *
 * Graph:
 * +-----+-----+-----+-----+-----++---+---++---+---+               +---+---+---+---+
 * |*71  |*72  |*73  |*74  |*75  ||*EC|*EB||*E2|*E1|               |*0B|*9E|*9B|*9C|
 * +-----+-----+-----+-----+-----++---+---++---+---+               +---+---+---+---+
 * +---+---+---+---+---+---+---+---+---+---+---+---+---+---+-----+ +---+---+---+---+
 * |1B |F1 |F2 |F3 |F4 |F5 |F6 |F7 |F8 |F9 |FA |8C |8B |FB |13   | |*9A|*93|*97|*9D|
 * +-------------------------------------------------------------+ +---------------+
 * |09   |E0 |E1 |E2 |E3 |E4 |E5 |E6 |E7 |F0 |8D |8A |FC |08 |   | |*95|*96|*94|*90|
 * +---------------------------------------------------------|   | +---------------+
 * |      |7F |E9 |EA |EB |EC |ED |EE |EF |8E |89 |FD |E8 |0D    | |*99|*92|*98|*91|
 * +-------------------------------------------------------------+ +---------------+
 * |        |80 |81 |82 |83 |84 |85 |86 |87 |88 |FE |FF |        | |*8F|*9F|*1E|*0D|
 * +------+-----------------------------------------------+------+ +-----------|   |
 *        |   |   |20                             |   |*E8|        |*1D|*1C|*1F|   |
 *        +---+---+-------------------------------+---+---+        +---+---+---+---+
 *
 */

static const uint8_t PROGMEM ten_keys[256] = {
    [0x0B] = 0x51, // HOME
    [0x0C] = 0x51, // CLR (shift HOME)
    [0x0D] = 0xB6, // numpad ⏎
    [0x1C] = 0xB4, // ⇨
    [0x1D] = 0xB3, // ⇦
    [0x1E] = 0xB1, // ⇧
    [0x1F] = 0xB5, // ⇩
    [0x2A] = 0x34, // numpad *
    [0x2B] = 0x33, // numpad +
    [0x2C] = 0xB0, // numpad ,
    [0x2D] = 0x32, // numpad -
    [0x2E] = 0x96, // numpad .
    [0x2F] = 0x52, // numpad /
    [0x30] = 0xA7, // numpad 0
    [0x31] = 0x22, // numpad 1
    [0x32] = 0x24, // numpad 2
    [0x33] = 0x27, // numpad 3
    [0x34] = 0x21, // numpad 4
    [0x35] = 0x82, // numpad 5
    [0x36] = 0x26, // numpad 6
    [0x37] = 0x20, // numpad 7
    [0x38] = 0x23, // numpad 8
    [0x39] = 0x25, // numpad 9
    [0x3D] = 0x83, // numpad =
    [0x71] = 0x40, // F1
    [0x72] = 0x41, // F2
    [0x73] = 0x42, // F3
    [0x74] = 0x43, // F4
    [0x75] = 0x44, // F5
    [0x76] = 0x40, // shift F1
    [0x77] = 0x41, // shift F2
    [0x78] = 0x42, // shift F3
    [0x79] = 0x43, // shift F4
    [0x7A] = 0x44, // shift F5
    [0x8F] = 0xA7, // graph numpad 0
    [0x90] = 0x83, // graph numpad =
    [0x91] = 0x96, // graph numpad .
    [0x92] = 0x24, // graph numpad 2
    [0x93] = 0x23, // graph numpad 8
    [0x94] = 0x26, // graph numpad 6
    [0x95] = 0x21, // graph numpad 4
    [0x96] = 0x82, // graph numpad 5
    [0x97] = 0x25, // graph numpad 9
    [0x98] = 0x27, // graph numpad 3
    [0x99] = 0x22, // graph numpad 1
    [0x9A] = 0x20, // graph numpad 7
    [0x9B] = 0x34, // graph numpad *
    [0x9C] = 0x32, // graph numpad -
    [0x9D] = 0x33, // graph numpad +
    [0x9E] = 0x52, // graph numpad /
    [0x9F] = 0xB0, // graph numpad ,
    [0xE1] = 0x50, // COPY
    [0xE2] = 0x47, // HELP
    [0xE8] = 0xB2, // XFER
    [0xEB] = 0x46, // ROLL DOWN
    [0xEC] = 0x45, // ROLL UP
};

static const uint8_t PROGMEM graph_keys[256] = {
    [0x03] = 0x67, // graph shift BREAK
    [0x08] = 0x81, // graph DEL
    [0x09] = 0x35, // graph H TAB
    [0x0D] = 0xB7, // graph ⏎
    [0x12] = 0x81, // graph INS (shift DEL)
    [0x13] = 0x67, // graph BREAK
    [0x1B] = 0x30, // graph ESC
    [0x20] = 0x36, // graph SPACE
    [0x7F] = 0x13, // graph A
    [0x80] = 0x15, // graph Z
    [0x81] = 0x16, // graph X
    [0x82] = 0x17, // graph C
    [0x83] = 0x97, // graph V
    [0x84] = 0xA0, // graph B
    [0x85] = 0xA1, // graph N
    [0x86] = 0xA2, // graph M
    [0x87] = 0xA3, // graph ,
    [0x88] = 0xA4, // graph .
    [0x89] = 0x93, // graph ;
    [0x8A] = 0x77, // graph @
    [0x8B] = 0x65, // graph ^
    [0x8C] = 0x64, // graph -
    [0x8D] = 0x76, // graph P
    [0x8E] = 0x92, // graph L
    [0xE0] = 0x10, // graph Q
    [0xE1] = 0x11, // graph W
    [0xE2] = 0x12, // graph E
    [0xE3] = 0x70, // graph R
    [0xE4] = 0x71, // graph T
    [0xE5] = 0x72, // graph Y
    [0xE6] = 0x73, // graph U
    [0xE7] = 0x74, // graph I
    [0xE8] = 0x95, // graph ]
    [0xE9] = 0x84, // graph S
    [0xEA] = 0x14, // graph D
    [0xEB] = 0x85, // graph F
    [0xEC] = 0x86, // graph G
    [0xED] = 0x87, // graph H
    [0xEE] = 0x90, // graph J
    [0xEF] = 0x91, // graph K
    [0xF0] = 0x75, // graph O
    [0xF1] = 0x31, // graph 1
    [0xF2] = 0x53, // graph 2
    [0xF3] = 0x54, // graph 3
    [0xF4] = 0x55, // graph 4
    [0xF5] = 0x56, // graph 5
    [0xF6] = 0x57, // graph 6
    [0xF7] = 0x60, // graph 7
    [0xF8] = 0x61, // graph 8
    [0xF9] = 0x62, // graph 9
    [0xFA] = 0x63, // graph 0
    [0xFB] = 0x66, // graph ¥
    [0xFC] = 0x80, // graph [
    [0xFD] = 0x94, // graph :
    [0xFE] = 0xA5, // graph /
    [0xFF] = 0xA6, // graph ロ
};

static const uint8_t PROGMEM ascii_keys[128] = {
    [0x03] = 0x67, // shift BREAK
    [0x08] = 0x81, // DEL
    [0x09] = 0x35, // H TAB
    [0x0D] = 0xB7, // ⏎
    [0x12] = 0x81, // INS (shift DEL)
    [0x13] = 0x67, // BREAK
    [0x1B] = 0x30, // ESC
    [' ']  = 0x36,
    ['!']  = 0x31, // shift 1
    ['"']  = 0x53, // shift 2
    ['#']  = 0x54, // shift 3
    ['$']  = 0x55, // shift 4
    ['%']  = 0x56, // shift 5
    ['&']  = 0x57, // shift 6
    ['\''] = 0x60, // shift 7
    ['(']  = 0x61, // shift 8
    [')']  = 0x62, // shift 9
    ['*']  = 0x94, // shift :
    ['+']  = 0x93, // shift ;
    [',']  = 0xA3,
    ['-']  = 0x64,
    ['.']  = 0xA4,
    ['/']  = 0xA5,
    ['0']  = 0x63,
    ['1']  = 0x31,
    ['2']  = 0x53,
    ['3']  = 0x54,
    ['4']  = 0x55,
    ['5']  = 0x56,
    ['6']  = 0x57,
    ['7']  = 0x60,
    ['8']  = 0x61,
    ['9']  = 0x62,
    [':']  = 0x94,
    [';']  = 0x93,
    ['<']  = 0xA3, // shift ,
    ['=']  = 0x64, // shift -
    ['>']  = 0xA4, // shift .
    ['?']  = 0xA5, // shift /
    ['@']  = 0x77,
    ['A']  = 0x13,
    ['B']  = 0xA0,
    ['C']  = 0x17,
    ['D']  = 0x14,
    ['E']  = 0x12,
    ['F']  = 0x85,
    ['G']  = 0x86,
    ['H']  = 0x87,
    ['I']  = 0x74,
    ['J']  = 0x90,
    ['K']  = 0x91,
    ['L']  = 0x92,
    ['M']  = 0xA2,
    ['N']  = 0xA1,
    ['O']  = 0x75,
    ['P']  = 0x76,
    ['Q']  = 0x10,
    ['R']  = 0x70,
    ['S']  = 0x84,
    ['T']  = 0x71,
    ['U']  = 0x73,
    ['V']  = 0x97,
    ['W']  = 0x11,
    ['X']  = 0x16,
    ['Y']  = 0x72,
    ['Z']  = 0x15,
    ['[']  = 0x80,
    [0x5C] = 0x66, // ¥
    [']']  = 0x95,
    ['^']  = 0x65,
    ['_']  = 0xA6, // ロ
    ['`']  = 0x77, // shift @
    ['a']  = 0x13,
    ['b']  = 0xA0,
    ['c']  = 0x17,
    ['d']  = 0x14,
    ['e']  = 0x12,
    ['f']  = 0x85,
    ['g']  = 0x86,
    ['h']  = 0x87,
    ['i']  = 0x74,
    ['j']  = 0x90,
    ['k']  = 0x91,
    ['l']  = 0x92,
    ['m']  = 0xA2,
    ['n']  = 0xA1,
    ['o']  = 0x75,
    ['p']  = 0x76,
    ['q']  = 0x10,
    ['r']  = 0x70,
    ['s']  = 0x84,
    ['t']  = 0x71,
    ['u']  = 0x73,
    ['v']  = 0x97,
    ['w']  = 0x11,
    ['x']  = 0x16,
    ['y']  = 0x72,
    ['z']  = 0x15,
    ['{']  = 0x80, // shift [
    ['|']  = 0x66, // shift ¥
    ['}']  = 0x95, // shift ]
    [0x7E] = 0x65, // ‾ shift ^
};

static const uint8_t PROGMEM mode_a_kana_keys[128] = {
    [0xA0 - 0x80] = 0xA6, // shift ロ
    [0xA1 - 0x80] = 0xA4, // 。 shift .
    [0xA2 - 0x80] = 0x80, // 「 shift [
    [0xA3 - 0x80] = 0x95, // 」 shift ]
    [0xA4 - 0x80] = 0xA3, // 、 shift ,
    [0xA5 - 0x80] = 0xA5, // ・ shift /
    [0xA6 - 0x80] = 0x63, // ヲ shift 0
    [0xA7 - 0x80] = 0x54, // ァ shift 3
    [0xA8 - 0x80] = 0x12, // ィ shift E
    [0xA9 - 0x80] = 0x55, // ゥ shift 4
    [0xAA - 0x80] = 0x56, // ェ shift 5
    [0xAB - 0x80] = 0x57, // ォ shift 6
    [0xAC - 0x80] = 0x60, // ャ shift 7
    [0xAD - 0x80] = 0x61, // ュ shift 8
    [0xAE - 0x80] = 0x62, // ョ shift 9
    [0xAF - 0x80] = 0x15, // ッ shift Z
    [0xB0 - 0x80] = 0x66, // ー ¥
    [0xB1 - 0x80] = 0x54, // ア 3
    [0xB2 - 0x80] = 0x12, // イ E
    [0xB3 - 0x80] = 0x55, // ウ 4
    [0xB4 - 0x80] = 0x56, // エ 5
    [0xB5 - 0x80] = 0x57, // オ 6
    [0xB6 - 0x80] = 0x71, // カ T
    [0xB7 - 0x80] = 0x86, // キ G
    [0xB8 - 0x80] = 0x16, // ク X
    [0xB9 - 0x80] = 0x94, // ケ :
    [0xBA - 0x80] = 0xA0, // コ B
    [0xBC - 0x80] = 0x14, // シ D
    [0xBD - 0x80] = 0x70, // ス R
    [0xBE - 0x80] = 0x76, // セ P
    [0xBF - 0x80] = 0x17, // ソ C
    [0xC0 - 0x80] = 0x10, // タ Q
    [0xC1 - 0x80] = 0x13, // チ A
    [0xC2 - 0x80] = 0x15, // ツ Z
    [0xC3 - 0x80] = 0x11, // テ W
    [0xC4 - 0x80] = 0x84, // ト S
    [0xC5 - 0x80] = 0x73, // ナ U
    [0xC6 - 0x80] = 0x74, // ニ I
    [0xC7 - 0x80] = 0x31, // ヌ 1
    [0xC8 - 0x80] = 0xA3, // ネ ,
    [0xC9 - 0x80] = 0x91, // ノ K
    [0xCA - 0x80] = 0x85, // ハ F
    [0xCB - 0x80] = 0x97, // ヒ V
    [0xCC - 0x80] = 0x53, // フ 2
    [0xCD - 0x80] = 0x65, // ヘ ^
    [0xCE - 0x80] = 0x64, // ホ -
    [0xCF - 0x80] = 0x90, // マ J
    [0xD0 - 0x80] = 0xA1, // ミ N
    [0xD1 - 0x80] = 0x95, // ム ]
    [0xD2 - 0x80] = 0xA5, // メ /
    [0xD3 - 0x80] = 0xA2, // モ M
    [0xD4 - 0x80] = 0x60, // ヤ 7
    [0xD5 - 0x80] = 0x61, // ユ 8
    [0xD6 - 0x80] = 0x62, // ヨ 9
    [0xD7 - 0x80] = 0x75, // ラ O
    [0xD8 - 0x80] = 0x92, // リ L
    [0xD9 - 0x80] = 0xA4, // ル .
    [0xDA - 0x80] = 0x93, // レ ;
    [0xDB - 0x80] = 0xA6, // ロ
    [0xDC - 0x80] = 0x63, // ワ 0
    [0xDD - 0x80] = 0x72, // ン Y
    [0xDE - 0x80] = 0x77, // ゛ @
    [0xDF - 0x80] = 0x80, // ゜ [
};

static const uint8_t PROGMEM mode_b_kana_keys[128] = {
    [0xA0 - 0x80] = 0x66, // shift ¥
    [0xA1 - 0x80] = 0xA5, // shift /
    [0xA2 - 0x80] = 0x80, // shift [
    [0xA3 - 0x80] = 0x95, // shift ]
    [0xA4 - 0x80] = 0xA4, // shift .
    [0xA5 - 0x80] = 0xA6, // shift ロ
    [0xA6 - 0x80] = 0xA5, // /
    [0xA7 - 0x80] = 0x31, // shift 1
    [0xA8 - 0x80] = 0x53, // shift 2
    [0xA9 - 0x80] = 0x54, // shift 3
    [0xAA - 0x80] = 0x55, // shift 4
    [0xAB - 0x80] = 0x56, // shift 5
    [0xAC - 0x80] = 0xA1, // shift N
    [0xAD - 0x80] = 0xA2, // shift M
    [0xAE - 0x80] = 0xA3, // shift ,
    [0xAF - 0x80] = 0x17, // shift C
    [0xB0 - 0x80] = 0x94, // shift :
    [0xB1 - 0x80] = 0x31, // 1
    [0xB2 - 0x80] = 0x53, // 2
    [0xB3 - 0x80] = 0x54, // 3
    [0xB4 - 0x80] = 0x55, // 4
    [0xB5 - 0x80] = 0x56, // 5
    [0xB6 - 0x80] = 0x10, // Q
    [0xB7 - 0x80] = 0x11, // W
    [0xB8 - 0x80] = 0x13, // A
    [0xB9 - 0x80] = 0x70, // R
    [0xBA - 0x80] = 0x71, // T
    [0xBC - 0x80] = 0x84, // S
    [0xBD - 0x80] = 0x14, // D
    [0xBE - 0x80] = 0x85, // F
    [0xBF - 0x80] = 0x86, // G
    [0xC0 - 0x80] = 0x15, // Z
    [0xC1 - 0x80] = 0x16, // X
    [0xC2 - 0x80] = 0x17, // C
    [0xC3 - 0x80] = 0x97, // V
    [0xC4 - 0x80] = 0xA0, // B
    [0xC5 - 0x80] = 0x57, // 6
    [0xC6 - 0x80] = 0x60, // 7
    [0xC7 - 0x80] = 0x61, // 8
    [0xC8 - 0x80] = 0x62, // 9
    [0xC9 - 0x80] = 0x63, // 0
    [0xCA - 0x80] = 0x72, // Y
    [0xCB - 0x80] = 0x73, // U
    [0xCC - 0x80] = 0x74, // I
    [0xCD - 0x80] = 0x75, // O
    [0xCE - 0x80] = 0x76, // P
    [0xCF - 0x80] = 0x87, // H
    [0xD0 - 0x80] = 0x90, // J
    [0xD1 - 0x80] = 0x91, // K
    [0xD2 - 0x80] = 0x92, // L
    [0xD3 - 0x80] = 0x93, // ;
    [0xD4 - 0x80] = 0xA1, // N
    [0xD5 - 0x80] = 0xA2, // M
    [0xD6 - 0x80] = 0xA3, // ,
    [0xD7 - 0x80] = 0x64, // -
    [0xD8 - 0x80] = 0x65, // ^
    [0xD9 - 0x80] = 0x66, // ¥
    [0xDA - 0x80] = 0x77, // @
    [0xDB - 0x80] = 0x80, // [
    [0xDC - 0x80] = 0xA4, // .
    [0xDD - 0x80] = 0xA6, // ロ
    [0xDE - 0x80] = 0x94, // :
    [0xDF - 0x80] = 0x95, // ]
};

static enum {
    IDLE, KEY_HEADER, KEY_BITS, GAME_HEADER, GAME_BITS
} state = IDLE;

typedef enum {
    KEY_EVENT, GAME_EVENT, ERROR_EVENT
} event_type_t;

typedef struct {
    uint8_t event_type;
    union {
        uint8_t bits[3];
        struct {
            unsigned ctrl:1;
            unsigned shift:1;
            unsigned kana:1;
            unsigned caps_lock:1;
            unsigned graph:1;
            unsigned repeat:1;
            unsigned key_input:1;
            unsigned ten_key:1;
            uint8_t ascii_code; // Actually JIS X 0201
        } key;
        struct {
            unsigned c:1;
            unsigned x:1;
            unsigned z:1;
            unsigned d:1;
            unsigned a:1;
            unsigned e:1;
            unsigned w:1;
            unsigned q:1;
            unsigned kp_3:1;
            unsigned kp_6:1;
            unsigned kp_9:1;
            unsigned kp_2:1;
            unsigned kp_8:1;
            unsigned kp_1:1;
            unsigned kp_4:1;
            unsigned kp_7:1;
            unsigned main_ret:1;
            unsigned sp:1;
            unsigned h_tab:1;
            unsigned kp_ast:1;
            unsigned kp_plus:1;
            unsigned kp_minus:1;
            unsigned main_1:1;
            unsigned esc:1;
        } game;
        struct {
            unsigned half:1;
            unsigned state:4;
            unsigned bit_count:5;
            uint16_t width;
        } error_info;
    };
} queue_entry_t;

// Get a key that would have generated the given ASCII code given the rest of the shifts.
static uint8_t unascii(queue_entry_t event, bool mode_b) {
    uint8_t ascii = event.key.ascii_code;

    // Ten key / numpad bit indicates:
    //  numpad versions of regular chars (digits, return),
    //  function keys reusing regular chars (F1 = q),
    //  arrow keys in control character range,
    //  special commands outside 7-bit (HELP, COPY).
    if (event.key.ten_key) {
        return pgm_read_byte(ten_keys + ascii);
    }

    // GRAPH is stronger than SHIFT or カナ for non-numpad keys
    // (except for those it does not change, including INS DEL and BREAK, which have SHIFT variants).
    if (event.key.graph) {
        return pgm_read_byte(graph_keys + ascii);
    }

    if (ascii & 0x80) {
        if (!event.key.kana) {
            return 0;           // カナ not locked
        }
        return pgm_read_byte((mode_b ? mode_b_kana_keys : mode_a_kana_keys) + (ascii & 0x7F));
    }

    // If CTRL is generating an ASCII character, prefer the standard form.
    // This distinguishes return from CTRL-M.
    if (event.key.ctrl && (ascii & 0x60) == 0) {
        ascii |= 0x40;
    }

    return pgm_read_byte(ascii_keys + ascii);
}

#define QUEUE_SIZE 16
static queue_entry_t next_code, code_queue[QUEUE_SIZE];
static uint8_t code_queue_in, code_queue_out;

static inline void queue_clear(void) {
    code_queue_in = code_queue_out = 0;
}

static inline bool queue_is_empty(void) {
    return (code_queue_in == code_queue_out);
}

static inline bool queue_is_full(void) {
    // One entry wasted to be able to check this easily.
    return (((code_queue_in + 1) % QUEUE_SIZE) == code_queue_out);
}

static inline queue_entry_t queue_remove(void) {
    queue_entry_t entry = code_queue[code_queue_out];
    code_queue_out = (code_queue_out + 1) % QUEUE_SIZE;
    return entry;
}

static inline void queue_add(queue_entry_t entry) {
    code_queue[code_queue_in] = entry;
    code_queue_in = (code_queue_in + 1) % QUEUE_SIZE;
}

static uint16_t pulse_start;
static uint8_t bit_count;

static inline void queue_event(event_type_t event_type) {
    next_code.event_type = event_type;
    if (!queue_is_full()) {
        queue_add(next_code);
    }
    state = IDLE;
}

static inline void queue_error_event(bool half, uint16_t width) {
    next_code.error_info.half = half;
    next_code.error_info.state = state;
    next_code.error_info.bit_count = bit_count;
    next_code.error_info.width = width;
    queue_event(ERROR_EVENT);
}

static inline void add_bit(uint8_t value) {
    if (value) {
        // Big-endian
        next_code.bits[bit_count >> 3] |= 1 << (7 - (bit_count & 7));
    }
    bit_count++;
}

static inline void start_pulse(uint16_t count) {
    uint16_t width16 = count - pulse_start;
    uint8_t width = width16 > 256 ? 256 : (uint8_t)width16; // Nothing 4ms or wider is real.
    if (state == IDLE) {
        next_code.bits[0] = next_code.bits[1] = next_code.bits[2] = 0;
        bit_count = 0;
        if (width >= 50 && width <= 75) { // 1000us = 62.5 ticks
            state = KEY_HEADER;
        } else if (width >= 20 && width <= 30) { // 400us = 25.0 ticks
            state = GAME_HEADER;
        } else {
            // Rejected, stay IDLE
            queue_error_event(false, width16);
        }
    } else {
        if (width >= 10 && width <= 20) { // 250us = 15.625 ticks
            if (state == KEY_BITS && bit_count == 16) {
                queue_event(KEY_EVENT);
            } else if (state == GAME_BITS && bit_count == 24) {
                queue_event(GAME_EVENT);
            }
        } else {
            // Rejected, go IDLE
            queue_error_event(false, width16);
        }
    }
}

static inline void whole_pulse(uint16_t count) {
    uint16_t width16 = count - pulse_start;
    uint8_t width = width16 > 256 ? 256 : (uint8_t)width16; // Nothing 4ms or wider is real.
    if (state == KEY_HEADER) {
        if (width >= 100 && width <= 110) { // 1700us (1000 + 700) = 106.25 ticks
            state = KEY_BITS;
        } else {
            queue_error_event(true, width16);
        }
    } else if (state == KEY_BITS) {
        uint8_t value;
        if (width >= 50 && width <= 75) { //  1000us (250 + 750) = 62.5 ticks
            value = 0;
        } else if (width >= 120 && width <= 130) { // 2000us (250 + 1750) = 125.0 ticks
            value = 1;
        } else {
            queue_error_event(true, width16);
            return;
        }
        add_bit(value);
    } else if (state == GAME_HEADER) {
        if (width >= 30 && width <= 40) { // 600us (400 + 200) = 37.5 ticks
            state = GAME_BITS;
        } else {
            queue_error_event(true, width16);
        }
    } else if (state == GAME_BITS) {
        uint8_t value;
        if (width >= 25 && width <= 35) { //  500us (250 + 250) = 31.25 ticks
            value = 0;
        } else if (width >= 60 && width <= 65) { // 1000us (250 + 750) = 62.5 ticks
            value = 1;
        } else {
            queue_error_event(true, width16);
            return;
        }
        add_bit(value);
    }
}

#define DATA_PORT PORTD
#define DATA_PIN PIND
#define DATA_DDR DDRD
#define DATA_MASK (1 << 0)

ISR(INT0_vect) {
    bool pin_state = (DATA_PIN & DATA_MASK) != 0;
    uint16_t count = TCNT3;
    if (pin_state) {
        // Rising edge
        start_pulse(count);
    } else {
        // Falling edge
        if (state != IDLE) {
            // End of previous pulse
            whole_pulse(count);
        }
        pulse_start = count;
    }
}

static matrix_row_t matrix[MATRIX_ROWS];

__attribute__ ((weak))
void matrix_init_kb(void) {
    matrix_init_user();
}

__attribute__ ((weak))
void matrix_scan_kb(void) {
    matrix_scan_user();
}

__attribute__ ((weak))
void matrix_init_user(void) {
}

__attribute__ ((weak))
void matrix_scan_user(void) {
}

void matrix_init(void) {
    for (uint8_t row = 0; row < MATRIX_ROWS; row++) matrix[row] = 0;

#if F_CPU != 16000000
#error Wrong prescalar for clock rate
#endif

    // Configure TCNT3 to count once every 16us, to distinguish pulses whose half-widths are in the hundreds of microseconds.
    TCCR3A = 0;                 // Normal
    TCCR3B = _BV(CS32);         // Prescalar = 256

    DATA_PORT |= DATA_MASK;     // Pullup on DATA line

    // Interrupt 0 on either edge.
    EIMSK |= (1 << INT0);
    EICRA |= (1 << ISC00);

    matrix_init_quantum();
}

uint8_t matrix_scan(void) {
    static bool game_seen = false;

    debug_enable = true;

    if (!queue_is_empty()) {
        queue_entry_t event = queue_remove();
        uint8_t code;
        switch (event.event_type) {
        case KEY_EVENT:
            event.bits[0] ^= 0xFF; // Invert flag senses.
            if (event.key.key_input) {
                code = unascii(event, game_seen);
            } else {
                code = 0;
            }
            dprintf("Key %02X %02X - %02X\n", event.bits[0], event.bits[1], code);
            matrix[0] = event.bits[0];
            for (uint8_t row = game_seen ? 4 : 1; row < MATRIX_ROWS; row++) {
                // Clear all regular (based on game mode) keys.
                matrix[row] = 0;
            }
            if (code != 0) {
                uint8_t row = code >> 4;
                uint8_t col = code & 7;
                // Since the bit serial protocol is big-endian for the ASCII part,
                // we read it all that way, and so interpret col index accordingly.
                matrix[row] |= 1 << (7 - col);
            }
            break;
        case GAME_EVENT:
            dprintf("Game %02X %02X %02X\n", event.bits[0], event.bits[1], event.bits[2]);
            game_seen = true;
            // The last game bit is activated by _either_ ⏎ key.
            // Therefore, _neither_ key is assigned to index 37 and the key report is used instead.
            matrix[1] = event.bits[0];
            matrix[2] = event.bits[1];
            matrix[3] = event.bits[2];
            break;
        case ERROR_EVENT:
            dprintf("Error %s@%d/%d: %d\n", event.error_info.half ? "second " : "first ",
                    event.error_info.state, event.error_info.bit_count, event.error_info.width);
            break;
        }
    }

    matrix_scan_quantum();
    return 1;
}

void matrix_print(void) {
    print("\nr/c 01234567\n");
    for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
        print_hex16(row); print(": ");
        print_bin_reverse8(matrix_get_row(row));
        print("\n");
    }
}

inline
matrix_row_t matrix_get_row(uint8_t row) {
    return matrix[row];
}
