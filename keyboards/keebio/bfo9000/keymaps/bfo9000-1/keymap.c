#include QMK_KEYBOARD_H

// Custom Macros
#define PLAY KC_MEDIA_PLAY_PAUSE
#define WS_LEFT LCA(KC_LEFT)
#define WS_RIGH LCA(KC_RIGHT)
#define OSX_WSL LCTL(KC_LEFT)
#define OSX_WSR LCTL(KC_RIGHT)

enum layers {
    BASE,  // default layer
    OSX,   // symbols
    MDIA,  // media keys
    MOUS,  // mouse keys
};

#include "tapdance.c"


enum custom_keycodes {
    GITHUB,
    SPC_MOUS,
    VU,
};

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

void send_int(uint16_t num) {
  char *str = "error";
  itoa(num, str, 10);
  send_string(str);
}

/**
 * https://beta.docs.qmk.fm/using-qmk/guides/custom_quantum_functions
*/
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  keypos_t pos = record->event.key;
  switch(keycode) {
    case GITHUB:
      if (record->event.pressed) {
        SEND_STRING("https://github.com");
      }
      break;
    case VU:
      if (record->event.pressed) {
        SEND_STRING("Vu Vu Vu!");
      }
      break;
    case SPC_MOUS: // Tap for space, enable mouse layer when held
      if (record->event.pressed) {
        layer_on(MOUS);
      } else {
        const uint16_t last_timestamp = LAST_KEY_TIMESTAMPS[pos.row][pos.col];
        int time = record->event.time - last_timestamp;
        if (time < 200) {
          tap_code(KC_SPC);
        }
        layer_off(MOUS);
      }
      break;
  }

  LAST_KEY_TIMESTAMPS[pos.row][pos.col] = record->event.time;
  return true;
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

[BASE] = LAYOUT(
  TD(ESC_LT), KC_F1,   KC_F2,   KC_F3,    KC_F4,    KC_F5,  KC_F6,   KC_F7,   KC_F8,         KC_F9,    KC_F10,  KC_F11,  KC_F12,  KC_F9,    KC_F10,  KC_F11,  KC_F12,  KC_DEL,
  KC_GRV,     KC_1,    KC_2,    KC_3,     KC_4,     KC_5,   KC_6,    KC_7,    KC_8,          _______,  KC_9,    KC_0,    KC_MINS, KC_EQUAL, _______, KC_MINS, KC_BSPC, KC_BSPC,
  KC_TAB,     KC_Q,    KC_W,    KC_E,     KC_R,     KC_T,   KC_VOLD, KC_VOLU, PLAY,          KC_PGUP,  KC_LBRC, KC_RBRC, KC_Y,    KC_U,     KC_I,    KC_O,    KC_P,    KC_BSLS,
  KC_LCTL,    KC_A,    KC_S,    KC_D,     KC_F,     KC_G,   KC_F2,   KC_F12,  KC_HOME,       KC_PGDN,  KC_UP,   KC_LSFT, KC_H,    KC_J,     KC_K,    KC_L,    KC_SCLN, KC_QUOT,
  KC_LSFT,    KC_Z,    KC_X,    KC_C,     KC_V,     KC_B,   WS_LEFT, WS_RIGH, KC_END,        KC_LEFT,  KC_DOWN, KC_RGHT, KC_N,    KC_M,     KC_COMM, KC_DOT,  KC_UP,   KC_SLSH,
  KC_LCTL,    KC_LGUI, KC_LALT, MO(MDIA), SPC_MOUS, KC_SPC, KC_ENT,  VU,      GITHUB,        KC_PSCR,  _______,  KC_ENT,  KC_ENT,  KC_RGUI,  MO(MDIA),KC_LEFT, KC_DOWN, KC_RIGHT
),

[OSX] = LAYOUT(
  _______, _______, _______, _______, _______, _______, _______, _______, _______,     _______, _______, _______, _______, _______, _______, _______, _______, _______,
  _______, _______, _______, _______, _______, _______, _______, _______, _______,     _______, _______, _______, _______, _______, _______, _______, _______, _______,
  _______, _______, _______, _______, _______, _______, _______, _______, _______,     _______, _______, _______, _______, _______, _______, _______, _______, _______,
  KC_LGUI, _______, _______, _______, _______, _______, _______, _______, _______,     _______, _______, _______, _______, _______, _______, _______, _______, _______,
  _______, _______, _______, _______, _______, _______, OSX_WSL, OSX_WSR, _______,     _______, _______, _______, _______, _______, _______, _______, _______, _______,
  _______, _______, _______, _______, _______, _______, _______, _______, _______,     _______, _______, _______, _______, _______, _______, _______, _______, _______
),

[MDIA] = LAYOUT(
  _______, _______, _______, _______,  _______, _______, _______, _______, _______,     _______, _______, _______, _______, _______, _______, _______, _______, _______,
  _______, _______, _______, _______,  _______, _______, _______, _______, _______,     _______, _______, _______, _______, _______, _______, _______, _______, _______,
  _______, _______, KC_UP,   _______,  _______, _______, _______, _______, _______,     _______, _______, _______, _______, _______, _______, _______, _______, _______,
  KC_PGUP, KC_LEFT, KC_DOWN, KC_RIGHT, _______, _______, _______, _______, _______,     _______, _______, _______, _______, _______, _______, _______, _______, _______,
  KC_PGDN, _______, _______, _______,  _______, _______, _______, _______, _______,     _______, _______, _______, _______, _______, _______, _______, KC_VOLU, _______,
  _______, _______, _______, _______,  _______, _______, _______, _______, _______,     _______, _______, _______, PLAY,    _______, PLAY,    KC_MRWD, KC_VOLD, KC_MFFD
),

[MOUS] = LAYOUT(
  _______, _______, _______, _______,  _______, _______, _______, _______, _______,     _______, _______, _______, _______, _______, _______, _______, _______, _______,
  _______, _______, _______, _______,  _______, _______, _______, _______, _______,     _______, _______, _______, _______, _______, _______, _______, _______, _______,
  _______, _______, KC_MS_U, _______,  _______, _______, _______, _______, _______,     _______, _______, _______, _______, _______, _______, KC_MS_U, _______, _______,
  KC_WH_U, KC_MS_L, KC_MS_D, KC_MS_R,  _______, _______, _______, _______, _______,     _______, _______, _______, _______, _______, KC_MS_L, KC_MS_D, KC_MS_R, KC_WH_U,
  KC_WH_D, _______, _______, _______,  _______, _______, _______, _______, _______,     _______, _______, _______, _______, _______, _______, _______, _______, KC_WH_D,
  _______, _______, _______, _______,  _______, KC_BTN1, KC_BTN2, _______, _______,     _______, _______, _______, KC_BTN1, KC_BTN2, _______, _______, _______, _______
),
};
