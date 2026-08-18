// SPDX-License-Identifier: GPL-2.0-or-later
//
// TGR Lena Mini (KLC rerun). The Mini PCB runs the kopibeng/tgr_lena firmware
// (same MCU, matrix pins, and USB IDs) but only populates a subset of the
// matrix: the right nav block (cols 15-17) does not exist, and the left flank
// is 3 keys ([0,0]/[1,0]/[2,0]). Absent positions are left transparent.

#include "keycodes.h"
#include QMK_KEYBOARD_H

enum layers {
    _COLEMAK,
    _FN,
};

#define SUP_ESC LGUI_T(KC_ESC)
#define SUP_ENT RGUI_T(KC_ENT)
#define FN_TAB LT(_FN, KC_TAB)
#define FN_BSLS LT(_FN, KC_BSLS)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_COLEMAK] = LAYOUT_all(
        KC_DEL,  QK_GESC, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC, KC_BSPC, _______, _______, _______,
        KC_PGUP, FN_TAB,  KC_Q,    KC_W,    KC_F,    KC_P,    KC_G,    KC_J,    KC_L,    KC_U,    KC_Y,    KC_SCLN, KC_LBRC, KC_RBRC,          FN_BSLS, _______, _______, _______,
        KC_PGDN, SUP_ESC, KC_A,    KC_R,    KC_S,    KC_T,    KC_D,    KC_H,    KC_N,    KC_E,    KC_I,    KC_O,    KC_QUOT,                   SUP_ENT, _______, _______, _______,
                 KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_B,    KC_K,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,          MO(_FN), _______, _______, _______,
                 KC_LCTL,          KC_LALT,          KC_SPC,  KC_LGUI,          KC_SPC,           KC_RALT,                   KC_RGUI,          KC_RCTL, _______, _______, _______
    ),

    [_FN] = LAYOUT_all(
        QK_BOOT, _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_DEL,  KC_DEL,  _______, _______, _______,
        _______, _______, _______, KC_PGDN, KC_PGUP, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______, _______, _______,
        _______, _______, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, _______, _______, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, _______,                   _______, _______, _______, _______,
                 _______, RM_TOGG, RM_NEXT, RM_VALU, RM_HUEU, RM_SATU, _______, _______, _______, _______, _______, _______, _______,          _______, _______, _______, _______,
                 _______,          _______,          KC_LCTL, _______,          KC_LCTL,          _______,                   _______,          _______, _______, _______, _______
    ),
};
