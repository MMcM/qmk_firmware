
#pragma once

#include "quantum.h"

/*
 * Most of these are based on the base character, with others chosen to make the matrix smaller and the mapping
 * reasonably compact.
 *
 * +---+  +---+
 * |03 |  |08 |
 * +---+  +---+
 *
 * +---+---+-------+-------+-------+-------+-------+---+---+-----+
 * |8A*|8D |80     |81     |82     |83     |84     |0C |7E |7F   |
 * +-------------------------------------------------------------+
 * |1B |31 |32 |33 |34 |35 |36 |37 |38 |39 |30 |2D |5E |5C |12   |
 * +-------------------------------------------------------------+
 * |09   |71 |77 |65 |72 |74 |79 |75 |69 |6F |70 |40 |5B |5D |   |
 * +---------------------------------------------------------|   |
 * |01    |61 |73 |64 |66 |67 |68 |6A |6B |6C |3B |3A |5F |0D    |
 * +-------------------------------------------------------------+
 * |00*     |7A |78 |63 |76 |62 |6E |6D |2C |2E |2F |00* |1E*|8E |
 * +-------------------------------------------------------------+
 * |8B |02 |20*                                      |1D*|1F*|1C*|
 * +---+---+-----------------------------------------+---+---+---+
 *
 * The seven game keys are marked with *.
 */

#define LAYOUT( \
    K03, K08, \
    K8A, K8D, K80, K81, K82, K83, K84, K0C, K7E, K7F, \
    K1B, K31, K32, K33, K34, K35, K36, K37, K38, K39, K30, K2D, K5E, K5C, K12, \
    K09, K71, K77, K65, K72, K74, K79, K75, K69, K6F, K70, K40, K5B, K5D, \
    K01, K61, K73, K64, K66, K67, K68, K6A, K6B, K6C, K3B, K3A, K5F, K0D, \
    K00, K7A, K78, K63, K76, K62, K6E, K6D, K2C, K2E, K2F, K00X, K1E, K8E, \
    K8B, K02, K20, K1D, K1F, K1C) { \
    { K00, K01, K02, K03, KC_NO, KC_NO, KC_NO, KC_NO, K08, K09, KC_NO, KC_NO, K0C, K0D, KC_NO, KC_NO }, \
    { KC_NO, KC_NO, K12, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, K1B, K1C, K1D, K1E, K1F }, \
    { K20, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, K2C, K2D, K2E, K2F }, \
    { K30, K31, K32, K33, K34, K35, K36, K37, K38, K39, K3A, K3B, KC_NO, KC_NO, KC_NO, KC_NO }, \
    { K40, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO }, \
    { KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, K5B, K5C, K5D, K5E, K5F }, \
    { KC_NO, K61, K62, K63, K64, K65, K66, K67, K68, K69, K6A, K6B, K6C, K6D, K6E, K6F }, \
    { K70, K71, K72, K73, K74, K75, K76, K77, K78, K79, K7A, KC_NO, KC_NO, KC_NO, K7E, K7F }, \
    { K80, K81, K82, K83, K84, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, K8A, K8B, KC_NO, K8D, K8E, KC_NO } \
 }
