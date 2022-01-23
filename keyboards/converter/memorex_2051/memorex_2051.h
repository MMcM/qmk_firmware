
#pragma once

#include "quantum.h"

/*
 * +---+---+   +---+---+---+---+---+---+---+---+---+---+---+---+---+-----+-----------+---+
 * |C1 |09 |   |83 |73 |B3 |33 |D3 |53 |93 |13 |E3 |63 |A3 |23 |C3 |43   |2D         |CD |
 * +-------+   +-------------------------------------------------------------------------+
 * |C9 |49 |   |FB   |7B |BB |3B |DB |5B |9B |1B |EB |6B |AB |2B |CB |4B |1D |ED |6D |8D |
 * +-------+   +-----------------------------------------------------|   ----------------+
 * |89 |41 |   |D5/D4|77 |B7 |37 |D7 |57 |97 |17 |E7 |67 |A7 |27 |C7 |   |DD |5D |9D |4D |
 * +-------+   +---------------------------------------------------------------------|   |
 * |71 |F1 |   |1514|8F |7F |BF |3F |DF |5F |9F |1F |EF |6F |AF |9594|CF |7D |BD |3D |   |
 * +-------+   +---------------------------------------------------------------------|   |
 * |B1 |31 |   |81       |0F                                 |E9     |FD         |AD |   |
 * +---+---+   +---------+-----------------------------------+-------+-----------+---+---+
 */

#define LAYOUT( \
    KC1, K09, K83, K73, KB3, K33, KD3, K53, K93, K13, KE3, K63, KA3, K23, KC3, K43, K2D, KCD, \
    KC9, K49, KFB, K7B, KBB, K3B, KDB, K5B, K9B, K1B, KEB, K6B, KAB, K2B, KCB, K4B, K1D, KED, K6D, K8D, \
    K89, K41, KD5, K77, KB7, K37, KD7, K57, K97, K17, KE7, K67, KA7, K27, KC7, KDD, K5D, K9D, K4D, \
    K71, KF1, K15, K8F, K7F, KBF, K3F, KDF, K5F, K9F, K1F, KEF, K6F, KAF, K95, KCF, K7D, KBD, K3D, \
    KB1, K31, K81, K0F, KE9, KFD, KAD) { \
    { KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, K09, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, K0F }, \
    { KC_NO, KC_NO, KC_NO, K13, KC_NO, K15, KC_NO, K17, KC_NO, KC_NO, KC_NO, K1B, KC_NO, K1D, KC_NO, K1F }, \
    { KC_NO, KC_NO, KC_NO, K23, KC_NO, KC_NO, KC_NO, K27, KC_NO, KC_NO, KC_NO, K2B, KC_NO, K2D, KC_NO, KC_NO }, \
    { KC_NO, K31, KC_NO, K33, KC_NO, KC_NO, KC_NO, K37, KC_NO, KC_NO, KC_NO, K3B, KC_NO, K3D, KC_NO, K3F }, \
    { KC_NO, K41, KC_NO, K43, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, K49, KC_NO, K4B, KC_NO, K4D, KC_NO, KC_NO }, \
    { KC_NO, KC_NO, KC_NO, K53, KC_NO, KC_NO, KC_NO, K57, KC_NO, KC_NO, KC_NO, K5B, KC_NO, K5D, KC_NO, K5F }, \
    { KC_NO, KC_NO, KC_NO, K63, KC_NO, KC_NO, KC_NO, K67, KC_NO, KC_NO, KC_NO, K6B, KC_NO, K6D, KC_NO, K6F }, \
    { KC_NO, K71, KC_NO, K73, KC_NO, KC_NO, KC_NO, K77, KC_NO, KC_NO, KC_NO, K7B, KC_NO, K7D, KC_NO, K7F }, \
    { KC_NO, K81, KC_NO, K83, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, K89, KC_NO, KC_NO, KC_NO, K8D, KC_NO, K8F }, \
    { KC_NO, KC_NO, KC_NO, K93, KC_NO, K95, KC_NO, K97, KC_NO, KC_NO, KC_NO, K9B, KC_NO, K9D, KC_NO, K9F }, \
    { KC_NO, KC_NO, KC_NO, KA3, KC_NO, KC_NO, KC_NO, KA7, KC_NO, KC_NO, KC_NO, KAB, KC_NO, KAD, KC_NO, KAF }, \
    { KC_NO, KB1, KC_NO, KB3, KC_NO, KC_NO, KC_NO, KB7, KC_NO, KC_NO, KC_NO, KBB, KC_NO, KBD, KC_NO, KBF }, \
    { KC_NO, KC1, KC_NO, KC3, KC_NO, KC_NO, KC_NO, KC7, KC_NO, KC9, KC_NO, KCB, KC_NO, KCD, KC_NO, KCF }, \
    { KC_NO, KC_NO, KC_NO, KD3, KC_NO, KD5, KC_NO, KD7, KC_NO, KC_NO, KC_NO, KDB, KC_NO, KDD, KC_NO, KDF }, \
    { KC_NO, KC_NO, KC_NO, KE3, KC_NO, KC_NO, KC_NO, KE7, KC_NO, KE9, KC_NO, KEB, KC_NO, KED, KC_NO, KEF }, \
    { KC_NO, KF1, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KFB, KC_NO, KFD, KC_NO, KC_NO } \
 }
