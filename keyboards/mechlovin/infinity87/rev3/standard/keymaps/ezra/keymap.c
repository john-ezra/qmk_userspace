// SPDX-License-Identifier: GPL-2.0-or-later
//
// Merisi Works 500C/M on a Mechlovin Infinity87 Rev. 3 PCB. Standard TKL F-row
// on [0,2]..[0,13]. The 7u WKL bottom row uses [5,0] [5,2] [5,6] [5,11] [5,13];
// the blocker slots [5,1] [5,12] and the unused 6.25u slot [5,10] are left
// transparent, as are the ISO left-shift key [4,1] and the 1u right of the
// 1.75u shift [4,13]. Backslash sits on both split-backspace nodes so a 2u cap
// works whichever node it lands on.

#include QMK_KEYBOARD_H

enum layers {
    _COLEMAK,
    _FN,
};

#define SUP_ESC LGUI_T(KC_ESC)
#define SUP_ENT RGUI_T(KC_ENT)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_COLEMAK] = LAYOUT_all(
        KC_ESC,            KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,           KC_PSCR, KC_SCRL, KC_PAUS,
        KC_GRV,   KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSLS, KC_BSLS, KC_INS,  KC_HOME, KC_PGUP,
        KC_TAB,   KC_Q,    KC_W,    KC_F,    KC_P,    KC_G,    KC_J,    KC_L,    KC_U,    KC_Y,    KC_SCLN, KC_LBRC, KC_RBRC, KC_BSPC,          KC_DEL,  KC_END,  KC_PGDN,
        SUP_ESC,  KC_A,    KC_R,    KC_S,    KC_T,    KC_D,    KC_H,    KC_N,    KC_E,    KC_I,    KC_O,    KC_QUOT,          SUP_ENT,
        KC_LSFT,  _______, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_K,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT, _______,                   KC_UP,
        KC_LCTL,  _______, KC_LALT,                            KC_SPC,                             _______, MO(_FN), _______, KC_RCTL,          KC_LEFT, KC_DOWN, KC_RGHT
    ),

    [_FN] = LAYOUT_all(
        QK_BOOT,           _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______, _______,
        _______,  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______,  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______, _______,
        _______,  KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, _______, _______, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, _______,          _______,
        _______,  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,                   _______,
        _______,  _______, _______,                            KC_LCTL,                            _______, _______, _______, _______,          _______, _______, _______
    ),
};
