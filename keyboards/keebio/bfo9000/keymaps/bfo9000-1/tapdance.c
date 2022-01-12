#include "quantum.h"

//////////////////////////////////////////////////////////////////////
//  Tap Dance Setup                                                 //
//////////////////////////////////////////////////////////////////////
// https://beta.docs.qmk.fm/using-qmk/software-features/feature_tap_dance#how-to-use-tap-dance-id-how-to-use

// Tap Dance keycodes
enum td_keycodes {
    ESC_LT, // Toggle OSX -> Double Tap Held || Escape when Pressed
    CMD_SHIFT, // CMD When Held || Shiftble Tap Hold
    HM_WSL, // Home key on single press, workspace left on double press
    END_WSR, // End key on single press, workspace right on double press
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

static td_state_t td_state;

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

void esclt_finished(qk_tap_dance_state_t *state, void *user_data) {
  td_state = cur_dance(state);
  switch (td_state) {
    case TD_SINGLE_TAP_HOLD:
      clear_mods();
    case TD_SINGLE_TAP:
    case TD_DOUBLE_TAP:
      register_code16(KC_ESC);
      break;
    case TD_DOUBLE_TAP_HOLD:
      layer_invert(OSX);
      break;
    default:
      break;
  }
}

void esclt_reset(qk_tap_dance_state_t *state, void *user_data) {
  switch (td_state) {
    case TD_SINGLE_TAP:
    case TD_DOUBLE_TAP:
      unregister_code16(KC_ESC);
    default:
      break;
  }
}

void cmd_shift_finished(qk_tap_dance_state_t *state, void *user_data) {
  td_state = cur_dance(state);
  switch (td_state) {
    case TD_SINGLE_TAP:
    case TD_SINGLE_TAP_HOLD:
      register_mods(MOD_BIT(KC_LGUI));
      break;
    case TD_DOUBLE_TAP_HOLD:
      register_mods(MOD_BIT(KC_LSFT));
      break;
    default:
      break;
  }
}

void cmd_shift_reset(qk_tap_dance_state_t *state, void *user_data) {
  switch (td_state) {
    case TD_SINGLE_TAP:
    case TD_SINGLE_TAP_HOLD:
      unregister_mods(MOD_BIT(KC_LGUI));
      break;
    case TD_DOUBLE_TAP_HOLD:
      unregister_mods(MOD_BIT(KC_LSFT));
      break;
    default:
      break;
  }
}

void hm_wsl_finished(qk_tap_dance_state_t *state, void *user_data) {
  td_state = cur_dance(state);
  switch (td_state) {
    case TD_SINGLE_TAP:
    case TD_SINGLE_TAP_HOLD:
      register_code16(KC_HOME);
      break;
    case TD_DOUBLE_TAP:
    case TD_DOUBLE_TAP_HOLD:
      if (layer_state_is(OSX)) {
        register_mods(MOD_BIT(KC_LCTL));
      } else {
        register_mods(MOD_BIT(KC_LCTL));
        register_mods(MOD_BIT(KC_LALT));
      }
      register_code16(KC_LEFT);
      break;
    default:
      break;
  }
}

void hm_wsl_reset(qk_tap_dance_state_t *state, void *user_data) {
  switch (td_state) {
    case TD_SINGLE_TAP:
    case TD_SINGLE_TAP_HOLD:
      unregister_code16(KC_HOME);
      break;
    case TD_DOUBLE_TAP:
    case TD_DOUBLE_TAP_HOLD:
      if (layer_state_is(OSX)) {
        unregister_mods(MOD_BIT(KC_LCTL));
      } else {
        unregister_mods(MOD_BIT(KC_LCTL));
        unregister_mods(MOD_BIT(KC_LALT));
      }
      unregister_code16(KC_LEFT);
      break;
    default:
      break;
  }
}

void end_wsr_finished(qk_tap_dance_state_t *state, void *user_data) {
  td_state = cur_dance(state);
  switch (td_state) {
    case TD_SINGLE_TAP:
    case TD_SINGLE_TAP_HOLD:
      register_code16(KC_END);
      break;
    case TD_DOUBLE_TAP:
    case TD_DOUBLE_TAP_HOLD:
      register_code16(layer_state_is(OSX) ? OSX_WSR : LIN_WSR);
      break;
    default:
      break;
  }
}

void end_wsr_reset(qk_tap_dance_state_t *state, void *user_data) {
  switch (td_state) {
    case TD_SINGLE_TAP:
    case TD_SINGLE_TAP_HOLD:
      unregister_code16(KC_END);
      break;
    case TD_DOUBLE_TAP:
    case TD_DOUBLE_TAP_HOLD:
      unregister_code16(layer_state_is(OSX) ? OSX_WSR : LIN_WSR);
      break;
    default:
      break;
  }
}

// Define `ACTION_TAP_DANCE_FN_ADVANCED()` for each tapdance keycode, passing in `finished` and `reset` functions
qk_tap_dance_action_t tap_dance_actions[] = {
  [ESC_LT] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, esclt_finished, esclt_reset),
  [CMD_SHIFT] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, cmd_shift_finished, cmd_shift_reset),
  [HM_WSL] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, hm_wsl_finished, hm_wsl_reset),
  [END_WSR] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, end_wsr_finished, end_wsr_reset),
};