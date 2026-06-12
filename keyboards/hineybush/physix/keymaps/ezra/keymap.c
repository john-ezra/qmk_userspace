#include QMK_KEYBOARD_H

enum layers {
    _COLEMAK,
    _FN,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_COLEMAK] = LAYOUT_split_bksp_275_rspace(
        QK_GESC, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_CAPS, KC_BSPC, KC_DEL,
        KC_TAB,  KC_Q,    KC_W,    KC_F,    KC_P,    KC_G,    KC_J,    KC_L,    KC_U,    KC_Y,    KC_SCLN, KC_LBRC, KC_RBRC, KC_BSLS,          KC_PGUP,
        KC_BSPC, KC_A,    KC_R,    KC_S,    KC_T,    KC_D,    KC_H,    KC_N,    KC_E,    KC_I,    KC_O,    KC_QUOT, KC_ENT,                    KC_PGDN,
        KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_RALT, KC_K,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,          KC_UP,
        KC_LCTL,          MO(_FN),                   KC_SPC,  KC_LGUI,          KC_SPC,  MO(_FN),          KC_RCTL,          KC_LEFT, KC_DOWN, KC_RGHT
    ),

    [_FN] = LAYOUT_split_bksp_275_rspace(
        QK_BOOT, UG_SATD, UG_SATU, UG_TOGG, UG_NEXT, _______, _______, _______, _______, BL_BRTG, BL_TOGG, BL_UP,   BL_DOWN, _______, _______, KC_INS,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          KC_HOME,
        _______, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, _______, _______, _______, _______, _______, _______, _______, _______,                   KC_END,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          UG_VALU,
        _______,          _______,                   _______, _______,          _______, _______,          _______,          UG_HUED, UG_VALD, UG_HUEU
    ),
};
