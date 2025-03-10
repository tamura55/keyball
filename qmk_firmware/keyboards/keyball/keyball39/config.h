/*
Copyright 2022 @Yowkees
Copyright 2022 MURAOKA Taro (aka KoRoN, @kaoriya)

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

// Key matrix parameters
#define MATRIX_ROWS         (4 * 2)  // split keyboard
#define MATRIX_COLS         6
#define MATRIX_ROW_PINS     { F4, F5, F6, F7 }
#define MATRIX_COL_PINS     { D4, C6, D7, E6, B4, B5 }
#define MATRIX_MASKED
#define DEBOUNCE            5
#define DIODE_DIRECTION     COL2ROW

// Split parameters
#define SOFT_SERIAL_PIN         D2
#define SPLIT_HAND_MATRIX_GRID  F6, B5
#define SPLIT_USB_DETECT
#ifdef OLED_ENABLE
#    define SPLIT_OLED_ENABLE
#endif

// If your PC does not recognize Keyball, try setting this macro. This macro
// increases the firmware size by 200 bytes, so it is disabled by default, but
// it has been reported to work well in such cases.
//#define SPLIT_WATCHDOG_ENABLE

#define SPLIT_TRANSACTION_IDS_KB KEYBALL_GET_INFO, KEYBALL_GET_MOTION, KEYBALL_SET_CPI

// RGB LED settings
#define WS2812_DI_PIN       D3
#ifdef RGBLIGHT_ENABLE
#    define RGBLED_NUM      48
#    define RGBLED_SPLIT    { 24, 24 }  // (24 + 22)
// #    define RGBLIGHT_LAYERS  // LED範囲制御にあたり追加
// #    define SPLIT_LAYER_STATE_ENABLE  // LED範囲制御にあたり追加
#    ifndef RGBLIGHT_LIMIT_VAL
#        define RGBLIGHT_LIMIT_VAL  180 // 赤色不安定のため、200→180へ変更
#    endif
#    ifndef RGBLIGHT_VAL_STEP
#        define RGBLIGHT_VAL_STEP   15
#    endif
#    ifndef RGBLIGHT_HUE_STEP
#        define RGBLIGHT_HUE_STEP   17
#    endif
#    ifndef RGBLIGHT_SAT_STEP
#        define RGBLIGHT_SAT_STEP   17
#    endif
#endif

// RGB Matrix用
#ifdef RGB_MATRIX_ENABLE
#    define RGBLED_NUM         48       // LEDの総数
#    define RGB_MATRIX_LED_COUNT RGBLED_NUM  // 全体のLED数を指定
#    define RGB_MATRIX_SPLIT   { 24, 24 }  // 左右に分かれているLED数
#    define RGB_MATRIX_MAXIMUM_BRIGHTNESS 150  // RGBLIGHT_LIMIT_VALに対応
#    define RGB_MATRIX_VAL_STEP 15  // 明るさのステップ
#    define RGB_MATRIX_HUE_STEP 17  // 色相のステップ
#    define RGB_MATRIX_SAT_STEP 17  // 彩度のステップ
#    define RGB_DISABLE_WHEN_USB_SUSPENDED true  // USBサスペンド時にRGBをオフにする
#    define RGB_MATRIX_STARTUP_MODE RGB_MATRIX_SOLID_COLOR  // RGB Matrixの初期モードを設定（単色モード）
#endif

#ifndef OLED_FONT_H
#    define OLED_FONT_H "keyboards/keyball/lib/logofont/logofont.c"
#    define OLED_FONT_START 32
#    define OLED_FONT_END 195
#endif

#if !defined(LAYER_STATE_8BIT) && !defined(LAYER_STATE_16BIT) && !defined(LAYER_STATE_32BIT)
#    define LAYER_STATE_8BIT
#endif

// To squeeze firmware size
#undef LOCKING_SUPPORT_ENABLE
#undef LOCKING_RESYNC_ENABLE
