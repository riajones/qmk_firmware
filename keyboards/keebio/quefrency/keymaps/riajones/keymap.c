/* Copyright 2022 Riley Jones <riajones88@gmail.com> @riajones
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include QMK_KEYBOARD_H
#include "riajones.h"
#include "tapdance.c"
#include "macros.c"

#define TG_NORM TG(NORM)

extern keymap_config_t keymap_config;

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [BASE] = LAYOUT_65_with_macro(
    SS_LINU, QK_GESC, KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC, KC_BSPC, PLAY,
    KC_F1,   KC_F2,   KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS, KC_DEL,
    KC_F3,   KC_F4,   TD_CMOU, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_ENT,  KC_HOME,
    KC_F5,   KC_F6,   KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT, KC_UP,   KC_END,
    KC_F7,   KC_F8,   KC_LCTL, KC_LGUI, KC_LALT, CU_MED_MOU,KC_SPC,         _______, KC_ENT,  MO(MDIA),MO(MOUS),CTL_APP, KC_LEFT, KC_DOWN, KC_RGHT
  ),

  [MDIA] = LAYOUT_65_with_macro(
    TG_NORM, _______, _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  _______, _______, _______,
    _______, _______, RGB_TOG, _______, KC_UP,   _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, KC_WH_U, KC_LEFT, KC_DOWN, KC_RGHT, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, KC_WH_D, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_VOLU, PLAY,
    _______, _______, KC_TILD, _______, _______, _______, _______,          _______, _______, _______, _______, _______, KC_MPRV, KC_VOLD, KC_MNXT
  ),

  [MOUS] = LAYOUT_65_with_macro(
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, KC_MS_U, _______, _______, _______, _______, _______, _______, _______, KC_MS_U, _______, _______, _______, _______,
    _______, _______, _______, KC_MS_L, KC_MS_D, KC_MS_R, _______, _______, _______, _______, _______, KC_MS_L, KC_MS_D, KC_MS_R, _______, KC_PGUP,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_MS_U, KC_PGDN,
    _______, _______, _______, _______, _______, KC_BTN2, KC_BTN1,          _______, KC_BTN1, KC_BTN2, _______, _______, KC_MS_L, KC_MS_D, KC_MS_R
  ),

  [NORM] = LAYOUT_65_with_macro(
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______,          _______, KC_SPC,  _______, _______, _______, _______, _______, _______
  ),
};

#ifdef ENCODER_MAP_ENABLE
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][2] = {
    [BASE] = { ENCODER_CCW_CW(KC_LEFT, KC_RIGHT), ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },
    [MDIA] = { ENCODER_CCW_CW(RGB_RMOD, RGB_MOD), ENCODER_CCW_CW(RGB_SPD, RGB_SPI) },
    [MOUS] = { ENCODER_CCW_CW(RGB_HUD, RGB_HUI), ENCODER_CCW_CW(RGB_SAD, RGB_SAI) },
    [NORM] = { ENCODER_CCW_CW(KC_WH_D, KC_WH_U), ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },
};
#endif

layer_state_t layer_state_set_user(layer_state_t state) {
  switch(get_highest_layer(state)) {
    case BASE:
        rgblight_setrgb(RGB_WHITE);
        break;
    case MDIA:
        rgblight_setrgb(RGB_RED);
        break;
    case MOUS:
        rgblight_setrgb(RGB_BLUE);
        break;
    case NORM:
        rgblight_setrgb(RGB_WHITE);
        break;
  }
  return state;
}
