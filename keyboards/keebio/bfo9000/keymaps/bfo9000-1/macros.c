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
#define MAX_MACRO_SIZE 16
#define MACRO_PLAY_INTERVAL 1000

typedef struct {
    uint16_t    keycode;
    keyrecord_t keyrecord;
} macro_record;

typedef struct {
    bool          recording;
    macro_record *keys;
} custom_macro;

static uint16_t LAST_KEY_TIMESTAMPS[MATRIX_ROWS][MATRIX_COLS];

static custom_macro MACRO_OVERRIDES[MATRIX_ROWS][MATRIX_COLS];

static bool     CUSTOM_MACRO_SHOULD_START_RECORDING = false;
static bool     CUSTOM_MACRO_SHOULD_CLEAR           = false;
static keypos_t CUSTOM_MACRO_TO_RECORD;

#define MAX_TAP_DURATION 200

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

void reset_custom_macro(uint16_t row, uint16_t col) {
    MACRO_OVERRIDES[row][col].recording = false;
    free(MACRO_OVERRIDES[row][col].keys);
    MACRO_OVERRIDES[row][col].keys = NULL;
}

custom_macro *get_current_recording(void) {
    custom_macro *current_recording = &MACRO_OVERRIDES[CUSTOM_MACRO_TO_RECORD.row][CUSTOM_MACRO_TO_RECORD.col];
    if (!current_recording->recording) {
        return NULL;
    }
    return current_recording;
}

press_type get_press_type(keyrecord_t *record) {
    keypos_t       pos            = record->event.key;
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

void custom_macro_key(uint16_t keycode, keyrecord_t *record) {
    custom_macro *current_recording = get_current_recording();
    switch (get_press_type(record)) {
        case DOWN:
            break;
        case TAP_UP:
            if (current_recording != NULL) {
                current_recording->recording = false;
                break;
            }
            CUSTOM_MACRO_SHOULD_START_RECORDING = !CUSTOM_MACRO_SHOULD_START_RECORDING;
            break;
        case HOLD_UP:
            CUSTOM_MACRO_SHOULD_CLEAR = 1;
            break;
    }
}

void handle_custom_event(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        // Setup
        uint8_t initial_mods = get_mods();
        clear_mods();

        switch (keycode) {
            case CU_GMAL:
                gmail(keycode, record);
                break;
            case CU_YTUB:
                youtube(keycode, record);
                break;
            case CU_SCRN:
                screenshot(keycode);
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

void add_to_macro(custom_macro *macro, uint16_t keycode, keyrecord_t *record) {
    if (macro->keys == NULL) {
        macro_record keys[MAX_MACRO_SIZE];
        for (int i = 0; i < MAX_MACRO_SIZE; i++) {
            keys[i].keycode = KC_NO;
        }
        macro->keys = keys;
    }
    for (int i = 0; i < MAX_MACRO_SIZE; i++) {
        if (macro->keys[i].keycode == KC_NO) {
            macro->keys[i].keycode   = keycode;
            macro->keys[i].keyrecord = *record;
            return;
        }
    }
}

void start_macro_recording(keyrecord_t *record) {
    keypos_t      pos          = record->event.key;
    custom_macro *macro        = &MACRO_OVERRIDES[pos.row][pos.col];
    macro->recording           = true;
    CUSTOM_MACRO_TO_RECORD.row = pos.row;
    CUSTOM_MACRO_TO_RECORD.col = pos.col;
}

void play_macro(custom_macro *macro) {
    if (macro->keys == NULL || macro->recording) {
        return;
    }
    for (int i = 0; i < MAX_MACRO_SIZE; i++) {
        if (macro->keys[i].keycode == KC_NO) {
            break;
        }
        process_record(&macro->keys[i].keyrecord);
        // _delay_ms(MACRO_PLAY_INTERVAL);
    }
    dynamic_macro_play_user(1);
}

bool play_macro_or_key(uint16_t keycode, keyrecord_t *record) {
    keypos_t pos = record->event.key;
    if (CUSTOM_MACRO_SHOULD_CLEAR) {
        reset_custom_macro(pos.row, pos.col);
        CUSTOM_MACRO_SHOULD_CLEAR = false;
        return false;
    }

    if (CUSTOM_MACRO_SHOULD_START_RECORDING) {
        start_macro_recording(record);
        CUSTOM_MACRO_SHOULD_START_RECORDING = false;
        return false;
    }

    custom_macro *current_recording = get_current_recording();
    if (current_recording != NULL) {
        add_to_macro(current_recording, keycode, record);
        return false;
    }

    custom_macro *macro = &MACRO_OVERRIDES[pos.row][pos.col];
    if (macro->keys != NULL) {
        play_macro(macro);
        return false;
    }

    return true;
}

bool handle_key_event(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case CU_MACRO:
            custom_macro_key(keycode, record);
            return false;
        case CU_SPC_MOUS: // Tap for space, enable mouse layer when held
            space_mouse(keycode, record);
            break;
        case CU_ENT_MED:
            enter_media(keycode, record);
            return true;
        case CU_GMAL:
        case CU_YTUB:
        case CU_SCRN:
        case CU_TMUX:
            handle_custom_event(keycode, record);
            return false;
        default:
            if (record->event.pressed) {
                return play_macro_or_key(keycode, record);
            }
    }
    return true;
}

/**
 * https://beta.docs.qmk.fm/using-qmk/guides/custom_quantum_functions
 */
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    bool should_propigate = handle_key_event(keycode, record);
    // Record the keypress
    keypos_t pos                          = record->event.key;
    LAST_KEY_TIMESTAMPS[pos.row][pos.col] = record->event.time;

    return should_propigate;
}

void matrix_init_(void) {
    for (int i = 0; i < MATRIX_ROWS; i++) {
        for (int j = 0; j < MATRIX_COLS; j++) {
            reset_custom_macro(i, j);
        }
    }
}

void keyboard_post_init_user(void) {
  // Customise these values to desired behaviour
  debug_enable=true;
  debug_matrix=true;
  //debug_keyboard=true;
  //debug_mouse=true;
}
