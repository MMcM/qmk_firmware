
#pragma once

#include "quantum.h"

/*
 * +---+---+---+---+---+  +---+---+---+---+---+  +---+---+---+---+  +---+-------+  +---+---+---+---+
 * |56 |57 |58 |59 |5A |  |64 |65 |66 |67 |68 |  |71 |72 |73 |74 |  |7C |7D     |  |80 |81 |82 |83 |
 * +---+---+---+---+---+  +---+---+---+---+---+  +---+---+---+---+  +---+-------+  +---+---+---+---+
 *    +---+---+---+---+---+---+---+---+---+---+---+---+---+------+  +---+---+---+  +---+---+---+---+
 *    |BF |C0 |C5 |CB |D0 |D6 |DB |E0 |E5 |EA |EF |F9 |F5 |BC    |  |8A |8B |8C |  |A1 |A2 |A3 |A4 |
 *    +----------------------------------------------------------+  +-----------+  +---------------+
 *    |BE   |C1 |C6 |CC |D1 |D7 |DC |E1 |E6 |EB |F0 |FA |F6 |BD  |  |8D |8E |8F |  |9D |9E |9F |A0 |
 * +--+------------------------------------------------------+   |  +-----------+  +---------------+
 * |AF |B0   |C2 |C7 |CD |D2 |D8 |DD |E2 |E7 |EC |F2 |FB |F7 |   |      |AA |      |99 |9A |9B |9C |
 * +-------------------------------------------------------------+  +-----------+  +---------------+
 * |AE      |C9 |C3 |C8 |CE |D3 |D9 |DE |E3 |E8 |ED |F3 |AB      |  |A7 |A9 |A8 |  |96 |97 |98 |95 |
 * +------+---------------------------------------------------+--+  +---+---+---+  +------------   |
 *        |B1   |AC   |D4                         |B2   |AD   |                    |92     |94 |   |
 *        +-----+-----+---------------------------+-----+-----+                    +-------+---+---+
 */
#define LAYOUT( \
    K56, K57, K58, K59, K5A, K64, K65, K66, K67, K68, K71, K72, K73, K74, K7C, K7D, K80, K81, K82, K83, \
    KBF, KC0, KC5, KCB, KD0, KD6, KDB, KE0, KE5, KEA, KEF, KF9, KF5, KBC, K8A, K8B, K8C, KA1, KA2, KA3, KA4, \
    KBE, KC1, KC6, KCC, KD1, KD7, KDC, KE1, KE6, KEB, KF0, KFA, KF6, KBD, K8D, K8E, K8F, K9D, K9E, K9F, KA0, \
    KAF, KB0, KC2, KC7, KCD, KD2, KD8, KDD, KE2, KE7, KEC, KF2, KFB, KF7, KAA, K99, K9A, K9B, K9C, \
    KAE, KC9, KC3, KC8, KCE, KD3, KD9, KDE, KE3, KE8, KED, KF3, KAB, KA7, KA9, KA8, K96, K97, K98, K95, \
    KB1, KAC, KD4, KB2, KAD, K92, K94) { \
    { KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO }, \
    { KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO }, \
    { KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO }, \
    { KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO }, \
    { KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO }, \
    { KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, K56, K57, K58, K59, K5A, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO }, \
    { KC_NO, KC_NO, KC_NO, KC_NO, K64, K65, K66, K67, K68, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO }, \
    { KC_NO, K71, K72, K73, K74, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, K7C, K7D, KC_NO, KC_NO }, \
    { K80, K81, K82, K83, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, K8A, K8B, K8C, K8D, K8E, K8F }, \
    { KC_NO, KC_NO, K92, KC_NO, K94, K95, K96, K97, K98, K99, K9A, K9B, K9C, K9D, K9E, K9F }, \
    { KA0, KA1, KA2, KA3, KA4, KC_NO, KC_NO, KA7, KA8, KA9, KAA, KAB, KAC, KAD, KAE, KAF }, \
    { KB0, KB1, KB2, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KBC, KBD, KBE, KBF }, \
    { KC0, KC1, KC2, KC3, KC_NO, KC5, KC6, KC7, KC8, KC9, KC_NO, KCB, KCC, KCD, KCE, KC_NO }, \
    { KD0, KD1, KD2, KD3, KD4, KC_NO, KD6, KD7, KD8, KD9, KC_NO, KDB, KDC, KDD, KDE, KC_NO }, \
    { KE0, KE1, KE2, KE3, KC_NO, KE5, KE6, KE7, KE8, KC_NO, KEA, KEB, KEC, KED, KC_NO, KEF }, \
    { KF0, KC_NO, KF2, KF3, KC_NO, KF5, KF6, KF7, KC_NO, KF9, KFA, KFB, KC_NO, KC_NO, KC_NO, KC_NO } \
}

