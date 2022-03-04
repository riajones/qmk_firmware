#include "quantum.h"

//////////////////////////////////////////////////////////////////////
//  Tap Dance Setup                                                 //
//////////////////////////////////////////////////////////////////////
// https://beta.docs.qmk.fm/using-qmk/software-features/feature_tap_dance#how-to-use-tap-dance-id-how-to-use

// Tap Dance keycodes
enum td_keycodes {
  TD_PLACEHOLDER, // Replace if adding tapdance key
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

// static td_state_t td_state;

// Function to determine the current tapdance state
td_state_t cur_dance(qk_tap_dance_state_t *state) {
  if (state->count == 1) {
    if (state->interrupted || !state->pressed) {
      return TD_SINGLE_TAP;
    }
    return TD_SINGLE_TAP_HOLD;
  }

  if (state->count == 2) {
    if (state->interrupted || !state->pressed) {
      return TD_DOUBLE_TAP;
    }
    return TD_DOUBLE_TAP_HOLD;
  }
  return TD_UNKNOWN; // Any number higher than the maximum state value you return above
}

// Define `ACTION_TAP_DANCE_FN_ADVANCED()` for each tapdance keycode, passing in `finished` and `reset` functions
qk_tap_dance_action_t tap_dance_actions[] = {
};
