#include "keycodes.h"
#include QMK_KEYBOARD_H

enum layers {
    _COLEMAK,
    _FN,
};

#define SUP_ESC LGUI_T(KC_ESC)
#define SUP_ENT RGUI_T(KC_ENT)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_COLEMAK] = LAYOUT_all(
        QK_GESC, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSLS, KC_INS,
        KC_TAB,  KC_Q,    KC_W,    KC_F,    KC_P,    KC_G,    KC_J,    KC_L,    KC_U,    KC_Y,    KC_SCLN, KC_LBRC, KC_RBRC, KC_BSPC,
        SUP_ESC, KC_A,    KC_R,    KC_S,    KC_T,    KC_D,    KC_H,    KC_N,    KC_E,    KC_I,    KC_O,    KC_QUOT,          SUP_ENT,
        KC_LSFT, _______, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_K,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT, KC_RALT,
        KC_LCTL, KC_RCTL, MO(_FN),                            KC_SPC,                                      MO(_FN), KC_RCTL, KC_RCTL
    ),

    [_FN] = LAYOUT_all(
        QK_BOOT, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_DEL,  _______,
        _______, KC_HOME, KC_PGDN, KC_PGUP, KC_END,  _______, KC_TILD, KC_LCBR, KC_RCBR, _______, _______, _______, _______, KC_INS,
        _______, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, _______, KC_MINS, KC_LPRN, KC_RPRN, _______, _______, _______,          _______,
        _______, _______, _______, _______, _______, _______, _______, KC_UNDS, KC_LBRC, KC_RBRC, _______, _______, _______, _______,
        _______, _______, _______,                            _______,                                     _______, _______, _______
    ),
};
