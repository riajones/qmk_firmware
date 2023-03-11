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

static uint16_t LAST_KEY_TIMESTAMPS[MATRIX_ROWS][MATRIX_COLS];
static const int MAX_TAP_DURATION = 100;

typedef enum press_type {
    TAP,
    HOLD,
    TAP_HOLD,
    TAP_HOLD_RELEASE,
} press_type;

press_type get_press_type(keyrecord_t *record) {
    keypos_t pos = record->event.key;
    uint16_t last_timestamp = LAST_KEY_TIMESTAMPS[pos.row][pos.col];
    int press_time = record->event.time - last_timestamp;
    if (record->event.pressed) {
        if (press_time < MAX_TAP_DURATION) {
            return TAP_HOLD;
        }
        return HOLD;
    }

    if (press_time < MAX_TAP_DURATION) {
        return TAP;
    }
    return TAP_HOLD_RELEASE;
}

// Utility Functions
void send_int(uint16_t num) {
    char *str = "error";
    itoa(num, str, 10);
    send_string(str);
}

// Macro Definitions
void enter_media(uint16_t keycode, keyrecord_t *record) {
    switch (get_press_type(record)) {
        case HOLD:
        case TAP_HOLD:
            layer_on(MDIA);
            break;
        case TAP:
            tap_code(KC_ENT);
        case TAP_HOLD_RELEASE:
            layer_off(MDIA);
            break;
    }
}

void media_mouse(uint16_t keycode, keyrecord_t *record) {
    switch (get_press_type(record)) {
        case HOLD:
            layer_on(MDIA);
            break;
        case TAP_HOLD:
            layer_on(MOUS);
            break;
        case TAP:
        case TAP_HOLD_RELEASE:
            layer_off(MDIA);
            layer_off(MOUS);
            break;
    }
}

#ifdef CUSTOM_MACROS_ENABLED
void custom_macro_key(uint16_t keycode, keyrecord_t *record) {
    custom_macro *current_recording = get_current_recording();
    switch (get_press_type(record)) {
        case HOLD:
            break;
        case TAP_UP:
            if (current_recording != NULL) {
                current_recording->recording = false;
                break;
            }
            CUSTOM_MACRO_SHOULD_START_RECORDING = !CUSTOM_MACRO_SHOULD_START_RECORDING;
            break;
        case TAP:
        case TAP_HOLD_RELEASE:
            CUSTOM_MACRO_SHOULD_CLEAR = 1;
            break;
    }
}
#endif

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
        #ifdef CUSTOM_MACROS_ENABLED
        case CU_MACRO:
            custom_macro_key(keycode, record);
            return false;
        #endif
        case CU_ENT_MED:
            enter_media(keycode, record);
            return true;
        case CU_MED_MOU:
            media_mouse(keycode, record);
            return false;
        default:
            if (record->event.pressed) {
                #ifdef CUSTOM_MACROS_ENABLED
                return play_macro_or_key(keycode, record);
                #endif
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
    #ifdef CUSTOM_MACROS_ENABLED
    for (int i = 0; i < MATRIX_ROWS; i++) {
        for (int j = 0; j < MATRIX_COLS; j++) {
            reset_custom_macro(i, j);
        }
    }
    #endif
}
