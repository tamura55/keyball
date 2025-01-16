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

#ifdef RGBLIGHT_ENABLE
bool cw_active = false;  // Caps Word用フラグ

void caps_word_set_user(bool active) {
    if (active) {  // Caps Wordが有効な場合
        rgblight_sethsv(HSV_RED);
        cw_active = true;
    } else {
        if (layer_state_is(6)) {
            rgblight_sethsv(HSV_GREEN);
        } else if (layer_state_is(5)) {
            rgblight_sethsv(HSV_BLUE);
        } else {
            rgblight_sethsv(HSV_OFF); // それ以外の場合、LEDを消灯
        }
        cw_active = false;
    }
}
#endif

layer_state_t layer_state_set_user(layer_state_t state) {
    uint8_t highest_layer = get_highest_layer(state);  // 一度だけ取得して変数に格納
//    keyball_set_scroll_mode(highest_layer == 3);  // Auto enable scroll mode when the highest layer is 3
#if KEYBALL_SCROLLSNAP_ENABLE == 2
    if (highest_layer != 6) {
        keyball_set_scrollsnap_mode(KEYBALL_SCROLLSNAP_MODE_VERTICAL);  // レイヤー6以外ではSSNP_VRTに固定
    }
#endif

#ifdef RGBLIGHT_ENABLE
    // レイヤーとLEDを連動させる
    switch (highest_layer) {
        case 5:
            rgblight_sethsv(HSV_BLUE);
//            oled_set_brightness(5);  // OLEDの輝度を下げる
            break;
        case 6:
            rgblight_sethsv(HSV_GREEN);
//            oled_set_brightness(5);  // OLEDの輝度を下げる
            break;
        default:
//#if KEYBALL_SCROLLSNAP_ENABLE == 2
//            keyball_set_scrollsnap_mode(KEYBALL_SCROLLSNAP_MODE_VERTICAL);  // レイヤー5,6以外ではSSNP_VRTに固定
//#endif
            if (cw_active) {
                rgblight_sethsv(HSV_RED); // レイヤー5,6以外かつCaps Wordが有効な場合
//                oled_set_brightness(5);  // OLEDの輝度を下げる
            } else {
                rgblight_sethsv(HSV_OFF);
//                oled_set_brightness(255);  // OLEDの輝度をデフォルト値に戻す
            }
    }
#endif
    
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

/*
// Retro Tappingを有効化するキーを定義
bool get_retro_tapping(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case LCTL_T(KC_GRV):  // 親指キー
        case LSFT_T(KC_SPC):  // 親指キー
        case C_S_T(KC_ESC):  // 親指キー
        case LT(2,KC_TAB):  // 親指キー
        case LT(1,KC_ENT):  // 親指キー
        case LALT_T(KC_MINS):  // 小指付け根キー
            return true;
        default:
            return false;
    }
}

// nested tapが苦手なキーにのみHold On Other Key Pressを適用
bool get_hold_on_other_key_press(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case THM_LL:
        case THM_LC:
        case THM_LR:
        case THM_RL:
        case THM_RR:
        case AML_LL:
        case AML_LC:
        case AML_LR:
        case LIL_L:
        case LIL_R:
        case AML_ENT1:  // AML専用右親指キー
        case AML_TAB2:  // AML専用右親指キー
            // Immediately select the hold action when another key is pressed.
            return true;
        default:
            // Do not select the hold action when another key is pressed.
            return false;
    }
}
*/

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
// TO6_MO3用
//static bool pressed_other_key_mo3 = false;
//static uint16_t to6_mo3_timer;

// Tap Dance用フラグ
//static bool first_td_ime3_pressed = false;
//static uint16_t first_td_ime3_pressed_time = 0;
//static bool td_ime3_pressed = false;  // 押されたかどうかを確認。ただし他のキーを押したらリセットされる

/* 擬似コンボ用
// Combo Termを50msに設定
#define CUSTOM_COMBO_TERM 50
// キー押下状態を記録するフラグ。コンボ1(Q+W→Esc)用
bool is_q_pressed = false;
bool is_w_pressed = false;
uint16_t q_pressed_time = 0;
uint16_t w_pressed_time = 0;
// コンボが成立したかを追跡
bool combo_executed = false;
// コンボ状態をリセット
void reset_combo_state(void) {
    is_q_pressed = is_w_pressed = false;
    q_pressed_time = w_pressed_time = 0;
}
*/

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    // 新しいキーが押されたら combo_executed をリセット
//    if (record->event.pressed) {
//        combo_executed = false;
//    }
    
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
                tap_code(KC_INT5);    // 無変換キー(IMEオフ)
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

        case MHEN_CW:
            if (record->event.pressed) {
                tap_code(KC_INT5);    // 無変換キー(IMEオフ)
                caps_word_on();         // Caps Wordを有効化
            }
            return false;
/*
        case TO6_MO3:
            if (record->event.pressed) {
                pressed_other_key_mo3 = false;         // 他のキーが押されるまでフラグをリセット
                to6_mo3_timer = timer_read();          // タイマーをスタート
                layer_on(3);                           // Layer3を有効化
            } else {
                // 他のキーが押されていない場合
                if (!pressed_other_key_mo3) {
                    // Tapping Term以内にリリースされた場合
                    if (timer_elapsed(to6_mo3_timer) < TAPPING_TERM) {
                        layer_off(3);                  // Layer3を無効化
                        layer_on(6);                   // Layer6を有効化
                    }  // Tapping Termを超えている場合
                    else {
                        layer_off(3);                  // Layer3を無効化
                    }
                } // 他のキーが押された場合
                else {
                    layer_off(3);                      // Layer3を無効化
                }
            }
            return false;
*/
      case TMS_MTG:
            if (record->event.pressed) {
                register_code(KC_LWIN);
                wait_ms(300);
                tap_code(KC_4);
                wait_ms(300);
                tap_code(KC_4);
                unregister_code(KC_LWIN);
                wait_ms(300);
                register_code(KC_LCTL);
                register_code(KC_LSFT);
                tap_code(KC_M);
                unregister_code(KC_LSFT);
                unregister_code(KC_LCTL);
            }
            return false;
/*
        case TD_IME3:
            if (record->event.pressed) {
                if (!first_td_ime3_pressed) {
                    first_td_ime3_pressed_time = record->event.time;
                // 一回目のタップのフラグがオン & 最初のキー押下から2回目のキー押下までの時間が TAPPING_TERM の2倍超なら
                // 間隔を空けた2回目のタップと判断する
                } else if (first_td_ime3_pressed && (TIMER_DIFF_16(record->event.time, first_td_ime3_pressed_time) > TAPPING_TERM * 2)) {
                    first_td_ime3_pressed_time = record->event.time;
                    first_td_ime3_pressed = false;
                }
                layer_on(3);
                td_ime3_pressed = true;  // 押されたのでフラグON
            } else {
                layer_off(3);
                // タップのフラグがオフ & 最初のキー押下からキーを離した時までの時間が TAPPING_TERM 未満なら
                // タップと判断する
                if (!first_td_ime3_pressed && td_ime3_pressed && (TIMER_DIFF_16(record->event.time, first_td_ime3_pressed_time) < TAPPING_TERM)) {
                    tap_code(KC_INT4);    // 変換キーを送信
                    first_td_ime3_pressed = true;
                // タップのフラグがオン & 最初のキー押下から2回目のタイプでキーを離した時までの時間が TAPPING_TERM の2倍以下なら
                // ダブルタップと判断する
                } else if (first_td_ime3_pressed && td_ime3_pressed && (TIMER_DIFF_16(record->event.time, first_td_ime3_pressed_time) <= TAPPING_TERM * 2)) {
                    tap_code(KC_INT5);    // 無変換キーを送信
                    first_td_ime3_pressed = false;
                } else {
                    first_td_ime3_pressed = false;
                }
                td_ime3_pressed = false;  // 離したのでリセット
            }
            return false;
*/
/*
///// コンボ1。ここから /////
        case KC_Q:
            if (record->event.pressed) {
                is_q_pressed = true;
                q_pressed_time = timer_read();
                // Wが既に押されていて、50ms以内ならコンボ成立
                if (is_w_pressed && timer_elapsed(w_pressed_time) < CUSTOM_COMBO_TERM) {
                    tap_code(KC_ESC);
                    combo_executed = true;  // コンボが成立したことを記録
                    reset_combo_state();     // combo_executed はリセットされない
                    return false;  // QとWの入力をキャンセル
                }
                return false;  // 一旦Qの入力をキャンセル
            } else {
                // コンボが実行された場合はリリース時の処理をスキップ
                if (!combo_executed) {
                    // Wが50ms以内に押されていない場合のみQを送信
                    if (!is_w_pressed || timer_elapsed(w_pressed_time) >= CUSTOM_COMBO_TERM) {
                        tap_code(KC_Q);  // リリース時にQを送信
                    }
                }
                is_q_pressed = false;
                q_pressed_time = 0;
            }
            return false;

        case KC_W:
            if (record->event.pressed) {
                is_w_pressed = true;
                w_pressed_time = timer_read();
                // Qが既に押されていて、50ms以内ならコンボ成立
                if (is_q_pressed && timer_elapsed(q_pressed_time) < CUSTOM_COMBO_TERM) {
                    tap_code(KC_ESC);
                    combo_executed = true;  // コンボが成立したことを記録
                    reset_combo_state();     // combo_executed はリセットされない
                    return false;  // QとWの入力をキャンセル
                }
                return false;  // 一旦Wの入力をキャンセル
            } else {
                // コンボが実行された場合はリリース時の処理をスキップ
                if (!combo_executed) {
                    // Qが50ms以内に押されていない場合のみWを送信
                    if (!is_q_pressed || timer_elapsed(q_pressed_time) >= CUSTOM_COMBO_TERM) {
                        tap_code(KC_W);  // リリース時にWを送信
                    }
                }
                is_w_pressed = false;
                w_pressed_time = 0;
            }
            return false;
///// コンボ1。ここまで /////
*/
        default:
            // 他のキーが押された場合にフラグを立てる
            if (record->event.pressed) {
                if (layer_state_is(1)) {
                    pressed_other_key_ent = true;  // Layer1で他のキーが押されたことを記録
                }
                if (layer_state_is(2)) {
                    pressed_other_key_tab = true;  // Layer2で他のキーが押されたことを記録
                }
//                if (layer_state_is(3)) {
//                    pressed_other_key_mo3 = true;  // Layer3で他のキーが押されたことを記録
//                }
//                first_td_ime3_pressed = false;  // フラグをリセット
//                td_ime3_pressed = false;  // 他のキーを押したらリセットすることでタップ入力させない
            }
            return true;  // 通常のキー処理を続ける
    }
}
#endif
//////////////////////////////
/// カスタムキーコード。ここまで ///
//////////////////////////////

