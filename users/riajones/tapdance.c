#include QMK_KEYBOARD_H
#include "riajones.h"

static td_state_t td_state;

// Function to determine the current tapdance state
td_state_t cur_dance(tap_dance_state_t *state) {
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
void hmeend_finished(tap_dance_state_t *state, void *user_data) {
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

void hmeend_reset(tap_dance_state_t *state, void *user_data) {
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
void cmdmou_finished(tap_dance_state_t *state, void *user_data) {
  td_state = cur_dance(state);
  switch (td_state) {
    case TD_SINGLE_TAP:
    case TD_SINGLE_TAP_HOLD:
      register_mods(MOD_BIT(KC_LGUI));
      break;
    case TD_DOUBLE_TAP_HOLD:
      layer_invert(MOUS);
      break;
    default:
      break;
  }
}

void cmdmou_reset(tap_dance_state_t *state, void *user_data) {
  switch (td_state) {
    case TD_SINGLE_TAP:
    case TD_SINGLE_TAP_HOLD:
      unregister_mods(MOD_BIT(KC_LGUI));
      break;
    case TD_DOUBLE_TAP_HOLD:
      layer_invert(MOUS);
      break;
    default:
      break;
  }
}

//////////////////////////////////////////////////////////////////////
// MDI_MOU                                                          //
//////////////////////////////////////////////////////////////////////
void medmou_finished(tap_dance_state_t *state, void *user_data) {
  td_state = cur_dance(state);
  switch (td_state) {
    case TD_SINGLE_TAP_HOLD:
      layer_invert(MDIA);
      break;
    case TD_DOUBLE_TAP_HOLD:
      layer_invert(MOUS);
      break;
    default:
      break;
  }
}

void medmou_reset(tap_dance_state_t *state, void *user_data) {
  switch (td_state) {
    case TD_SINGLE_TAP_HOLD:
      layer_invert(MDIA);
      break;
    case TD_DOUBLE_TAP_HOLD:
      layer_invert(MOUS);
      break;
    default:
      break;
  }
}

//////////////////////////////////////////////////////////////////////
// TB_CORP                                                          //
//////////////////////////////////////////////////////////////////////
void tbcorp_finished(tap_dance_state_t *state, void *user_data) {
  td_state = cur_dance(state);
  switch (td_state) {
    case TD_SINGLE_TAP:
    case TD_SINGLE_TAP_HOLD:
      send_string("https://staging-tensorboard.corp.google.com");
      break;
    case TD_DOUBLE_TAP:
    case TD_DOUBLE_TAP_HOLD:
      send_string("http://localhost:8080");
      break;
    default:
      break;
  }
}

void tbcorp_reset(tap_dance_state_t *state, void *user_data) {}

//////////////////////////////////////////////////////////////////////
// TB_OSS                                                           //
//////////////////////////////////////////////////////////////////////
void tboss_finished(tap_dance_state_t *state, void *user_data) {
  td_state = cur_dance(state);
  switch (td_state) {
    case TD_SINGLE_TAP:
    case TD_SINGLE_TAP_HOLD:
      send_string("https://localhost:6006");
      break;
    case TD_DOUBLE_TAP:
    case TD_DOUBLE_TAP_HOLD:
      send_string("https://github.com/tensorflow/tensorboard");
      break;
    default:
      break;
  }
}

void tboss_reset(tap_dance_state_t *state, void *user_data) {}

//////////////////////////////////////////////////////////////////////
// GITHUB                                                           //
//////////////////////////////////////////////////////////////////////
void github_finished(tap_dance_state_t *state, void *user_data) {
  td_state = cur_dance(state);
  switch (td_state) {
    case TD_SINGLE_TAP:
    case TD_SINGLE_TAP_HOLD:
      send_string("https://github.com/pulls");
      break;
    case TD_DOUBLE_TAP:
    case TD_DOUBLE_TAP_HOLD:
      send_string("https://github.com");
      break;
    default:
      break;
  }
}

void github_reset(tap_dance_state_t *state, void *user_data) {}

//////////////////////////////////////////////////////////////////////
// Map actions to handlers                                          //
//////////////////////////////////////////////////////////////////////
// Define `ACTION_TAP_DANCE_FN_ADVANCED()` for each tapdance keycode, passing in `finished` and `reset` functions
tap_dance_action_t tap_dance_actions[] = {
    [HME_END] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, hmeend_finished, hmeend_reset),
    [CMD_MOU] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, cmdmou_finished, cmdmou_reset),
    [MED_MOU] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, medmou_finished, medmou_reset),
    [TB_CORP] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, tbcorp_finished, tbcorp_reset),
    [TB_OSS] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, tboss_finished, tboss_reset),
    [GITHUB] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, github_finished, github_reset),
};
