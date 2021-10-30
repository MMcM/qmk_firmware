/* Copyright 2021 RaouldDuke-Esq
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

#include "quantum.h"

/*
 * +---+   +---+---+---+---+---+---+---+---+---+---+
 * |12 |   |00 |01 |02 |03 |04 |05 |06 |07 |08 |09 |
 * +---+   +---+---+---+---+---+---+---+---+---+---+
 * +---+---+---+---+---+               +---+---+---+   +---+---+---+---+---+---+   +---+---+---+
 * |13 |8E |45 |19 |14 |               |10 |11 |0F |   |0C |0E |1E |1F |20 |0B |   |24 |25 |26 |
 * +-------------------+               +-------|   |   +-------------------|   |   +-----------+
 * |ALT|8F |90 |2E |28 |               |21 |22 |   |   |33 |91 |92 |93 |94 |   |   |36     |37 |
 * +---+---+---+---+---+               +---+---+---+   +---+---+---+---+---+---+   +-------+---+
 * +-------+---+---+---+---+---+---+---+---+   +---+---+---+       +---+---+---+   +---+---+---+
 * |48     |42 |43 |47 |4A |2A |46 |95 |49 |   |16 |5A |5B |       |17 |2C |18 |   |3E |3F |40 |
 * +-------+---+---+---+---+---+---+---+---+   +---+---+---+       +---+---+---+   +-----------+
 * +---+---+---+---+---+---+---+   +---+---+---+---+---+---+---+                   |50 |51 |52 |
 * |53 |54 |55 |56 |57 |58 |59 |   |5C |5D |5E |5F |60 |61 |62 |   +---+---+---+   +-----------+
 * +---------------------------+   +---------------------------+   |96 |3C |3D |   |63 |64 |65 |
 * |7C |7D |7E |7F |80 |81 |82 |   |84 |85 |86 |87 |88 |89 |8A |   +-----------+   +-----------+
 * +---+---+---+---+---+---+---+   +---+---+---+---+---+---+---+   |3B |97 |4D |   |79 |7A |7B |
 *                         +-----------+                           +-----------+   +-----------+
 *                         |83         |                           |98 |4E |4F |   |8B |8C     |
 *                         +-----------+                           +---+---+---+   +---+-------+
 */
#define LAYOUT( \
    K12,      K00, K01, K02, K03, K04, K05, K06, K07, K08, K09, \
    K13, K8E, K45, K19, K14,                     K10, K11, K0F,      K0C, K0E, K1E, K1F, K20, K0B,     K24, K25, K26, \
    KALT,K8F, K90, K2E, K28,                     K21, K22,           K33, K91, K92, K93, K94,          K36,      K37, \
    K48,      K42, K43, K47, K4A, K2A, K46, K95, K49,      K16, K5A, K5B,           K17, K2C, K18,     K3E, K3F, K40, \
                                                                                                       K50, K51, K52, \
    K53, K54, K55, K56, K57, K58, K59,      K5C, K5D, K5E, K5F, K60, K61, K62,      K96, K3C, K3D,     K63, K64, K65, \
    K7C, K7D, K7E, K7F, K80, K81, K82,      K84, K85, K86, K87, K88, K89, K8A,      K3B, K97, K4D,     K79, K7A, K7B, \
                                  K83,                                              K98, K4E, K4F,     K8B, K8C \
) \
{ \
    { K00, K01, K02, K03, K04, K05, K06, K07, K08, K09, KC_NO, K0B, K0C, KC_NO, K0E, K0F }, \
    { K10, K11, K12, K13, K14, KC_NO, K16, K17, K18, K19, KC_NO, KC_NO, KC_NO, KC_NO, K1E, K1F }, \
    { K20, K21, K22, KC_NO, K24, K25, K26, KC_NO, K28, KC_NO, K2A, KC_NO, K2C, KC_NO, K2E, KC_NO }, \
    { KC_NO, KC_NO, KC_NO, K33, KC_NO, KC_NO, K36, K37, KC_NO, KC_NO, KC_NO, K3B, K3C, K3D, K3E, K3F }, \
    { K40, KC_NO, K42, K43, KC_NO, K45, K46, K47, K48, K49, K4A, KC_NO, KC_NO, K4D, K4E, K4F }, \
    { K50, K51, K52, K53, K54, K55, K56, K57, K58, K59, K5A, K5B, K5C, K5D, K5E, K5F }, \
    { K60, K61, K62, K63, K64, K65, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO }, \
    { KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, K79, K7A, K7B, K7C, K7D, K7E, K7F }, \
    { K80, K81, K82, K83, K84, K85, K86, K87, K88, K89, K8A, K8B, K8C, KC_NO, K8E, K8F }, \
    { K90, K91, K92, K93, K94, K95, K96, K97, K98, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO }, \
    { KALT } \
 }
