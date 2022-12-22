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

#pragma once

#include QMK_KEYBOARD_H

// Aliases
#define PLAY KC_MEDIA_PLAY_PAUSE
#define CTL_APP LCTL_T(KC_APP)

#define LIN_WSL LCA(KC_LEFT)
#define LIN_WSR LCA(KC_RIGHT)
#define LIN_WSU KC_LGUI
#define LIN_SNL LGUI(KC_LEFT)
#define LIN_SNR LGUI(KC_RIGHT)
#define OSX_WSL LCTL(KC_LEFT)
#define OSX_WSR LCTL(KC_RIGHT)
#define OSX_WSU LCTL(KC_UP)
#define OSX_SNL LCA(KC_LEFT)
#define OSX_SNR LCA(KC_RIGHT)

#define SS_LINU LSFT(LCTL(KC_PSCR))
#define SS_OSX LSG(KC_4)

#define DB_STRT KC_F8
#define DB_PLAY KC_F8
#define DB_STEP KC_F10
#define DB_IN KC_F11
#define DB_OUT LSFT(KC_F11)

// Tapdance Aliases
#ifdef TAP_DANCE_ENABLE
#define TD_CMOU TD(CMD_MOU)
#define TD_FMOU TD(FN1_MOU)
#endif

enum layers {
  BASE,
  OSX,
  MDIA,
  MOUS,
  NORM,
};

enum custom_keycodes {
  // String  Inputs
  CU_GMAL = SAFE_RANGE,
  CU_YTUB,
  // Custom behavior
  CU_MACRO,
  // Operating System Functionality
  CU_SCRN,
  CU_TERM,
  CU_TMUX,
  CU_SPC_MOUS,
  CU_ENT_MED,
  NEW_SAFE_RANGE,
};


#ifdef TAP_DANCE_ENABLE
// Tap Dance keycodes
enum td_keycodes {
  HME_END, // Single tap home, double tap end
  CMD_MOU, // CMD when held, mouse when tapped and held
  FN1_MOU, // Activates FN1 when held, activates mouse when tapped and held
};

// Define a type containing as many tapdance states as you need
typedef enum {
  TD_NONE,
  TD_UNKNOWN,
  TD_SINGLE_TAP,
  TD_SINGLE_TAP_HOLD,
  TD_DOUBLE_TAP,
  TD_DOUBLE_TAP_HOLD
} td_state_t;
#endif
