/**
 * https://github.com/qmk/qmk_firmware/blob/master/tmk_core/common/keyboard.h
 * typedef struct {
 *   uint8_t col;
 *   uint8_t row;
 * } keypos_t;
 *
 * typedef struct {
 *   keypos_t key;
 *   bool     pressed;
 *   uint16_t time;
 * } keyevent_t;
 */
static uint16_t LAST_KEY_TIMESTAMPS[MATRIX_ROWS][MATRIX_COLS];
static int MAX_TAP_DURATION = 200;

typedef enum press_type {
  DOWN,
  HOLD_UP,
  TAP_UP,
} press_type;

void send_int(uint16_t num) {
  char *str = "error";
  itoa(num, str, 10);
  send_string(str);
}

press_type get_press_type(keyrecord_t *record) {
  keypos_t pos = record->event.key;
  const uint16_t last_timestamp = LAST_KEY_TIMESTAMPS[pos.row][pos.col];
  if (record->event.pressed) {
    return DOWN;
  }
  int press_time = record->event.time - last_timestamp;
  if (press_time < MAX_TAP_DURATION) {
    return TAP_UP;
  }
  return HOLD_UP;
}

void launch_program(char *name) {
  // Setup
  uint8_t initial_mods = get_mods();
  clear_mods();
  if (layer_state_is(BASE)) {
    tap_code(KC_LGUI);
    tap_code_delay(KC_LGUI, 100);
    send_string(name);
    tap_code_delay(KC_ENT, 500);
  }
  if (layer_state_is(OSX)) {
    add_mods(mod_config(MOD_LGUI));
    tap_code(KC_SPACE);
    tap_code_delay(KC_LGUI, 100);
    send_string(name);
    tap_code_delay(KC_ENT, 500);
  }
  // Cleanup
  clear_mods();
  set_mods(initial_mods);
}

void screenshot(uint16_t keycode) {
  if (layer_state_is(BASE)) {
    add_mods(mod_config(MOD_LCTL & MOD_MASK_SHIFT));
    tap_code(KC_PSCR);
  }
  if (layer_state_is(OSX)) {
    add_mods(mod_config(MOD_LGUI & MOD_MASK_SHIFT));
    tap_code(KC_4);
  }
}

void terminal(uint16_t keycode) {
  if (layer_state_is(BASE)) {
    launch_program("terminal");
  }
  if (layer_state_is(OSX)) {
    launch_program("terminal");
  }
}

void vscode(uint16_t keycode) {
   if (layer_state_is(BASE)) {
    launch_program("vscode");
  }
  if (layer_state_is(OSX)) {
    launch_program("Visual Studio Code");
  }
}

void obs_controls(uint16_t keycode) {
  switch (keycode) {
    case OBS_STR:
      send_string(SS_LCTL(SS_LALT("v")));
      break;
    case OBS_STP:
      send_string(SS_LCTL(SS_LALT(SS_LSFT("v"))));
      break;
    case OBS_SC1:
      send_string(SS_LCTL(SS_LGUI(SS_LALT(SS_LSFT("1")))));
      break;
    case OBS_SC2:
      send_string(SS_LCTL(SS_LGUI(SS_LALT(SS_LSFT("2")))));
      break;
    case OBS_SC3:
      send_string(SS_LCTL(SS_LGUI(SS_LALT(SS_LSFT("3")))));
      break;
  }
}

