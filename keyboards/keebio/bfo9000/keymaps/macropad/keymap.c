#include QMK_KEYBOARD_H
#include "keycodes.c"

// Custom Macros
#define PLAY KC_MEDIA_PLAY_PAUSE

#define DB_STRT KC_F5
#define DB_PLAY KC_F5
#define DB_STEP KC_F10
#define DB_IN KC_F11
#define DB_OUT LSFT(KC_F11)

enum layers {
    BASE,  // default layer
    OSX,   // symbols
};

#include "tapdance.c"
#include "macros.c"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

[BASE] = LAYOUT(
  KC_PWR,   TO(BASE), TO(OSX), _______, _______, _______, KC_VOLD, KC_VOLU, PLAY,           _______, _______, _______, _______, _______, _______, _______, _______, _______,
  KC_SLEP,  _______,  _______, _______, _______, _______, CU_SNPL, CU_SNPR, _______,        _______, _______, _______, _______, _______, _______, _______, _______, _______,
  CU_SCRN,  _______,  CU_GHUB, CU_GMAL, CU_YTUB, _______, CU_WSPL, CU_WSPR, CU_DASH,        _______, _______, _______, _______, _______, _______, _______, _______, _______,
  _______,  _______,  _______, _______, _______, DB_STRT, _______, _______, _______,        _______, _______, _______, _______, _______, _______, _______, _______, _______,
  CU_CODE,  CU_CHRM,  CU_STEM, CU_OBS,  CU_DSCD, _______, DB_PLAY, DB_STEP, _______,        _______, _______, _______, _______, _______, _______, _______, _______, _______,
  _______,  _______,  _______, _______, _______, _______, DB_IN,   DB_OUT, _______,        _______, _______, _______, _______, _______, _______, _______, _______, _______
),

[OSX] = LAYOUT(
  _______, _______, _______, _______, _______, _______, _______, _______, _______,       _______, _______, _______, _______, _______, _______, _______, _______, _______,
  _______, _______, _______, _______, _______, _______, _______, _______, _______,       _______, _______, _______, _______, _______, _______, _______, _______, _______,
  _______, _______, _______, _______, _______, _______, _______, _______, _______,       _______, _______, _______, _______, _______, _______, _______, _______, _______,
  _______, _______, _______, _______, _______, _______, _______, _______, _______,       _______, _______, _______, _______, _______, _______, _______, _______, _______,
  _______, _______, _______, _______, _______, _______, _______, _______, _______,       _______, _______, _______, _______, _______, _______, _______, _______, _______,
  _______, _______, _______, _______, _______, _______, _______, _______, _______,       _______, _______, _______, _______, _______, _______, _______, _______, _______
),
};