#ifdef COMBO_ENABLE
enum combo_events {
  PARENTHESES,
  SQUARE_BRACKETS,
  CURLY_BRACKETS,
  ANGLE_BRACKETS,
  MAIL_CONFIRMED,
  APPLICATION,
  PASTE_SELECT,
};

const uint16_t PROGMEM paren_combo[] = {KC_F, KC_J, COMBO_END};
const uint16_t PROGMEM sqbra_combo[] = {KC_D, KC_K, COMBO_END};
const uint16_t PROGMEM cubra_combo[] = {KC_S, KC_L, COMBO_END};
const uint16_t PROGMEM anbra_combo[] = {KC_A, KC_BSPC, COMBO_END};
const uint16_t PROGMEM mail_combo[] = {KC_G, KC_H, COMBO_END};
const uint16_t PROGMEM app_combo[] = {KC_B, KC_N, COMBO_END};
const uint16_t PROGMEM paste_combo[] = {KC_V, KC_M, COMBO_END};

combo_t key_combos[] = {
  [PARENTHESES] = COMBO_ACTION(paren_combo),
  [SQUARE_BRACKETS] = COMBO_ACTION(sqbra_combo),
  [CURLY_BRACKETS] = COMBO_ACTION(cubra_combo),
  [ANGLE_BRACKETS] = COMBO_ACTION(anbra_combo),
  [MAIL_CONFIRMED] = COMBO_ACTION(mail_combo),
  [APPLICATION] = COMBO_ACTION(app_combo),
  [PASTE_SELECT] = COMBO_ACTION(paste_combo),
};
/* COMBO_ACTION(x) is same as COMBO(x, KC_NO) */

