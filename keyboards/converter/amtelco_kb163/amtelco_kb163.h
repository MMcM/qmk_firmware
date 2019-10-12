
#pragma once

#include "quantum.h"

/*
 * +---+---+---+  +---+---+---+---+  +---+---+---+---+  +---+---+---+---+  +---+---+---+---+  +---+---+---+---+
 * |335|33C|343|  |33E|346|34D|354|  |303|30B|383|30A|  |32C|344|34E|376|  |32B|334|333|33B|  |366|30D|315|324|
 * +-----------+  +---------------+  +---------------+  +---------------+  +---------------+  +---------------+
 * |355|345|32D|  |325|32E|336|33D|  |301|309|378|307|  |30C|304|306|305|  |342|34B|34C|352|  |35B|31C|31B|323|
 * +-----------+  +---------------+  +---------------+  +---------------+  +---------------+  +---------------+
 * +---+   +---+---+---+---+  +---+---+---+---+  +---+---+---+---+  +---+---+---+  +---+---+---+---+  +---+---+
 * | 76|   | 05| 06| 04| 0C|  | 03| 0B| 83| 0A|  | 01| 09| 78| 07|  |17C| 7E|277|  |31D|316|31E|326|  |349|329|
 * +---+   +---+---+---+---+  +---+---+---+---+  +---+---+---+---+  +---+---+---+  +---+---+---+---+  +---+---+
 * +---+---+---+---+---+---+---+---+---+---+---+---+---+---------+  +---+---+---+  +---+---+---+---+  +---+---+
 * | 0E| 16| 1E| 26| 25| 2E| 36| 3D| 3E| 46| 45| 4E| 55|       66|  |170|16C|17D|  | 77|14A| 7C| 7B|  |33A|341|
 * +-------------------------------------------------------------+  +-----------+  +---------------+  +-------+
 * |   0D| 15| 1D| 24| 2D| 2C| 35| 3C| 43| 44| 4D| 54| 5B|     5D|  |171|169|17A|  | 6C| 75| 7D| 79|  |321|30E|
 * +-------------------------------------------------------------+  +-----------+  +------------   +  +-------+
 * |    58| 1C| 1B| 23| 2B| 34| 33| 3B| 42| 4B| 4C| 52|        5A|                 | 6B| 73| 74|   |  |32A|35D|
 * +-------------------------------------------------------------+      +---+      +---------------+  +-------+
 * |      12| 1A| 22| 21| 2A| 32| 31| 3A| 41| 49| 4A|          59|      |175|      | 69| 72| 7A|15A|  |332|31A|
 * +-------------------------------------------------------------+  +---+---+---+  +------------   +  +-------+
 * |   14|    |  11 |           29              | 111 |    |  114|  |16B|172|174|  |     70| 71|   |  |331|322|
 * +-----+    +---------------------------------------+    +-----+  +---+---+---+  +---------------+  +-------+
 */
