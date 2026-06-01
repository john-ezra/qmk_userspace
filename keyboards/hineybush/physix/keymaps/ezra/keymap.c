#include QMK_KEYBOARD_H

enum layers {
    _BASE,
    _FN,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BASE] = LAYOUT_split_bksp_275_rspace(
        QK_GESC, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_CAPS, KC_BSPC, KC_DEL,
        KC_TAB,  KC_Z,    KC_R,    KC_L,    KC_D,    KC_W,    KC_Y,    KC_P,    KC_U,    KC_X,    KC_Q,    KC_LBRC, KC_RBRC, KC_BSLS,          KC_PGUP,
        KC_BSPC, KC_H,    KC_N,    KC_T,    KC_S,    KC_C,    KC_B,    KC_I,    KC_E,    KC_O,    KC_A,    KC_QUOT, KC_ENT,                    KC_PGDN,
        KC_LSFT, KC_K,    KC_V,    KC_M,    KC_F,    KC_G,    KC_J,    KC_SCLN, KC_COMM, KC_DOT,  KC_SLSH, KC_RALT, KC_RSFT,          KC_UP,
        KC_LCTL,          KC_LGUI,                   KC_SPC,  MO(_FN),          KC_SPC,  KC_RGUI,          KC_RCTL,          KC_LEFT, KC_DOWN, KC_RGHT
    ),

    [_FN] = LAYOUT_split_bksp_275_rspace(
        QK_BOOT, UG_SATD, UG_SATU, UG_TOGG, UG_NEXT, _______, _______, _______, _______, BL_BRTG, BL_TOGG, BL_UP,   BL_DOWN, _______, _______, KC_INS,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          KC_HOME,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,                   KC_END,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          UG_VALU,
        _______,          _______,                   _______, _______,          _______, _______,          _______,          UG_HUED, UG_VALD, UG_HUEU
    ),
};
