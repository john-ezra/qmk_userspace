/* Copyright 2020 Garret Gartner (Kingly-Keys)
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

#include QMK_KEYBOARD_H

enum layers {
    _COLEMAK,
    _FN,
};

#define SUP_ESC LGUI_T(KC_ESC)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* _COLEMAK: ISO Colemak with left numpad cluster (single 7u spacebar)
     * ISO keys: KC_NUBS (\ |) next to left shift, KC_NUHS (# ~) top-right.
     * The 7u spacebar is matrix [3,11] = LT(_FN, KC_SPC); the split-only
     * switches [3,7]/[3,9]/[3,13] are unpopulated (_______). GUI via SUP_ESC.
     */
    [_COLEMAK] = LAYOUT(
        KC_7,    KC_8,    KC_9,    QK_GESC, KC_TAB,  KC_Q,    KC_W,    KC_F,    KC_P,    KC_G,    KC_J,    KC_L,    KC_U,    KC_Y,    KC_SCLN, KC_QUOT, KC_NUHS,
        KC_4,    KC_5,    KC_6,             SUP_ESC, KC_A,    KC_R,    KC_S,    KC_T,    KC_D,    KC_H,    KC_N,    KC_E,    KC_I,    KC_O,             KC_BSPC,
        KC_1,    KC_2,    KC_3,    KC_UP,   KC_LSFT, KC_NUBS, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_K,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,
        KC_0,    KC_0,    KC_LEFT, KC_DOWN, KC_RGHT, KC_LCTL, KC_LALT, _______, _______, KC_SPC,  _______, KC_RALT, KC_RCTL, MO(_FN)
    ),

    /* _FN: numbers, F-keys, symbols, navigation, media */
    [_FN] = LAYOUT(
        KC_F7,   KC_F8,   KC_F9,   QK_BOOT,  _______, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,
        KC_F4,   KC_F5,   KC_F6,            _______, _______, _______, _______, KC_LBRC, KC_RBRC, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, _______,          KC_DEL,
        KC_F1,   KC_F2,   KC_F3,   KC_PGUP, _______, _______, KC_MUTE, KC_VOLD, KC_VOLU, KC_MPRV, KC_MPLY, KC_MNXT, _______, _______, _______, _______, _______,
        KC_F10,  KC_F11,  KC_HOME, KC_PGDN, KC_END,  _______, _______, _______, _______, _______, _______, _______, _______, _______
    ),
};
