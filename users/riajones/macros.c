/* Copyright 2022 Riley Jones <riajones88@gmail.com> @riajones
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

typedef enum press_type {
    DOWN,
    HOLD_UP,
    TAP_UP,
} press_type;

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

static uint16_t LAST_KEY_TIMESTAMPS[MATRIX_ROWS][MATRIX_COLS];

// Utility Functions
void send_int(uint16_t num) {
    char *str = "error";
    itoa(num, str, 10);
    send_string(str);
}

// Macro Definitions
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

// Life Cycle Functions
void handle_custom_event(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        // Setup
        uint8_t initial_mods = get_mods();
        clear_mods();

        switch (keycode) {
            default:
                break;
        }

        // Cleanup
        clear_mods();
        set_mods(initial_mods);
    }
}

bool handle_key_event(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case CU_MACRO:
            custom_macro_key(keycode, record);
            return false;
        case CU_ENT_MED:
            enter_media(keycode, record);
            return true;
        // Some other cases should trigger handle_custom_event then return false
        default:
            if (record->event.pressed) {
                return play_macro_or_key(keycode, record);
            }
    }
    return true;
}

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
