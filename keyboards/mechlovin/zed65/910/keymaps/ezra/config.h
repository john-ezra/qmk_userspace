// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

// The Polycarbonate Rev2 retains the Rev1 hardware definition but has its own USB identity and underglow chain.
#undef PRODUCT_ID
#define PRODUCT_ID 0x6506

#undef PRODUCT
#define PRODUCT "Zed65 910 Rev2"

#undef RGBLIGHT_LED_COUNT
#define RGBLIGHT_LED_COUNT 28
