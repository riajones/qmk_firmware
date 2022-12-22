#include QMK_KEYBOARD_H
#include "riajones.h"

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


//////////////////////////////////////////////////////////////////////
// HME_END                                                          //
//////////////////////////////////////////////////////////////////////
void hmeend_finished(qk_tap_dance_state_t *state, void *user_data) {
  td_state = cur_dance(state);
  switch (td_state) {
    case TD_SINGLE_TAP:
    case TD_SINGLE_TAP_HOLD:
      register_code16(KC_HOME);
      break;
    case TD_DOUBLE_TAP:
    case TD_DOUBLE_TAP_HOLD:
      register_code16(KC_END);
      break;
    default:
      break;
  }
}

void hmeend_reset(qk_tap_dance_state_t *state, void *user_data) {
  switch (td_state) {
    case TD_SINGLE_TAP:
    case TD_SINGLE_TAP_HOLD:
      unregister_code16(KC_HOME);
      break;
    case TD_DOUBLE_TAP:
    case TD_DOUBLE_TAP_HOLD:
      unregister_code16(KC_END);
      break;
    default:
      break;
  }
}

//////////////////////////////////////////////////////////////////////
// CMD_MOU                                                          //
//////////////////////////////////////////////////////////////////////
void cmdmou_finished(qk_tap_dance_state_t *state, void *user_data) {
  td_state = cur_dance(state);
  switch (td_state) {
    case TD_SINGLE_TAP_HOLD:
      register_mods(MOD_BIT(KC_LGUI));
      break;
    case TD_DOUBLE_TAP_HOLD:
      layer_invert(MOUSE);
      break;
    default:
      break;
  }
}

void cmdmou_reset(qk_tap_dance_state_t *state, void *user_data) {
  switch (td_state) {
    case TD_SINGLE_TAP_HOLD:
      unregister_mods(MOD_BIT(KC_LGUI));
      break;
    case TD_DOUBLE_TAP_HOLD:
      layer_invert(MOUSE);
      break;
    default:
      break;
  }
}

//////////////////////////////////////////////////////////////////////
// FN1_MOU                                                          //
//////////////////////////////////////////////////////////////////////
void fn1mou_finished(qk_tap_dance_state_t *state, void *user_data) {
  td_state = cur_dance(state);
  switch (td_state) {
    case TD_SINGLE_TAP_HOLD:
      layer_invert(FN1);
      break;
    case TD_DOUBLE_TAP_HOLD:
      layer_invert(MOUSE);
      break;
    default:
      break;
  }
}

void fn1mou_reset(qk_tap_dance_state_t *state, void *user_data) {
  switch (td_state) {
    case TD_SINGLE_TAP_HOLD:
      layer_invert(FN1);
      break;
    case TD_DOUBLE_TAP_HOLD:
      layer_invert(MOUSE);
      break;
    default:
      break;
  }
}

//////////////////////////////////////////////////////////////////////
// Map actions to handlers                                          //
//////////////////////////////////////////////////////////////////////
// Define `ACTION_TAP_DANCE_FN_ADVANCED()` for each tapdance keycode, passing in `finished` and `reset` functions
qk_tap_dance_action_t tap_dance_actions[] = {
    [HME_END] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, hmeend_finished, hmeend_reset),
    [CMD_MOU] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, cmdmou_finished, cmdmou_reset),
    [FN1_MOU] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, fn1mou_finished, fn1mou_reset),
};
