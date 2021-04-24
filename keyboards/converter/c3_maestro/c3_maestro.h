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

/* This is a shortcut to help you visually see your layout.
 *
 * The first section contains all of the arguments representing the physical
 * layout of the board and position of the keys.
 *
 * The second converts the arguments into a two-dimensional array which
 * represents the switch matrix.
 */
#define LAYOUT( \
    K12,      K00, K01, K02, K03, K04, K05, K06, K07, K08, K09, \
    K13, K8E, K45, K19, K14,                     K10, K11,           K0C, K0E, K1E, K1F, K20,          K24, K25, K26, \
         K8F, K90, K2E, K28,                     K21, K22, K0F,      K33, K91, K92, K93, K94, K0B,     K36,      K37, \
    K48,      K42, K43, K47, K4A, K2A, K46, K95, K49,      K16, K5A, K5B,           K17, K2C, K1B,     K3E, K3F, K40, \
                                                                                                       K50, K51, K52, \
    K53, K54, K55, K56, K57, K58, K59,      K5C, K5D, K5E, K5F, K60, K61, K62,      K96, K3C, K3D,     K63, K64, K65, \
    K7C, K7D, K7E, K7F, K80, K81, K82,      K84, K85, K86, K87, K88, K89, K8A,      K3B, K97, K4D,     K79, K7A, K7B, \
                                  K83,                                              K98, K4E, K4F,     K8B, K8C  \
) \
{ \
    { K00, K01,   K02,   K03, K04,   K05,   K06,   K07, K08,   K09,   KC_NO, K0B, K0C, K0D,   K0E,   K0F }, \
    { K10, K11,   K12,   K13, K14,   KC_NO,   K16,   K17, KC_NO,   K19,   KC_NO,   K1B, KC_NO, KC_NO, K1E,   K1F }, \
    { K20, K21, K22, KC_NO, K24,   K25,   K26,   K27, K28,   KC_NO,   K2A,   KC_NO, K2C, KC_NO,   K2E, KC_NO }, \
    { KC_NO, KC_NO, KC_NO, K33, KC_NO,   KC_NO,   K36,   K37, KC_NO,   KC_NO,   KC_NO,   K3B, K3C, K3D,   K3E,   K3F }, \
    { K40, KC_NO,   KC_NO, K43, KC_NO, K45, K46, K47, K48, K49, K4A, KC_NO, KC_NO, K4D,   K4E,   K4F },  \
    { K50, K51, K52, K53, K54, K55, K56, K57, K58, K59, K5A, K5B, K5C, K5D, K5E, K5F }, \
    { K60, K61, K62, K63, K64, K65, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO }, \
    { KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, K79. K7A, K7B, K7C, K7D, K7E, K7F }, \
    { K80, K81, K82, K83, K84, K85, K86, K87, K88, K89, K8A, K8B, K8C, KC_NO, K8E, K8F }, \
    { K90, K91, K92, K93, K94, K95, K96, K97, K98, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO } \
}
