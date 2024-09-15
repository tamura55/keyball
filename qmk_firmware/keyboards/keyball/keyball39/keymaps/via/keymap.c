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

#include QMK_KEYBOARD_H

#include "quantum.h"

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  // keymap for default (VIA)
  [0] = LAYOUT_universal(
    KC_Q     , KC_W     , KC_E     , KC_R     , KC_T     ,                            KC_Y     , KC_U     , KC_I     , KC_O     , KC_P     ,
    KC_A     , KC_S     , KC_D     , KC_F     , KC_G     ,                            KC_H     , KC_J     , KC_K     , KC_L     , KC_MINS  ,
    KC_Z     , KC_X     , KC_C     , KC_V     , KC_B     ,                            KC_N     , KC_M     , KC_COMM  , KC_DOT   , KC_SLSH  ,
    KC_LCTL  , KC_LGUI  , KC_LALT  ,LSFT_T(KC_LNG2),LT(1,KC_SPC),LT(3,KC_LNG1),KC_BSPC,LT(2,KC_ENT),LSFT_T(KC_LNG2),KC_RALT,KC_RGUI, KC_RSFT
  ),

/*
  [1] = LAYOUT_universal(
    KC_F1    , KC_F2    , KC_F3    , KC_F4    , KC_RBRC  ,                            KC_F6    , KC_F7    , KC_F8    , KC_F9    , KC_F10   ,
    KC_F5    , KC_EXLM  , S(KC_6)  ,S(KC_INT3), S(KC_8)  ,                           S(KC_INT1), KC_BTN1  , KC_PGUP  , KC_BTN2  , KC_SCLN  ,
    S(KC_EQL),S(KC_LBRC),S(KC_7)   , S(KC_2)  ,S(KC_RBRC),                            KC_LBRC  , KC_DLR   , KC_PGDN  , KC_BTN3  , KC_F11   ,
    KC_INT1  , KC_EQL   , S(KC_3)  , _______  , _______  , _______  ,      TO(2)    , TO(0)    , _______  , KC_RALT  , KC_RGUI  , KC_F12
  ),

  [2] = LAYOUT_universal(
    KC_TAB   , KC_7     , KC_8     , KC_9     , KC_MINS  ,                            KC_NUHS  , _______  , KC_BTN3  , _______  , KC_BSPC  ,
   S(KC_QUOT), KC_4     , KC_5     , KC_6     ,S(KC_SCLN),                            S(KC_9)  , KC_BTN1  , KC_UP    , KC_BTN2  , KC_QUOT  ,
    KC_SLSH  , KC_1     , KC_2     , KC_3     ,S(KC_MINS),                           S(KC_NUHS), KC_LEFT  , KC_DOWN  , KC_RGHT  , _______  ,
    KC_ESC   , KC_0     , KC_DOT   , KC_DEL   , KC_ENT   , KC_BSPC  ,      _______  , _______  , _______  , _______  , _______  , _______
  ),

  [3] = LAYOUT_universal(
    RGB_TOG  , AML_TO   , AML_I50  , AML_D50  , _______  ,                            _______  , _______  , SSNP_HOR , SSNP_VRT , SSNP_FRE ,
    RGB_MOD  , RGB_HUI  , RGB_SAI  , RGB_VAI  , SCRL_DVI ,                            _______  , _______  , _______  , _______  , _______  ,
    RGB_RMOD , RGB_HUD  , RGB_SAD  , RGB_VAD  , SCRL_DVD ,                            CPI_D1K  , CPI_D100 , CPI_I100 , CPI_I1K  , KBC_SAVE ,
    QK_BOOT  , KBC_RST  , _______  , _______  , _______  , _______  ,      _______  , _______  , _______  , _______  , KBC_RST  , QK_BOOT
  ),
*/

};
// clang-format on