void snap_left(uint16_t keycode) {
  if (layer_state_is(BASE)) {
    add_mods(mod_config(MOD_LGUI));
    tap_code(KC_LEFT);
  }
  if (layer_state_is(OSX)) {
    add_mods(mod_config(MOD_LCTL & MOD_LALT));
    tap_code(KC_LEFT);
  }
}
void snap_right(uint16_t keycode) {
  if (layer_state_is(BASE)) {
    add_mods(mod_config(MOD_LGUI));
    tap_code(KC_RIGHT);
  }
  if (layer_state_is(OSX)) {
    add_mods(mod_config(MOD_LCTL & MOD_LALT));
    tap_code(KC_RIGHT);
  }
}
void workspace_left(uint16_t keycode) {
  if (layer_state_is(BASE)) {
    add_mods(mod_config(MOD_LCTL & MOD_LALT));
    tap_code(KC_LEFT);
  }
  if (layer_state_is(OSX)) {
    add_mods(mod_config(MOD_LCTL));
    tap_code(KC_LEFT);
  }
}
void workspace_right(uint16_t keycode) {
  if (layer_state_is(BASE)) {
    add_mods(mod_config(MOD_LCTL & MOD_LALT));
    tap_code(KC_RIGHT);
  }
  if (layer_state_is(OSX)) {
    add_mods(mod_config(MOD_LCTL));
    tap_code(KC_RIGHT);
  }
}
void dashboard(uint16_t keycode) {
  if (layer_state_is(BASE)) {
    tap_code(KC_LGUI);
  }
  if (layer_state_is(OSX)) {
    add_mods(mod_config(MOD_LCTL));
    tap_code(KC_UP);
  }
}

void github(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed) {
    SEND_STRING("https://github.com");
  }
}
void gmail(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed) {
    SEND_STRING("https://gmail.com");
  }
}
void youtube(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed) {
    SEND_STRING("https://youtube.com");
  }
}

void handle_custom_event(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed) {
    // Setup
    uint8_t initial_mods = get_mods();
    clear_mods();

    switch(keycode) {
      case CU_SCRN:
        screenshot(keycode);
        break;
      case CU_TERM:
        terminal(keycode);
        break;
      case CU_SNPL:
        snap_left(keycode);
        break;
      case CU_SNPR:
        snap_right(keycode);
        break;
      case CU_WSPL:
        workspace_left(keycode);
        break;
      case CU_WSPR:
        workspace_right(keycode);
        break;
      case CU_DASH:
        dashboard(keycode);
        break;
      case CU_CODE:
        vscode(keycode);
        break;
      case CU_CHRM:
        launch_program("Google Chrome");
        break;
      case CU_STEM:
        launch_program("Steam");
        break;
      case CU_OBS:
        launch_program("OBS");
        break;
      case CU_DSCD:
        launch_program("Discord");
        break;
      case OBS_STR:
      case OBS_STP:
      case OBS_SC1:
      case OBS_SC2:
      case OBS_SC3:
        obs_controls(keycode);
        break;
      default:
        break;
    }

    // Cleanup
    clear_mods();
    set_mods(initial_mods);
  }
}

bool handle_key_event(uint16_t keycode, keyrecord_t *record) {
  switch(keycode) {
    case CU_GHUB:
      github(keycode, record);
      return false;
    case CU_GMAL:
      gmail(keycode, record);
      return false;
    case CU_YTUB:
      youtube(keycode, record);
      return false;
    case CU_SCRN:
    case CU_TERM:
    case CU_SNPL:
    case CU_SNPR:
    case CU_WSPL:
    case CU_WSPR:
    case CU_DASH:
    case CU_CODE:
    case CU_CHRM:
    case CU_STEM:
    case CU_OBS:
    case CU_DSCD:
    case OBS_STR:
    case OBS_STP:
    case OBS_SC1:
    case OBS_SC2:
    case OBS_SC3:
      handle_custom_event(keycode, record);
      return false;
    default:
      break;
  }
  return true;
}

/**
 * https://beta.docs.qmk.fm/using-qmk/guides/custom_quantum_functions
*/
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  bool should_propigate = handle_key_event(keycode, record);
  // Record the keypress
  keypos_t pos = record->event.key;
  LAST_KEY_TIMESTAMPS[pos.row][pos.col] = record->event.time;

  return should_propigate;
}

// void post_process_record_user(uint16_t keycode, keyrecord_t *record) {
// }
