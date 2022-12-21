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

enum layers {
  BASE,
  FN1,
  MOUSE,
};

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
};

// Tap Dance keycodes
enum td_keycodes {
    HME_END, // Single tap home, double tap end
    CMD_MOU, // Mouse when held, cmd when tapped and held
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
