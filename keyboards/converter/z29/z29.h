
#pragma once

#include "quantum.h"

/*
 *     +---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+
 *     |88 |A0 |A1 |A2 |A3 |A4 |A5 |A6 |A7 |A8 |86 |84 |82 |80 |83 |85 |
 *     +---------------------------------------------------------------+      +---+---+---+---+
 *     |1B |31 |32 |33 |34 |35 |36 |37 |38 |39 |30 |2D |3D |81 |08 |89 |      |97 |98 |99 |9C |
 *     +---------------------------------------------------------------+      +---------------+
 *     |8B   |51 |57 |45 |52 |54 |59 |55 |49 |4F |50 |5B |5D |60 |7F |        |94 |95 |96 |9D |
 *    +--------------------------------------------------------------+        +---------------+
 *    |01 |8A |41 |53 |44 |46 |47 |48 |4A |4B |4C |3B |27 |0D    |5C |        |91 |92 |93 |9B |
 *    +--------------------------------------------------------------+        +-----------+   |
 *    |87 |02   |5A |58 |43 |56 |42 |4E |4D |2C |2E |2F |02   |0A |           |90     |9A |   |
 *    +---+------+--------------------------------------+-----+---+           +-------+---+---+
 *               |8C                                 |
 *               +-----------------------------------+
 *
 * Note: Codes shown are what is stored in the matrix, which is derived from the 8-bit protocol
 * after adjusting for Control, Shift, and Access.
 */

#define LAYOUT( \
    K88, KA0, KA1, KA2, KA3, KA4, KA5, KA6, KA7, KA8, K86, K84, K82, K80, K83, K85, \
    K1B, K31, K32, K33, K34, K35, K36, K37, K38, K39, K30, K2D, K3D, K81, K08, K89, K97, K98, K99, K9C, \
    K8B, K51, K57, K45, K52, K54, K59, K55, K49, K4F, K50, K5B, K5D, K60, K7F, K94, K95, K96, K9D, \
    K01, K8A, K41, K53, K44, K46, K47, K48, K4A, K4B, K4C, K3B, K27, K0D, K5C, K91, K92, K93, K9B, \
    K87, K02, K5A, K58, K43, K56, K42, K4E, K4D, K2C, K2E, K2F, K02X, K0A, K90, K9A, \
    K8C) { \
    { KC_NO, K01, K02, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, K08, KC_NO, K0A, KC_NO, KC_NO, K0D, KC_NO, KC_NO }, \
    { KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, K1B, KC_NO, KC_NO, KC_NO, KC_NO }, \
    { KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, K27, KC_NO, KC_NO, KC_NO, KC_NO, K2C, K2D, K2E, K2F }, \
    { K30, K31, K32, K33, K34, K35, K36, K37, K38, K39, KC_NO, K3B, KC_NO, K3D, KC_NO, KC_NO }, \
    { KC_NO, K41, K42, K43, K44, K45, K46, K47, K48, K49, K4A, K4B, K4C, K4D, K4E, K4F }, \
    { K50, K51, K52, K53, K54, K55, K56, K57, K58, K59, K5A, K5B, K5C, K5D, KC_NO, KC_NO }, \
    { K60, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO }, \
    { KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, K7F }, \
    { K80, K81, K82, K83, K84, K85, K86, K87, K88, K89, K8A, K8B, K8C, KC_NO, KC_NO, KC_NO }, \
    { K90, K91, K92, K93, K94, K95, K96, K97, K98, K99, K9A, K9B, K9C, K9D, KC_NO, KC_NO }, \
    { KA0, KA1, KA2, KA3, KA4, KA5, KA6, KA7, KA8, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO } \
}
