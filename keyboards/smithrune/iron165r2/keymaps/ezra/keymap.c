#include "keycodes.h"
#include "quantum_keycodes.h"
#include QMK_KEYBOARD_H

enum layers {
    _COLEMAK,
    _FN,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_COLEMAK] = LAYOUT_65_ansi_cb_blocker(
        QK_GESC, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSLS,
        KC_TAB,  KC_Q,    KC_W,    KC_F,    KC_P,    KC_G,    KC_J,    KC_L,    KC_U,    KC_Y,    KC_SCLN, KC_LBRC, KC_RBRC, KC_BSPC, KC_PGUP,
        KC_LGUI, KC_A,    KC_R,    KC_S,    KC_T,    KC_D,    KC_H,    KC_N,    KC_E,    KC_I,    KC_O,    KC_QUOT, KC_ENT,           KC_PGDN,
        KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_K,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,          KC_UP,   MO(_FN),
        KC_LCTL, KC_LALT, MO(_FN),                            KC_SPC,                             KC_RCTL, KC_RGUI, KC_LEFT, KC_DOWN, KC_RGHT
    ),

    [_FN] = LAYOUT_65_ansi_cb_blocker(
        QK_BOOT, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  _______,
        _______, UG_TOGG, UG_NEXT, UG_PREV, UG_HUEU, UG_HUED, UG_SATU, UG_SATD, UG_VALU, UG_VALD, _______, _______, _______, _______, KC_INS,
        _______, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, _______, _______, _______, _______, _______, _______, _______, _______,          KC_HOME,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, KC_END,
        _______, _______, _______,                            _______,                            _______, _______, _______, _______, _______
    ),
};