void process_combo_event(uint16_t combo_index, bool pressed) {
  switch(combo_index) {
    case PARENTHESES:
      if (pressed) {
        register_code(KC_LSFT);
        tap_code(KC_8);
        tap_code(KC_9);
        unregister_code(KC_LSFT);
      }
    break;
    case SQUARE_BRACKETS:
      if (pressed) {
        tap_code(KC_RBRC);
        tap_code(KC_BSLS);
      }
    break;
    case CURLY_BRACKETS:
      if (pressed) {
        register_code(KC_LSFT);
        tap_code(KC_RBRC);
        tap_code(KC_BSLS);
        unregister_code(KC_LSFT);
      }
    break;
    case ANGLE_BRACKETS:
      if (pressed) {
        register_code(KC_LSFT);
        tap_code(KC_COMMA);
        tap_code(KC_DOT);
        unregister_code(KC_LSFT);
      }
    break;
    case MAIL_CONFIRMED:
      if (pressed) {
        register_code(KC_LCTL);
        register_code(KC_LSFT);
        tap_code(KC_9);
        unregister_code(KC_LSFT);
        unregister_code(KC_LCTL);
      }
    break;
    case APPLICATION:
      if (pressed) {
        register_code(KC_LSFT);
        tap_code(KC_F10);
        unregister_code(KC_LSFT);
      }
    break;
    case PASTE_SELECT:
      if (pressed) {
        register_code(KC_LCTL);
        register_code(KC_LALT);
        tap_code(KC_V);
        unregister_code(KC_LALT);
        unregister_code(KC_LCTL);
      }
    break;
  }
}
#endif
