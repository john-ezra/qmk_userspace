#include "keycodes.h"
#include "quantum_keycodes.h"
#include QMK_KEYBOARD_H

enum layers {
    _COLEMAK,
    _FN,
    _ADJUST,
};


#define TG_ADJ TG(_ADJUST)
#define SUP_ESC LGUI_T(KC_ESC)
#define SUP_ENT LGUI_T(KC_ENT)

// Keep the keymap in visual TypeK order while feeding QMK's matrix-ordered LAYOUT_all.
#define LAYOUT_typek_visual( \
    k00, k01, k02, k03, k04, k05, k06, k46, k07, k08, k09, k0A, k0B, k0C, k0D, k2D, \
    k10, k11, k12, k13, k14, k15, k16,      k17, k18, k19, k1A, k1B, k1C, k1D, k4A, \
    k20, k21, k22, k23, k24, k25, k26,      k27, k28, k29, k2A, k2B, k2C,      k4B, \
    k30,      k31, k32, k33, k34, k35, k36, k37, k38, k39, k3A, k3B, k3C, k3D, k4C, \
         k41, k42,      k44, k45,                k47, k48, k49,                k4D  \
) \
    LAYOUT_all( \
        k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0A, k0B, k0C, k0D, \
        k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1A, k1B, k1C, k1D, \
        k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2A, k2B, k2C, k2D, \
        k30, k31, k32, k33, k34, k35, k36, k37, k38, k39, k3A, k3B, k3C, k3D, \
             k41, k42,      k44, k45, k46, k47, k48, k49, k4A, k4B, k4C,   k4D \
    )

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_COLEMAK] = LAYOUT_typek_visual(
        KC_ESC,  KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSLS, KC_DEL,
        KC_PGUP, KC_TAB,  KC_Q,    KC_W,    KC_F,    KC_P,    KC_G,             KC_J,    KC_L,    KC_U,    KC_Y,    KC_SCLN, KC_LBRC, KC_RBRC, KC_BSPC,
        KC_PGDN, KC_ESC,  KC_A,    KC_R,    KC_S,    KC_T,    KC_D,             KC_H,    KC_N,    KC_E,    KC_I,    KC_O,    KC_QUOT,          KC_ENT,
        TG_ADJ,  KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,             KC_B,    KC_K,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT, KC_RALT,
                 KC_LCTL,          MO(_FN), KC_SPC,  KC_LGUI,                   KC_RGUI, KC_SPC,  MO(_FN),                            KC_RCTL
    ),

    [_FN] = LAYOUT_typek_visual(
        _______, KC_GRV,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_INS,  _______,
        _______, _______, KC_HOME, KC_PGDN, KC_PGUP, KC_END,  _______,          KC_TILD, KC_LCBR, KC_RCBR, _______, _______, _______, _______, _______,
        _______, _______, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, _______,          KC_MINS, KC_LPRN, KC_RPRN, _______, _______, _______,          _______,
        _______, _______, _______, _______, _______, _______, _______,          _______, KC_UNDS, KC_LBRC, KC_RBRC, _______, _______, _______, _______,
                 _______, _______,          _______, _______,                   _______, _______, _______,                            _______
    ),

    [_ADJUST] = LAYOUT_typek_visual(
        QK_BOOT, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______,          UG_TOGG, UG_HUEU, UG_SATU, UG_VALU, UG_SPDU, UG_NEXT, _______, _______,
        _______, _______, _______, _______, _______, _______, _______,          _______, UG_HUED, UG_SATD, UG_VALD, UG_SPDD, UG_PREV,          _______,
        TG_ADJ,  _______, _______, _______, _______, _______, _______,          _______, _______, _______, _______, _______, _______, _______, _______,
                 _______, _______,          _______, _______,                   _______, _______, _______,                            _______
    ),
};

