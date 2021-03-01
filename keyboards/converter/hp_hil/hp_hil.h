
#pragma once

#include "quantum.h"

/*
 * Note that these macros are slightly different from most keyboards in that they only define a
 * section of the keymap, so that multiple can be used in keymap.c.
 */
#define SUB_LAYOUT_EMPTY() \
    { KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO }, \
    { KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO }, \
    { KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO }, \
    { KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO }, \
    { KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO }, \
    { KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO }, \
    { KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO }, \
    { KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO }

/*
 * 46021 (keycode Set 1):
 *
 * +---+---+ +----+----+----+----+---+---+----+----+----+----+ +---+---+   +---+---+---+---+
 * |0E |9C | |98  |96  |94  |92  |90 |A0 |A2  |A4  |A6  |A8  | |AC |AE |   |4A |42 |46 |4E |
 * +---+---+ +----+----+----+----+---+---+----+----+----+----+ +---+---+   +---+---+---+---+
 * +----+---+---+---+---+---+---+---+---+---+---+---+---+------+---+---+   +---+---+---+---+
 * |7E  |7C |7A |78 |76 |74 |72 |70 |B0 |B2 |B4 |B6 |B8 |BA    |BC |BE |   |2A |22 |26 |2E |
 * +-------------------------------------------------------------------+   +---------------+
 * |6E    |6C |6A |68 |66 |64 |62 |60 |C0 |C2 |C4 |C6 |C8 |CA  |CC |CE |   |1A |12 |16 |1E |
 * +-------------------------------------------------------------------+   +---------------+
 * |5E |0C |5A |58 |56 |54 |52 |50 |D0 |D2 |D4 |D6 |D8 |DA     |DC |DE |   |10 |14 |18 |1C |
 * +-------------------------------------------------------------------+   +---------------+
 * |3E |0A   |38 |36 |34 |32 |30 |F0 |E0 |E2 |E4 |E6 |08   |EA |FC |EE |   |20 |24 |28 |4C |
 * +---+-----+---------------------------------------+-----+-----------+   +-----------|   |
 * |9E |     |06 |F2                             |04 |     |F8 |FA |FE |   |2C     |48 |   |
 * +---+     +---+-------------------------------+---+     +---+---+---+   +-------+---+---+
 *
 */
#define SUB_LAYOUT_46021( \
    K0E, K9C, K98, K96, K94, K92, K90, KA0, KA2, KA4, KA6, KA8, KAC, KAE, K4A, K42, K46, K4E, \
    K7E, K7C, K7A, K78, K76, K74, K72, K70, KB0, KB2, KB4, KB6, KB8, KBA, KBC, KBE, K2A, K22, K26, K2E, \
    K6E, K6C, K6A, K68, K66, K64, K62, K60, KC0, KC2, KC4, KC6, KC8, KCA, KCC, KCE, K1A, K12, K16, K1E, \
    K5E, K0C, K5A, K58, K56, K54, K52, K50, KD0, KD2, KD4, KD6, KD8, KDA, KDC, KDE, K10, K14, K18, K1C, \
    K3E, K0A, K38, K36, K34, K32, K30, KF0, KE0, KE2, KE4, KE6, K08, KEA, KFC, KEE, K20, K24, K28, K4C, \
    K9E, K06, KF2, K04, KF8, KFA, KFE, K2C, K48 \
) \
    { KC_NO, KC_NO, K04, K06, K08, K0A, K0C, K0E, K10, K12, K14, K16, K18, K1A, K1C, K1E }, \
    { K20, K22, K24, K26, K28, K2A, K2C, K2E, K30, K32, K34, K36, K38, KC_NO, KC_NO, K3E }, \
    { KC_NO, K42, KC_NO, K46, K48, K4A, K4C, K4E, K50, K52, K54, K56, K58, K5A, KC_NO, K5E }, \
    { K60, K62, K64, K66, K68, K6A, K6C, K6E, K70, K72, K74, K76, K78, K7A, K7C, K7E }, \
    { KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, K90, K92, K94, K96, K98, KC_NO, K9C, K9E }, \
    { KA0, KA2, KA4, KA6, KA8, KC_NO, KAC, KAE, KB0, KB2, KB4, KB6, KB8, KBA, KBC, KBE }, \
    { KC0, KC2, KC4, KC6, KC8, KCA, KCC, KCE, KD0, KD2, KD4, KD6, KD8, KDA, KDC, KDE }, \
    { KE0, KE2, KE4, KE6, KC_NO, KEA, KC_NO, KEE, KF0, KF2, KC_NO, KC_NO, KF8, KFA, KFC, KFE }

/*
 * 46086 (keycode Set 2):
 *
 *     +---+---+---+---+
 *     |00 |02 |04 |06 |
 * +---+---------------+---+
 * |08 |0A |0C |0E |10 |12 |
 * +---+---------------+---+
 * |14 |16 |18 |1A |1C |1E |
 * +---+---------------+---+
 * |20 |22 |24 |26 |28 |2A |
 * +---+---------------+---+
 * |2C |2E |30 |32 |34 |36 |
 * +---+---------------+---+
 *     |38 |3A |3C |3E |
 *     +---+---+---+---+
 *
 */
