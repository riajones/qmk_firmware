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

// void custom_arrow(uint16_t keycode, keyrecord_t *record) {
//   if (record->event.pressed) {
//     uint8_t mods_state = get_mods();
//     if (MOD_BIT(KC_LALT) && MOD_BIT(KC_LGUI)) {
//       clear_mods();
//       add_mods(mod_config(MOD_LCTL));
//       if (keycode == CU_LEFT) {
//         add_mods(mod_config(MOD_LSFT));
//       } 
//       tap_code(KC_TAB);
//       set_mods(mods_state);
//       return;
//     }

//     if (keycode == CU_LEFT) {
//       tap_code(KC_LEFT);
//     } else if (keycode == CU_RIGHT) {
//       tap_code(KC_RGHT);
//     }
//   }
// }

void github(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed) {
    SEND_STRING("https://github.com");
  }
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

bool handle_key_event(uint16_t keycode, keyrecord_t *record) {
  switch(keycode) {
    case CU_GITHUB:
      github(keycode, record);
      return false;
    case CU_SPC_MOUS: // Tap for space, enable mouse layer when held
      space_mouse(keycode, record);
      break;
    case CU_KVM:
      if (record->event.pressed) {
        tap_code(KC_SCROLLLOCK);
        tap_code(KC_SCROLLLOCK);
      }
      return false;
    case CU_ENT_MED:
      enter_media(keycode, record);
      return true;
    // case CU_LEFT:
    // case CU_RIGHT:
    //   custom_arrow(keycode, record);
    //   return false;
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
