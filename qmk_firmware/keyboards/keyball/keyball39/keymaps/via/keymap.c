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
/*
  [0] = LAYOUT_universal(
    KC_Q     , KC_W     , KC_E     , KC_R     , KC_T     ,                            KC_Y     , KC_U     , KC_I     , KC_O     , KC_P     ,
    KC_A     , KC_S     , KC_D     , KC_F     , KC_G     ,                            KC_H     , KC_J     , KC_K     , KC_L     , KC_MINS  ,
    KC_Z     , KC_X     , KC_C     , KC_V     , KC_B     ,                            KC_N     , KC_M     , KC_COMM  , KC_DOT   , KC_SLSH  ,
    KC_LCTL  , KC_LGUI  , KC_LALT  ,LSFT_T(KC_LNG2),LT(1,KC_SPC),LT(3,KC_LNG1),KC_BSPC,LT(2,KC_ENT),LSFT_T(KC_LNG2),KC_RALT,KC_RGUI, KC_RSFT
  ),

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
//    uint8_t highest_layer = get_highest_layer(state);  // 一度だけ取得して変数に格納
    keyball_set_scroll_mode(get_highest_layer(state) == 3);  // Auto enable scroll mode when the highest layer is 3
#if KEYBALL_SCROLLSNAP_ENABLE == 2
    if (get_highest_layer(state) != 3) {
        keyball_set_scrollsnap_mode(KEYBALL_SCROLLSNAP_MODE_VERTICAL);  // レイヤー3以外ではSSNP_VRTに固定
    }
#endif

/*
////////// LEDトライ1。ここから //////////
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
            //rgblight_sethsv(HSV_OFF);
            for (int i = 30; i < 46; i++) {
                rgblight_sethsv_at(HSV_OFF, i);
            }
        } else {
            //rgblight_sethsv(HSV_OFF);
            for (int i = 0; i < 18; i++) {
                rgblight_sethsv_at(HSV_WHITE, i);
            }
        }
    }
////////// LEDトライ1。ここまで //////////

////////// LEDトライ2。ここから //////////
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
        oled_set_brightness(5);
    } else {
        rgblight_sethsv(HSV_OFF);
        oled_set_brightness(255);
    }
////////// LEDトライ2。ここまで //////////

///// RGB Matrixにて一部点灯トライ。ここから /////
    if (layer_state_cmp(state, 6)) {
        // Layer 6 の場合、青色に点灯させる
        for (int i = 0; i < RGBLED_NUM; i++) {
            if ((is_keyboard_master() && (i >= 0 && i <= 17)) || (!is_keyboard_master() && (i >= 30 && i <= 45))) {
                // 左側(マスター側)は0〜17、右側(スレーブ側)は30〜45を青色にする
                rgb_matrix_set_color(i, 0, 0, 255);  // 青色
            } else {
                // その他のLEDは消灯
                rgb_matrix_set_color(i, 0, 0, 0);
            }
        }
    } else {
        // Layer 6 以外はすべてのLEDをオフにする
        for (int i = 0; i < RGBLED_NUM; i++) {
            rgb_matrix_set_color(i, 0, 0, 0);
        }
    }
///// RGB Matrixにて一部点灯トライ。ここまで /////

////////// LEDトライ3。ここから //////////
    if (get_highest_layer(state) == 6) { // レイヤー6がアクティブな場合
        // 左側のLED0〜17と右側のLED30〜45を青色に設定
        rgblight_setrgb_range(0, 17, HSV_BLUE);  // 左側のLED0〜17を青色に設定
        rgblight_setrgb_range(30, 45, HSV_BLUE); // 右側のLED30〜45を青色に設定
        // その他のLEDをオフにする
        rgblight_setrgb_range(18, 29, RGB_OFF);  // 左側LED18〜23をオフ
        rgblight_setrgb_range(24, 29, RGB_OFF);  // 右側LED24〜29をオフ
        rgblight_setrgb_range(46, 47, RGB_OFF);  // 右側LED46以降をオフ（もしあれば）
    } else {
        // レイヤー6以外の場合、すべてのLEDをオフにする
        rgblight_setrgb_range(0, 47, RGB_OFF); // すべてのLEDをオフ
    }
////////// LEDトライ3。ここまで //////////
*/

    // レイヤーとLEDを連動させる
    if (get_highest_layer(state) == 6) {
        rgblight_sethsv(HSV_BLUE);
//        oled_set_brightness(5);  // OLEDの輝度を下げる
    } else {
        rgblight_sethsv(HSV_OFF);
//        oled_set_brightness(255);  // OLEDの輝度をデフォルト値に戻す
    }
    
    /*
    switch (get_highest_layer(state)) {
//        case 1:
//            rgblight_sethsv(HSV_BLUE);
//            oled_set_brightness(5);  // OLEDの輝度を下げる
//            break;
//        case 2:
//            rgblight_sethsv(HSV_RED);
//            oled_set_brightness(5);  // OLEDの輝度を下げる
//            break;
        case 6:
            rgblight_sethsv(HSV_BLUE);
//            oled_set_brightness(5);  // OLEDの輝度を下げる
            break;
        default:
            rgblight_sethsv(HSV_OFF);
//            oled_set_brightness(255);  // OLEDの輝度をデフォルト値に戻す
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

//////////////////////////////
/// カスタムキーコード。ここから ///
//////////////////////////////
#ifdef POINTING_DEVICE_AUTO_MOUSE_ENABLE
// フラグとタイマーを初期化。AML_ENT1用
static bool pressed_other_key_ent = false;
static uint16_t aml_ent1_timer;
// AML_TAB2用
static bool pressed_other_key_tab = false;
static uint16_t aml_tab2_timer;

// Combo Termを50msに設定
#define CUSTOM_COMBO_TERM 50
// キー押下状態を記録するフラグ。コンボ1(C+V→Esc)用
bool is_c_pressed = false;
bool is_v_pressed = false;
uint16_t c_pressed_time = 0;
uint16_t v_pressed_time = 0;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case AML_ENT1:
            if (record->event.pressed) {
                // AML_ENT1が押された瞬間
                pressed_other_key_ent = false;         // 他のキーが押されるまでフラグをリセット
                aml_ent1_timer = timer_read();         // タイマーをスタート
                layer_off(AUTO_MOUSE_DEFAULT_LAYER);   // Auto Mouse Layerを無効化
                layer_on(1);                           // Layer1を有効化
            } else {
                // AML_ENT1が離された瞬間
                // 他のキーが押されていない場合
                if (!pressed_other_key_ent) {
                    // Tapping Term以内にリリースされた場合のみEnterを送信
                    if (timer_elapsed(aml_ent1_timer) < TAPPING_TERM) {
                        tap_code(KC_ENT);              // Enterキーを送信
                    }
                    // Tapping Termを超えている場合は何もしない
                }
                layer_off(1);                          // Layer1を無効化
                layer_clear();                         // Layer0に戻る
            }
            return false;  // AML_ENT1に対して他の処理は行わない

        case AML_TAB2:
            if (record->event.pressed) {
                // AML_TAB2が押された瞬間
                pressed_other_key_tab = false;         // 他のキーが押されるまでフラグをリセット
                aml_tab2_timer = timer_read();         // タイマーをスタート
                layer_off(AUTO_MOUSE_DEFAULT_LAYER);   // Auto Mouse Layerを無効化
                layer_on(2);                           // Layer2を有効化
            } else {
                // AML_TAB2が離された瞬間
                // 他のキーが押されていない場合
                if (!pressed_other_key_tab) {
                    // Tapping Term以内にリリースされた場合のみTabを送信
                    if (timer_elapsed(aml_tab2_timer) < TAPPING_TERM) {
                        tap_code(KC_TAB);              // Tabキーを送信
                    }
                    // Tapping Termを超えている場合は何もしない
                }
                layer_off(2);                          // Layer2を無効化
                layer_clear();                         // Layer0に戻る
            }
            return false;  // AML_TAB2に対して他の処理は行わない

        case EXL_FLT:
            if (record->event.pressed) {
                register_code(KC_LALT);
                unregister_code(KC_LALT);
                tap_code(KC_W);
                tap_code(KC_F);
                tap_code(KC_F);
                tap_code(KC_UP);
                register_code(KC_LSFT);
                tap_code(KC_SPC);
                unregister_code(KC_LSFT);
                register_code(KC_LALT);
                unregister_code(KC_LALT);
                tap_code(KC_A);
                tap_code(KC_T);
                tap_code(KC_DOWN);
                tap_code(KC_UP);
            }
            return false;
            
///// コンボ1(C+V→Esc)。ここから /////
        case KC_C:
            if (record->event.pressed) {  // Cが押された
                is_c_pressed = true;
                c_pressed_time = timer_read();
                if (is_v_pressed && timer_elapsed(v_pressed_time) < CUSTOM_COMBO_TERM) {
                    // Vも押されていて、50ms以内ならESCを送信
                    tap_code(KC_ESC);
                    is_c_pressed = is_v_pressed = false;  // フラグのリセット
                    c_pressed_time = v_pressed_time = 0;  // タイマーのリセット
                    return false;  // CとVの入力をキャンセル
                }
            } else {  // Cが離された
                is_c_pressed = false;  // フラグのリセット
                c_pressed_time = 0;    // タイマーをリセット
            }
            return true;
        case KC_V:
            if (record->event.pressed) {
                is_v_pressed = true;
                v_pressed_time = timer_read();
                if (is_c_pressed && timer_elapsed(c_pressed_time) < CUSTOM_COMBO_TERM) {
                    // Cも押されていて、50ms以内ならESCを送信
                    tap_code(KC_ESC);
                    is_c_pressed = is_v_pressed = false;  // フラグのリセット
                    c_pressed_time = v_pressed_time = 0;  // タイマーのリセット
                    return false;  // CとVの入力をキャンセル
                }
            } else {
                is_v_pressed = false;  // フラグのリセット
                v_pressed_time = 0;    // タイマーをリセット
            }
            return true;
///// コンボ1(C+V→Esc)。ここまで /////

        default:
            // 他のキーが押された場合にフラグを立てる
            if (record->event.pressed) {
                if (layer_state_is(1)) {
                    pressed_other_key_ent = true;  // Layer1で他のキーが押されたことを記録
                }
                if (layer_state_is(2)) {
                    pressed_other_key_tab = true;  // Layer2で他のキーが押されたことを記録
                }
            }
            return true;  // 通常のキー処理を続ける
    }
}
#endif
//////////////////////////////
/// カスタムキーコード。ここまで ///
//////////////////////////////