#define LAYOUT( \
    K335, K33C, K343, K33E, K346, K34D, K354, K303, K30B, K383, K30A, K32C, K344, K34E, K376, K32B, K334, K333, K33B, K366, K30D, K315, K324, \
    K355, K345, K32D, K325, K32E, K336, K33D, K301, K309, K378, K307, K30C, K304, K306, K305, K342, K34B, K34C, K352, K35B, K31C, K31B, K323, \
    K76, K05, K06, K04, K0C, K03, K0B, K83, K0A, K01, K09, K78, K07, K17C, K7E, K277, K31D, K316, K31E, K326, K349, K329, \
    K0E, K16, K1E, K26, K25, K2E, K36, K3D, K3E, K46, K45, K4E, K55, K66, K170, K16C, K17D, K77, K14A, K7C, K7B, K33A, K341, \
    K0D, K15, K1D, K24, K2D, K2C, K35, K3C, K43, K44, K4D, K54, K5B, K5D, K171, K169, K17A, K6C, K75, K7D, K79, K321, K30E, \
    K58, K1C, K1B, K23, K2B, K34, K33, K3B, K42, K4B, K4C, K52, K5A, K6B, K73, K74, K32A, K35D, \
    K12, K1A, K22, K21, K2A, K32, K31, K3A, K41, K49, K4A, K59, K175, K69, K72, K7A, K15A, K332, K31A, \
    K14, K11, K29, K111, K114, K16B, K172, K174, K70, K71, K331, K322 \
) { \
    { KC_NO, K01, KC_NO, K03, K04, K05, K06, K07, KC_NO, K09, K0A, K0B, K0C, K0D, K0E, KC_NO, KC_NO, K11, K12, KC_NO, K14, K15, K16, KC_NO, KC_NO, KC_NO, K1A, K1B, K1C, K1D, K1E, KC_NO }, \
    { KC_NO, K21, K22, K23, K24, K25, K26, KC_NO, KC_NO, K29, K2A, K2B, K2C, K2D, K2E, KC_NO, KC_NO, K31, K32, K33, K34, K35, K36, KC_NO, KC_NO, KC_NO, K3A, K3B, K3C, K3D, K3E, KC_NO }, \
    { KC_NO, K41, K42, K43, K44, K45, K46, KC_NO, KC_NO, K49, K4A, K4B, K4C, K4D, K4E, KC_NO, KC_NO, KC_NO, K52, KC_NO, K54, K55, KC_NO, KC_NO, K58, K59, K5A, K5B, KC_NO, K5D, KC_NO, KC_NO }, \
    { KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, K66, KC_NO, KC_NO, K69, KC_NO, K6B, K6C, KC_NO, KC_NO, KC_NO, K70, K71, K72, K73, K74, K75, K76, K77, K78, K79, K7A, K7B, K7C, K7D, K7E, KC_NO }, \
    { KC_NO, KC_NO, KC_NO, K83, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO }, \
    { KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO }, \
    { KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO }, \
    { KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO }, \
    { KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, K111, KC_NO, KC_NO, K114, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO }, \
    { KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO }, \
    { KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, K14A, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, K15A, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO }, \
    { KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, K169, KC_NO, K16B, K16C, KC_NO, KC_NO, KC_NO, K170, K171, K172, KC_NO, K174, K175, KC_NO, KC_NO, KC_NO, KC_NO, K17A, KC_NO, K17C, K17D, KC_NO, KC_NO }, \
    { KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO }, \
    { KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO }, \
    { KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO }, \
    { KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO }, \
    { KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO }, \
    { KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO }, \
    { KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO }, \
    { KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, K277, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO }, \
    { KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO }, \
    { KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO }, \
    { KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO }, \
    { KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO }, \
    { KC_NO, K301, KC_NO, K303, K304, K305, K306, K307, KC_NO, K309, K30A, K30B, K30C, K30D, K30E, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, K315, K316, KC_NO, KC_NO, KC_NO, K31A, K31B, K31C, K31D, K31E, KC_NO }, \
    { KC_NO, K321, K322, K323, K324, K325, K326, KC_NO, KC_NO, K329, K32A, K32B, K32C, K32D, K32E, KC_NO, KC_NO, K331, K332, K333, K334, K335, K336, KC_NO, KC_NO, KC_NO, K33A, K33B, K33C, K33D, K33E, KC_NO }, \
    { KC_NO, K341, K342, K343, K344, K345, K346, KC_NO, KC_NO, K349, KC_NO, K34B, K34C, K34D, K34E, KC_NO, KC_NO, KC_NO, K352, KC_NO, K354, K355, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, K35B, KC_NO, K35D, KC_NO, KC_NO }, \
    { KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, K366, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, K376, KC_NO, K378, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO }, \
    { KC_NO, KC_NO, KC_NO, K383, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO }, \
    { KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO }, \
    { KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO }, \
    { KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO } \
}
