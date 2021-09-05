#include QMK_KEYBOARD_H
#include "keycodes.c"

// Custom Macros
#define PLAY KC_MEDIA_PLAY_PAUSE
#define CTL_APP LCTL_T(KC_APP)

#define LIN_WSL LCA(KC_LEFT)
#define LIN_WSR LCA(KC_RIGHT)
#define LIN_WSU KC_LGUI
#define LIN_SNL LGUI(KC_LEFT)
#define LIN_SNR LGUI(KC_RIGHT)
#define OSX_WSL LCTL(KC_LEFT)
#define OSX_WSR LCTL(KC_RIGHT)
#define OSX_WSU LCTL(KC_UP)
#define OSX_SNL LCA(KC_LEFT)
#define OSX_SNR LCA(KC_RIGHT)

#define SS_LINU LSFT(LCTL(KC_PSCR))
#define SS_OSX LSG(KC_4)

enum layers {
    BASE,  // default layer
    OSX,   // symbols
    MDIA,  // media keys
    MOUS,  // mouse keys
};

#include "tapdance.c"
#include "macros.c"


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

[BASE] = LAYOUT(
  TD(ESC_LT), KC_F1,   KC_F2,   KC_F3,    KC_F4,  KC_F5,   KC_F6,    KC_F7,   KC_F8,         CU_GITHUB, CU_VU,    TD(TD_DEB), XXXXXXX,  KC_F9,  KC_F10,  KC_F11,  KC_F12,   KC_DEL,
  KC_GRV,     KC_1,    KC_2,    KC_3,     KC_4,   KC_5,    KC_6,     KC_VOLD, KC_VOLU,       LIN_SNL,   LIN_SNR,  KC_7,       KC_8,     KC_9,   KC_0,    KC_MINS, KC_EQUAL, KC_BSPC,
  KC_TAB,     KC_Q,    KC_W,    KC_E,     KC_R,   KC_T,    KC_LBRC,  XXXXXXX, PLAY,          KC_PGUP,   LIN_WSU,  KC_RBRC,    KC_Y,     KC_U,   KC_I,    KC_O,    KC_P,     KC_BSLS,
  KC_LCTL,    KC_A,    KC_S,    KC_D,     KC_F,   KC_G,    KC_F2,    KC_F12,  KC_HOME,       KC_PGDN,   XXXXXXX,  XXXXXXX,    KC_H,     KC_J,   KC_K,    KC_L,    KC_SCLN,  KC_QUOT,
  KC_LSFT,    KC_Z,    KC_X,    KC_C,     KC_V,   KC_B,    LIN_WSL,  LIN_WSR, KC_END,        LIN_WSL,   LIN_WSR,  KC_SLSH,    KC_N,     KC_M,   KC_COMM, KC_DOT,  KC_UP,    TD(CMD_SHIFT),
  KC_LCTL,    KC_LGUI, KC_LALT, MO(MDIA), KC_SPC, XXXXXXX, MO(MOUS), CU_KVM,  KC_DEL,        SS_LINU,   MO(MOUS), CU_ENT_MED, XXXXXXX,  KC_ENT, CTL_APP, KC_LEFT, KC_DOWN,  KC_RGHT
),

[OSX] = LAYOUT(
  _______, _______, _______, _______, _______, _______, _______, _______, _______,     _______, _______, _______, _______, _______, _______, _______, _______, _______,
  _______, _______, _______, _______, _______, _______, _______, _______, _______,     OSX_SNL, OSX_SNR, _______, _______, _______, _______, _______, _______, _______,
  _______, _______, _______, _______, _______, _______, _______, _______, _______,     _______, OSX_WSU, _______, _______, _______, _______, _______, _______, _______,
  KC_LGUI, _______, _______, _______, _______, _______, _______, _______, _______,     _______, _______, _______, _______, _______, _______, _______, _______, _______,
  _______, _______, _______, _______, _______, _______, OSX_WSL, OSX_WSR, _______,     OSX_WSL, OSX_WSR, _______, _______, _______, _______, _______, _______, _______,
  _______, _______, _______, _______, _______, XXXXXXX, _______, _______, _______,     SS_OSX,  _______, _______, XXXXXXX, _______, _______, _______, _______, _______
),

[MDIA] = LAYOUT(
  _______, _______, _______, _______,  _______, _______, _______, _______, _______,     _______, _______, _______, _______, _______, _______, _______, _______, _______,
  _______, _______, _______, _______,  _______, _______, _______, KC_MPRV, KC_MNXT,     _______, _______, _______, _______, _______, _______, _______, _______, _______,
  _______, _______, KC_UP,   _______,  _______, _______, _______, _______, _______,     _______, _______, _______, _______, _______, _______, KC_UP,  _______,  _______,
  KC_PGUP, KC_LEFT, KC_DOWN, KC_RIGHT, _______, _______, _______, _______, _______,     _______, _______, _______, _______, _______, KC_LEFT, KC_DOWN, KC_RIGHT,_______,
  KC_PGDN, _______, _______, _______,  _______, _______, _______, _______, _______,     _______, _______, _______, _______, _______, _______, _______, KC_VOLU, _______,
  _______, _______, _______, _______,  _______, XXXXXXX, _______, _______, KC_BSPC,     _______, _______, _______, XXXXXXX, _______, PLAY,    _______, KC_VOLD, _______
),

[MOUS] = LAYOUT(
  _______, _______, _______, _______,  _______, _______, _______, _______, _______,     _______, _______, _______, _______, _______, _______, _______, _______, _______,
  _______, _______, _______, _______,  _______, _______, _______, _______, _______,     _______, _______, _______, _______, _______, _______, _______, _______, _______,
  _______, _______, KC_MS_U, _______,  _______, _______, _______, _______, _______,     _______, _______, _______, _______, _______, _______, KC_MS_U, _______, _______,
  KC_WH_U, KC_MS_L, KC_MS_D, KC_MS_R,  _______, _______, _______, _______, _______,     _______, _______, _______, _______, _______, KC_MS_L, KC_MS_D, KC_MS_R, KC_WH_U,
  KC_WH_D, _______, _______, _______,  _______, _______, _______, _______, _______,     _______, _______, _______, _______, _______, _______, _______, _______, KC_WH_D,
  _______, _______, _______, _______,  KC_BTN1, XXXXXXX, KC_BTN1, KC_BTN2, KC_BSPC,     _______, _______, _______, XXXXXXX, KC_BTN1, KC_BTN2, _______, _______, _______
),
};
