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

bool handle_key_event(uint16_t keycode, keyrecord_t *record) {
  switch(keycode) {
    case CU_GITHUB:
      github(keycode, record);
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
