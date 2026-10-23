// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#define TAPPING_TERM 150
#define HOLD_ON_OTHER_KEY_PRESS

// Boot with the underglow full white: saturation 0 makes white, and hue,
// brightness (the RGBLIGHT_LIMIT_VAL ceiling), mode, and on-state keep QMK's
// defaults. Only the first boot and an EEPROM reset read these.
#define RGBLIGHT_DEFAULT_SAT 0

// The h60 definition compiles in every RGBLIGHT animation family. Keep only
// static gradient and rainbow swirl. This file is included after the header
// generated from the keyboard definition, so these undefs remove the other
// families before the lighting code sees them.
#undef RGBLIGHT_EFFECT_ALTERNATING
#undef RGBLIGHT_EFFECT_BREATHING
#undef RGBLIGHT_EFFECT_CHRISTMAS
#undef RGBLIGHT_EFFECT_KNIGHT
#undef RGBLIGHT_EFFECT_RAINBOW_MOOD
#undef RGBLIGHT_EFFECT_RGB_TEST
#undef RGBLIGHT_EFFECT_SNAKE
#undef RGBLIGHT_EFFECT_TWINKLE
