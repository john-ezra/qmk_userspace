// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#define TAPPING_TERM 150
#define HOLD_ON_OTHER_KEY_PRESS

// Boot with the underglow full white: saturation 0 makes white, and hue,
// brightness (the RGBLIGHT_LIMIT_VAL ceiling), mode, and on-state keep QMK's
// defaults. Only the first boot and an EEPROM reset read these.
#define RGBLIGHT_DEFAULT_SAT 0