#define SUB_LAYOUT_46086( \
    K00, K02, K04, K06, \
    K08, K0A, K0C, K0E, K10, K12, \
    K14, K16, K18, K1A, K1C, K1E, \
    K20, K22, K24, K26, K28, K2A, \
    K2C, K2E, K30, K32, K34, K36, \
    K38, K3A, K3C, K3E \
) \
    { K00, K02, K04, K06, K08, K0A, K0C, K0E, K10, K12, K14, K16, K18, K1A, K1C, K1E }, \
    { K20, K22, K24, K26, K28, K2A, K2C, K2E, K30, K32, K34, K36, K38, K3A, K3C, K3E }, \
    { KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO }, \
    { KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO }, \
    { KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO }, \
    { KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO }, \
    { KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO }, \
    { KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO }
    
/*
 * 98203 (keycode Set 2):
 *
 *         +---+---+---+---+---+   +---+---+   +---+---+---+           +---+---+---+---+
 *         |34 |36 |38 |40 |42 |   |44 |46 |   |50 |52 |54 |           |60 |62 |64 |66 |
 *         +---+---+---+---+---+   +---+---+   +---+---+---+           +---+---+---+---+
 *         +---+---+---+---+---+   +---+---+   +---+---+---+           +---+---+---+---+
 *         |3A |3C |3E |48 |4A |   |4C |4E |   |56 |58 |5A |           |68 |6A |6C |6E |
 *         +---+---+---+---+---+   +---+---+   +---+---+---+           +---+---+---+---+
 * +---+---+---+---+---+---+---+---+---+---+---+---+---+---+  +-----+  +---+---+---+---+
 * |0C |A0 |A2 |A4 |A6 |A8 |AA |AC |AE |B0 |B2 |B4 |B6 |5C |  |70   |  |98 |9A |9C |9E |
 * +-------------------------------------------------------+  +-----+  +---------------+
 * |32   |D0 |D2 |D4 |D6 |D8 |DA |DC |DE |C8 |CA |B8 |BA | |  |5E   |  |90 |92 |94 |96 |
 * +------------------------------------------------------ |  +-----+  +---------------+
 * |30     |E0 |E2 |E4 |E6 |E8 |EA |EC |CC |CE |BC |BE |72 |  |74   |  |88 |8A |8C |8E |
 * +-------------------------------------------------------+  +-----+  +---------------+
 * |0A       |F0 |F2 |F4 |F6 |F8 |FA |EE |C0 |C2 |C4 |0A   |           |80 |82 |84 |86 |
 * +---------+---+-------------------------------+---+-----+  +-----+  +---------------+
 *               |C6                             |            |76   |  |78 |7A |7C |7E |
 *               +-------------------------------+            +-----+  +---+---+---+---+
 *
 */
#define SUB_LAYOUT_98203( \
    K34, K36, K38, K40, K42, K44, K46, K50, K52, K54, K60, K62, K64, K66, \
    K3A, K3C, K3E, K48, K4A, K4C, K4E, K56, K58, K5A, K68, K6A, K6C, K6E, \
    K0C, KA0, KA2, KA4, KA6, KA8, KAA, KAC, KAE, KB0, KB2, KB4, KB6, K5C, K70, K98, K9A, K9C, K9E, \
    K32, KD0, KD2, KD4, KD6, KD8, KDA, KDC, KDE, KC8, KCA, KB8, KBA, K5E, K90, K92, K94, K96, \
    K30, KE0, KE2, KE4, KE6, KE8, KEA, KEC, KCC, KCE, KBC, KBE, K72, K74, K88, K8A, K8C, K8E, \
    K0A, KF0, KF2, KF4, KF6, KF8, KFA, KEE, KC0, KC2, KC4, K80, K82, K84, K86, \
    KC6, K76, K78, K7A, K7C, K7E \
) \
    { KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, K0A, K0C, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO }, \
    { KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, K30, K32, K34, K36, K38, K3A, K3C, K3E }, \
    { K40, K42, K44, K46, K48, K4A, K4C, K4E, K50, K52, K54, K56, K58, K5A, K5C, K5E }, \
    { K60, K62, K64, K66, K68, K6A, K6C, K6E, K70, K72, K74, K76, K78, K7A, K7C, K7E }, \
    { K80, K82, K84, K86, K88, K8A, K8C, K8E, K90, K92, K94, K96, K98, K9A, K9C, K9E }, \
    { KA0, KA2, KA4, KA6, KA8, KAA, KAC, KAE, KB0, KB2, KB4, KB6, KB8, KBA, KBC, KBE }, \
    { KC0, KC2, KC4, KC6, KC8, KCA, KCC, KCE, KD0, KD2, KD4, KD6, KD8, KDA, KDC, KDE }, \
    { KE0, KE2, KE4, KE6, KE8, KEA, KEC, KEE, KF0, KF2, KF4, KF6, KF8, KFA, KC_NO, KC_NO }
