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

void tensorboard_oss(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed) {
    SEND_STRING("http://localhost:6006");
  }
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

void tmux(uint16_t keycode, keyrecord_t *record) {
    add_mods(mod_config(MOD_LCTL));
    tap_code(KC_B);
}

void space_mouse(uint16_t keycode, keyrecord_t *record) {
  switch (get_press_type(record)) {
    case DOWN:
      layer_on(MOUS);
      break;
    case TAP_UP:
      tap_code(KC_SPC);
    case HOLD_UP:
      layer_off(MOUS);
      break;
  }
}

void enter_media(uint16_t keycode, keyrecord_t *record) {
  switch (get_press_type(record)) {
    case DOWN:
      layer_on(MDIA);
      break;
    case TAP_UP:
      tap_code(KC_ENT);
    case HOLD_UP:
      layer_off(MDIA);
      break;
  }
}

void handle_custom_event(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed) {
    // Setup
    uint8_t initial_mods = get_mods();
    clear_mods();

    switch(keycode) {
      case CU_GHUB:
        github(keycode, record);
        break;
      case CU_GMAL:
        gmail(keycode, record);
        break;
      case CU_YTUB:
        youtube(keycode, record);
        break;
      case CU_SCRN:
        screenshot(keycode);
        break;
      case CU_TBOS:
        tensorboard_oss(keycode, record);
        break;
      case CU_TMUX:
        tmux(keycode, record);
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
    case CU_SPC_MOUS: // Tap for space, enable mouse layer when held
      space_mouse(keycode, record);
      break;
    case CU_ENT_MED:
      enter_media(keycode, record);
      return true;
    case CU_GHUB:
    case CU_GMAL:
    case CU_YTUB:
    case CU_SCRN:
    case CU_TBOS:
    case CU_TMUX:
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
