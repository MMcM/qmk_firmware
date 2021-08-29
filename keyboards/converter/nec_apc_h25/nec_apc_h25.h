
#pragma once

#include "quantum.h"

/*
 *   +---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+
 *   |00*|80 |81 |82 |83 |84 |85 |86 |87 |88 |89 |8A |8B |8C |8D |8E |8F |90 |91 |92 |93 |94 |95 |
 *   +---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+
 *   +---+---+---+---+---+---+---+---+---+---+---+---+---+---+-----+     +---+---+---+---+---+---+
 *   |1B |31 |32 |33 |34 |35 |36 |37 |38 |39 |30 |5F |2D |40 |9C   |     |FB |6F |9A |FF |96     |
 *   +-------------------------------------------------------------+     +-----------------------+
 *   |98   |51 |57 |45 |52 |54 |59 |55 |49 |4F |50 |5B |5D |5C |5E |     |FC |6A |77 |78 |79 |6D |
 *   +-------------------------------------------------------------+     +-----------------------+
 *   |01*|0A*|41 |53 |44 |46 |47 |48 |4A |4B |4C |3A |3B |97       |     |F7     |74 |75 |76 |6B |
 *   +-------------------------------------------------------------+     +-----------------------+
 *   |08*      |5A |58 |43 |56 |42 |4E |4D |2C |2E |2F |08*        |     |FA |F9 |71 |72 |73 |FD |
 *   +-------------------------------------------------------------+     +-------------------|   |
 *   |02*   |03*   |20                                 |05*  |9E   |     |F8     |70     |6E |   |
 *   +-------------+-----------------------------------+-----+-----+     +-------+-------+---+---+
 *
 *   Shift keys are only sent on conjunction with another key and are handled specially.
 */

#define LAYOUT( \
    K00, K80, K81, K82, K83, K84, K85, K86, K87, K88, K89, K8A, K8B, K8C, K8D, K8E, K8F, K90, K91, K92, K93, K94, K95, \
    K1B, K31, K32, K33, K34, K35, K36, K37, K38, K39, K30, K5F, K2D, K40, K9C, KFB, K6F, K9A, KFF, K96, \
    K98, K51, K57, K45, K52, K54, K59, K55, K49, K4F, K50, K5B, K5D, K5C, K5E, KFC, K6A, K77, K78, K79, K6D, \
    K01, K0A, K41, K53, K44, K46, K47, K48, K4A, K4B, K4C, K3A, K3B, K97, KF7, K74, K75, K76, K6B, \
    K08, K5A, K58, K43, K56, K42, K4E, K4D, K2C, K2E, K2F, K08X, KFA, KF9, K71, K72, K73, KFD, \
    K02, K03, K20, K05, K9E, KF8, K70, K6E) { \
    { K00, K01, K02, K03, KC_NO, K05, KC_NO, KC_NO, K08, KC_NO, K0A, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO }, \
    { KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, K1B, KC_NO, KC_NO, KC_NO, KC_NO }, \
    { K20, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, K2C, K2D, K2E, K2F }, \
    { K30, K31, K32, K33, K34, K35, K36, K37, K38, K39, K3A, K3B, KC_NO, KC_NO, KC_NO, KC_NO }, \
    { K40, K41, K42, K43, K44, K45, K46, K47, K48, K49, K4A, K4B, K4C, K4D, K4E, K4F }, \
    { K50, K51, K52, K53, K54, K55, K56, K57, K58, K59, K5A, K5B, K5C, K5D, K5E, K5F }, \
    { KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, K6A, K6B, KC_NO, K6D, K6E, K6F }, \
    { K70, K71, K72, K73, K74, K75, K76, K77, K78, K79, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO }, \
    { K80, K81, K82, K83, K84, K85, K86, K87, K88, K89, K8A, K8B, K8C, K8D, K8E, K8F }, \
    { K90, K91, K92, K93, K94, K95, K96, K97, K98, KC_NO, K9A, KC_NO, K9C, KC_NO, K9E, KC_NO }, \
    { KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO }, \
    { KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO }, \
    { KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO }, \
    { KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO }, \
    { KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO }, \
    { KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KF7, KF8, KF9, KFA, KFB, KFC, KFD, KC_NO, KFF } \
}
