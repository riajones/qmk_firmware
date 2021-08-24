#include "quantum.h"

//////////////////////////////////////////////////////////////////////
//  Tap Dance Setup                                                 //
//////////////////////////////////////////////////////////////////////
// https://beta.docs.qmk.fm/using-qmk/software-features/feature_tap_dance#how-to-use-tap-dance-id-how-to-use

// Tap Dance keycodes
enum td_keycodes {
    ESC_LT // Toggle OSX When Held Escape when Pressed
};

// Define a type containing as many tapdance states as you need
typedef enum {
    TD_NONE,
    TD_UNKNOWN,
    TD_SINGLE_TAP,
    TD_SINGLE_HOLD,
    TD_DOUBLE_SINGLE_TAP
} td_state_t;

static td_state_t td_state;

// Function to determine the current tapdance state
td_state_t cur_dance(qk_tap_dance_state_t *state) {
  if (state->count == 1) {
    if (state->interrupted || !state->pressed) {
      return TD_SINGLE_TAP;
    }
    return TD_SINGLE_HOLD;
  }

  if (state->count == 2) {
    return TD_DOUBLE_SINGLE_TAP;
  }
  return TD_UNKNOWN; // Any number higher than the maximum state value you return above
}

void esclt_finished(qk_tap_dance_state_t *state, void *user_data) {
  td_state = cur_dance(state);
  switch (td_state) {
    case TD_NONE:
    case TD_UNKNOWN:
      break;
    case TD_SINGLE_TAP:
      register_code16(KC_ESC);
      break;
    case TD_SINGLE_HOLD:
      // register_mods(MOD_BIT(KC_LALT)); // For a layer-tap key, use `layer_on(_MY_LAYER)` here
      layer_invert(OSX);
      break;
    case TD_DOUBLE_SINGLE_TAP: // Allow nesting of 2 parens `((` within tapping term
      tap_code16(KC_ESC);
      register_code16(KC_ESC);
  }
}

void esclt_reset(qk_tap_dance_state_t *state, void *user_data) {
  switch (td_state) {
    case TD_NONE:
    case TD_UNKNOWN:
      break;
    case TD_SINGLE_TAP:
      unregister_code16(KC_ESC);
      break;
    case TD_SINGLE_HOLD:
      // unregister_mods(MOD_BIT(KC_LALT)); // For a layer-tap key, use `layer_off(_MY_LAYER)` here
      break;
    case TD_DOUBLE_SINGLE_TAP:
      unregister_code16(KC_ESC);
  }
}

// Define `ACTION_TAP_DANCE_FN_ADVANCED()` for each tapdance keycode, passing in `finished` and `reset` functions
qk_tap_dance_action_t tap_dance_actions[] = {
  [ESC_LT] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, esclt_finished, esclt_reset)
};