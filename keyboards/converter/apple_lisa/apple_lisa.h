
#pragma once

#include "quantum.h"

/* ANSI layout
 *
 * +---+---+---+---+---+---+---+---+---+---+---+---+---+-----+ +---+---+---+---+
 * | ` | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 0 | - | = | BS  | |Clr| - | + | * |
 * +---------------------------------------------------------+ +---+---+---+---+
 * | Tab | Q | W | E | R | T | Y | U | I | O | P | [ | ] | \ | | 7 | 8 | 9 | / |
 * +---------------------------------------------------------+ +---+---+---+---+
 * | Caps | A | S | D | F | G | H | J | K | L | ; | ' |Return| | 4 | 5 | 6 | , |
 * +---------------------------------------------------------+ +---+---+---+---+
 * | Shift  | Z | X | C | V | B | N | M | , | . | / |  Shift | | 1 | 2 | 3 |   |
 * +---------------------------------------------------------+ +-------+---|Ent|
 *     |Opt|Apple|                                 |Enter|Opt| |   0   | . |   |
 *     +-----------------------------------------------------+ +-------+---+---+
 */
#define LAYOUT( \
    K68, K74, K71, K72, K73, K64, K61, K62, K63, K50, K51, K40, K41, K45, K20, K21, K22, K23, \
    K78, K75, K77, K60, K65, K66, K67, K52, K53, K5F, K44, K56, K57, K42, K24, K25, K26, K27, \
    K7D, K70, K76, K7B, K69, K6A, K6B, K54, K55, K59, K5A, K5B, K48,      K28, K29, K2A, K2B, \
    K7E, K79, K7A, K6D, K6C, K6E, K6F, K58, K5D, K5E, K4C, K7EX,          K4D, K2D, K2E, K2F, \
         K7C, K7F, K5C,                               K46, K4E,           K49,      K2C       \
) { \
   { KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO },  \
   { KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO },  \
   { KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO },  \
   { KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO },  \
   { K20, K21, K22, K23, K24, K25, K26, K27 },                  \
   { K28, K29, K2A, K2B, K2C, K2D, K2E, K2F },                  \
   { KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO },  \
   { KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO },  \
   { K40, K41, K42, KC_NO, K44, K45, K46, KC_NO },              \
   { K48, K49, KC_NO, KC_NO, K4C, K4D, K4E, KC_NO },            \
   { K50, K51, K52, K53, K54, K55, K56, K57 },                  \
   { K58, K59, K5A, K5B, K5C, K5D, K5E, K5F },                  \
   { K60, K61, K62, K63, K64, K65, K66, K67 },                  \
   { K68, K69, K6A, K6B, K6C, K6D, K6E, K6F },                  \
   { K70, K71, K72, K73, K74, K75, K76, K77 },                  \
   { K78, K79, K7A, K7B, K7C, K7D, K7E, K7F }                   \
}
