#define MAX_MACRO_SIZE 16
#define MACRO_PLAY_INTERVAL 1000

typedef struct {
    uint16_t    keycode;
    keyrecord_t record;
} macro_record;

typedef struct {
    bool          recording;
    macro_record *keys;
} custom_macro;

static custom_macro MACRO_OVERRIDES[MATRIX_ROWS][MATRIX_COLS];

static bool     CUSTOM_MACRO_SHOULD_START_RECORDING = false;
static bool     CUSTOM_MACRO_SHOULD_CLEAR           = false;
static keypos_t CUSTOM_MACRO_TO_RECORD;

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
            macro->keys[i].record = *record;
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
        register_code(macro->keys[i].keycode);
        unregister_code(macro->keys[i].keycode);
    }
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
