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

#define PLAY KC_MEDIA_PLAY_PAUSE
#define SS_LINU LSFT(LCTL(KC_PSCR))
#define CTL_APP LCTL_T(KC_APP)

#ifdef TAP_DANCE_ENABLE
#define TD_CMOU TD(CMD_MOU)
#define TD_MDMO TD(MED_MOU)
#define TD_TBCP TD(TB_CORP)
#define TD_TBOS TD(TB_OSS)
#define TD_GITH TD(GITHUB)
#endif

enum layers {
  BASE,
  MDIA,
  MOUS,
  NORM,
};

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  #ifdef CUSTOM_MACROS_ENABLED
  CU_MACRO,
  #endif
  CU_ENT_MED,
  CU_MED_MOU,
};

// Tap Dance keycodes
enum td_keycodes {
    HME_END, // Single tap home, double tap end
    CMD_MOU, // CMD when held, mouse when tapped and held
    MED_MOU, // Activates MDIA when held, activates mouse when tapped and held
    TB_CORP, // Types out the address for tensorboard.corp
    TB_OSS,  // Types out the address for tensorboard oss or the github repo
    GITHUB,  // Types out either github.com/pulls or github.com
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
