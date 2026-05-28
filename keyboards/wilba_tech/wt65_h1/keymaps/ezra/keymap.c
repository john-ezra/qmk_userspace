#include QMK_KEYBOARD_H

enum layers {
    _BASE,
    _FN,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BASE] = LAYOUT_65_ansi_blocker_tsangan(
        QK_GESC, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_CAPS,          KC_DEL,
        KC_TAB,  KC_Z,    KC_R,    KC_L,    KC_D,    KC_W,    KC_Y,    KC_P,    KC_U,    KC_X,    KC_Q,    KC_LBRC, KC_RBRC, KC_BSLS,          KC_PGUP,
        KC_BSPC, KC_H,    KC_N,    KC_T,    KC_S,    KC_C,    KC_B,    KC_I,    KC_E,    KC_O,    KC_A,    KC_QUOT, KC_ENT,                    KC_PGDN,
        KC_LSFT, KC_K,    KC_V,    KC_M,    KC_F,    KC_G,    KC_J,    KC_SCLN, KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,                   KC_UP,   MO(_FN),
        KC_LCTL, KC_LGUI, KC_LALT,                            KC_SPC,                                      KC_RGUI,          KC_LEFT, KC_DOWN, KC_RGHT
    ),

    [_FN] = LAYOUT_65_ansi_blocker_tsangan(
        QK_BOOT, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  _______,          KC_INS,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          KC_HOME,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,                   KC_END,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,                   _______, _______,
        _______, _______, _______,                            _______,                                     _______,          _______, _______, _______
    ),
};