/*
 * +---+---+---+---+---+   +---+---+---+---+---+   +---+---+---+---+   +---+   +---+   +---+---+---+---+
 * |56 |57 |58 |59 |5A |   |64 |65 |66 |67 |68 |   |71 |72 |73 |74 |   |7C |   |7D |   |80 |81 |82 |83 |
 * +---+---+---+---+---+   +---+---+---+---+---+   +---+---+---+---+   +---+   +---+   +---+---+---+---+
 * +---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+   +---+---+---+   +---+---+---+---+
 * |FC |BF |C0 |C5 |CB |D0 |D6 |DB |E0 |E5 |EA |EF |F9 |F5 |C9 |BC |   |8A |8B |8C |   |A1 |A2 |A3 |A4 |
 *   +-----------------------------------------------------------+-+   +-----------+   +---------------+
 *   |BE |C1 |C6 |CC |D1 |D7 |DC |E1 |E6 |EB |F0 |FA |F6 |C4 |BD |     |8D |8E |8F |   |9D |9E |9F |A0 |
 * +-+---------------------------------------------------------+-+     +---+---+---+   +---------------+
 * |AF |B0 |C2 |C7 |CD |D2 |D8 |DD |E2 |E7 |EC |F2 |FB |F7 |FD |           |AA |       |99 |9A |9B |9C |
 * +-+---------------------------------------------------------+-+     +---+---+---+   +---------------+
 *   |AE |B2 |C3 |C8 |CE |D3 |D9 |DE |E3 |E8 |ED |F3 |CA |F1 |AE |     |A7 |A9 |A8 |   |96 |97 |98 |94 |
 *   +-------+---------------------------------------+---+---+---+     +---+---+---+   +---------------+
 *           |B1 |D4                                 |                                 |92     |95     |
 *           +---+-----------------------------------+                                 +-------+-------+
 */
#define LAYOUT_ms_7004( \
    K56, K57, K58, K59, K5A, K64, K65, K66, K67, K68, K71, K72, K73, K74, K7C, K7D, K80, K81, K82, K83, \
    KFC, KBF, KC0, KC5, KCB, KD0, KD6, KDB, KE0, KE5, KEA, KEF, KF9, KF5, KC9, KBC, K8A, K8B, K8C, KA1, KA2, KA3, KA4, \
    KBE, KC1, KC6, KCC, KD1, KD7, KDC, KE1, KE6, KEB, KF0, KFA, KF6, KC4, KBD, K8D, K8E, K8F, K9D, K9E, K9F, KA0, \
    KAF, KB0, KC2, KC7, KCD, KD2, KD8, KDD, KE2, KE7, KEC, KF2, KFB, KF7, KFD, KAA, K99, K9A, K9B, K9C, \
    KAE, KB2, KC3, KC8, KCE, KD3, KD9, KDE, KE3, KE8, KED, KF3, KCA, KF1, KA7, KA9, KA8, K96, K97, K98, K94, \
    KB1, KD4, K92, K95) { \
    { KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO }, \
    { KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO }, \
    { KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO }, \
    { KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO }, \
    { KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO }, \
    { KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, K56, K57, K58, K59, K5A, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO }, \
    { KC_NO, KC_NO, KC_NO, KC_NO, K64, K65, K66, K67, K68, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO }, \
    { KC_NO, K71, K72, K73, K74, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, K7C, K7D, KC_NO, KC_NO }, \
    { K80, K81, K82, K83, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, K8A, K8B, K8C, K8D, K8E, K8F }, \
    { KC_NO, KC_NO, K92, KC_NO, K94, K95, K96, K97, K98, K99, K9A, K9B, K9C, K9D, K9E, K9F }, \
    { KA0, KA1, KA2, KA3, KA4, KC_NO, KC_NO, KA7, KA8, KA9, KAA, KC_NO, KC_NO, KC_NO, KAE, KAF }, \
    { KB0, KB1, KB2, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KBC, KBD, KBE, KBF }, \
    { KC0, KC1, KC2, KC3, KC4, KC5, KC6, KC7, KC8, KC9, KCA, KCB, KCC, KCD, KCE, KC_NO }, \
    { KD0, KD1, KD2, KD3, KD4, KC_NO, KD6, KD7, KD8, KD9, KC_NO, KDB, KDC, KDD, KDE, KC_NO }, \
    { KE0, KE1, KE2, KE3, KC_NO, KE5, KE6, KE7, KE8, KC_NO, KEA, KEB, KEC, KED, KC_NO, KEF }, \
    { KF0, KF1, KF2, KF3, KC_NO, KF5, KF6, KF7, KC_NO, KF9, KFA, KFB, KFC, KFD, KC_NO, KC_NO } \
}