layer_state_t layer_state_set_user(layer_state_t state) {
    uint8_t highest_layer = get_highest_layer(state);  // 一度だけ取得して変数に格納
    keyball_set_scroll_mode(highest_layer == 3);  // Auto enable scroll mode when the highest layer is 3
#if KEYBALL_SCROLLSNAP_ENABLE == 2
    if (highest_layer != 3) {
        keyball_set_scrollsnap_mode(KEYBALL_SCROLLSNAP_MODE_VERTICAL);  // レイヤー3以外ではSSNP_VRTに固定
    }
#endif

////////// トライアル //////////
//    if (highest_layer == 6) {
        // 左右のLED範囲を設定する
        if (is_keyboard_master()) {
            // マスター側 (右半分)
            for (int i = 30; i < 46; i++) {
                rgblight_sethsv_at(HSV_WHITE, i);
            }
        } else {
            // スレーブ側 (左半分)
            for (int i = 0; i < 18; i++) {
                rgblight_sethsv_at(HSV_WHITE, i);
            }
        }
    if (get_highest_layer(state) == 1) {
        if (is_keyboard_master()) {
            rgblight_sethsv(HSV_OFF);
        } else {
            rgblight_sethsv(HSV_OFF);
        }
    }
//    } else if (highest_layer == 1) {
//        rgblight_sethsv(HSV_GREEN);
//    } else {
//        rgblight_sethsv(HSV_OFF);
//        oled_set_brightness(255);
//    }
////////// トライアル //////////


/* トライアルにつきコメントアウト。ここから。
    // レイヤーとLEDを連動させる
    if (highest_layer == 6) {
        // 左右のLED範囲を設定する
        if (is_keyboard_master()) {
            // マスター側 (右半分)
            for (int i = 30; i < 46; i++) {
                rgblight_sethsv_at(HSV_WHITE, i);
            }
        } else {
            // スレーブ側 (左半分)
            for (int i = 0; i < 18; i++) {
                rgblight_sethsv_at(HSV_WHITE, i);
            }
        }
        
//        if (is_keyboard_left()) {
//            rgblight_sethsv_range(HSV_WHITE, 0, 18);  // 左側のLED
//        } else {
//            rgblight_sethsv_range(HSV_WHITE, 30, 46);  // 右側のLED
//        }
        //rgblight_sethsv_range(HSV_WHITE, 4, 40);
        oled_set_brightness(5);
    } else {
        rgblight_sethsv(HSV_OFF);
        oled_set_brightness(255);
    }
トライアルにつきコメントアウト。ここから。 */
    
//    bool kb_master = is_keyboard_master();  // 一度だけ取得して変数に格納
/*
    switch (highest_layer) {
        case 1:
            rgblight_sethsv(HSV_GREEN);
            break;
        case 2:
            rgblight_sethsv(HSV_BLUE);
            break;
        case 3:
            rgblight_sethsv(HSV_RED);
            if (is_keyboard_master()) {
                oled_set_brightness(5);  // マスター側のOLEDの輝度
            } else {
                oled_set_brightness(5);  // スレーブ側のOLEDの輝度
            }
            break;
        case 6:
//            rgblight_sethsv(HSV_WHITE);
            
            rgblight_disable();  // 全LEDをオフにする
            // 左右のLED範囲を設定する
            if (is_keyboard_master()) {
                // マスター側のLED（右側）
                set_led_range_red(7, 22);
            } else {
                // スレーブ側のLED（左側）
                set_led_range_red(1, 18);
            }
            rgblight_enable();  // RGBライトを有効にする
            
            oled_set_brightness(5);  // OLEDの輝度を下げる
            break;
        default:
            rgblight_sethsv(HSV_OFF);
            if (is_keyboard_master()) {
                oled_set_brightness(255);  // マスター側のOLEDの輝度
            } else {
                oled_set_brightness(255);  // スレーブ側のOLEDの輝度
            }
    }
*/

    // negokazさん追記部
#ifdef POINTING_DEVICE_AUTO_MOUSE_ENABLE
    keyball_handle_auto_mouse_layer_change(state);
#endif

    return state;
}

#ifdef OLED_ENABLE
#    include "lib/oledkit/oledkit.h"
void oledkit_render_info_user(void) {
    keyball_oled_render_keyinfo();
    keyball_oled_render_ballinfo();
    keyball_oled_render_layerinfo();
}
#endif

// Retro Tappingを有効化するキーを定義
/*
bool get_retro_tapping(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case LSFT_T(KC_GRV):  // 親指キー_old
        case LT(1, KC_SPC):  // 親指キー_old
        case LT(1, KC_GRV):  // 親指キー_new
        case LT(2, KC_ESC):  // 親指キー
        case LT(2, KC_ENT):  // 親指キー
        case LT(1, KC_TAB):  // 親指キー
        case LCTL_T(KC_MINS):  // 小指付け根キー
        // キーマップ刷新
        case LCTL_T(KC_GRV):  // 親指キー
        case LSFT_T(KC_SPC):  // 親指キー
        case C_S_T(KC_ESC):  // 親指キー
        case LT(2,KC_TAB):  // 親指キー
        case LT(1,KC_ENT):  // 親指キー
        case LALT_T(KC_ESC):  // 親指キー予備
        case LALT_T(KC_MINS):  // 小指付け根キー
            return true;
        default:
            return false;
    }
}
*/

// nested tapが苦手なキーにのみHold On Other Key Pressを適用
bool get_hold_on_other_key_press(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case LCTL_T(KC_GRV):  // 親指キー
        case LSFT_T(KC_SPC):  // 親指キー
        case C_S_T(KC_ESC):  // 親指キー
        case LT(2,KC_TAB):  // 親指キー
        case LT(1,KC_ENT):  // 親指キー
        case LALT_T(KC_MINS):  // 小指付け根キー
        case RCTL_T(KC_GRV):  // AML専用左親指キー
        case RSFT_T(KC_SPC):  // AML専用左親指キー
        case RCS_T(KC_ESC):  // AML専用左親指キー
        case AML_ENT1:  // AML専用右親指キー
        case AML_TAB2:  // AML専用右親指キー
            // Immediately select the hold action when another key is pressed.
            return true;
        default:
            // Do not select the hold action when another key is pressed.
            return false;
    }
}
