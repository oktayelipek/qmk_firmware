/*
Copyright 2020 Oktay Elipek

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program. If not, see <http://www.gnu.org/licenses/>.
*/

#include QMK_KEYBOARD_H

//General Definitions
#define LOCKSCREEN LCTL(LSFT(KC_POWER)) // Screen Lock shortcut for OSX

// Figma Componenets
#define CREATECOMPONENT LALT(LGUI(KC_K))    // Create Components
#define SHOWCOMPONENT LALT(KC_KP_2)        // Show Components
#define TEAMLIB LALT(LGUI(KC_O))            // Team Library
#define DETACHO LALT(LGUI(KC_B))             // Detatch Library

// Figma Shortcuts
#define FIGLAYERS LALT(KC_KP_1)            // go to layers
#define SENDBACK LGUI(KC_LBRACKET)          // Send layers to back
#define BRINGFORW LGUI(KC_RBRACKET)         // Send layers to front
#define GRID LCTL(KC_G)                    // Open and close grids.
#define TEXTLEFT LALT(LGUI(KC_L))           // Text Align Left
#define TEXTRIGHT LALT(LGUI(KC_R))          // Text Align Right
#define TEXTCENTER LALT(LGUI(KC_T))         // Text Align Center
#define RUNLASTPLUG LALT(LGUI(KC_P))        // Run last plugin


enum oktiboard_layers {
    _FIGMA,
    _LAB,
    _TEST
};

enum custom_keycodes {
    M_AUTOLAY,
    M_COPYSTYLES
};

bool is_copied = false;
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
    case M_AUTOLAY:
        if(!is_copied) {
            tap_code16(LSFT(KC_A));
            is_copied = true;
        } else {
            tap_code16(LGUI(LSFT(KC_A)));
            is_copied = false;
        }
        break;

    case M_COPYSTYLES:
        if(!is_copied) {
            tap_code16(LGUI(LALT(KC_C)));
            is_copied = true;
        } else {
            tap_code16(LGUI(LALT(KC_V)));
            is_copied = false;
        }
        break;
    }
    return true;
};


layer_state_t layer_state_set_user(layer_state_t state) {
    switch (get_highest_layer(state)) {
    case _FIGMA:
      rgblight_sethsv_noeeprom(HSV_PURPLE);
      break;
    case _LAB:
      rgblight_sethsv_noeeprom(HSV_CORAL);
      break;
    case _TEST:
      rgblight_sethsv_noeeprom(HSV_TEAL);
      break;
  }
  return state;
}


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Figma
 * ,---------------------------.
 * |  CC  |  SC  |  TL  |  DI  |
 * |------+------+------+------|
 * |  LYR |  BF  |  SB  | SHG  |
 * |------+------+------+------|
 * | PLG  | TAL  | TAC  | TAR  |
 * |------+------+------+------|
 * | AUL  |      |  CPS | CHNG |
 * `---------------------------'
 */


[_FIGMA] = LAYOUT_ortho_4x4(
		CREATECOMPONENT, SHOWCOMPONENT, TEAMLIB, DETACHO,
		FIGLAYERS, BRINGFORW, SENDBACK, GRID,
		RUNLASTPLUG, TEXTLEFT, TEXTCENTER, TEXTRIGHT,
		M_AUTOLAY, _______ , M_COPYSTYLES, TO(_LAB)
),

/* Lab
 * ,---------------------------.
 * | FGM  |      |EEP_RS| RESET|
 * |------+------+------+------|
 * |      |AU_ON |AU_OFF|      |
 * |------+------+------+------|
 * |RGB_TG|RGB_VI|RGB_VD|      |
 * |------+------+------+------|
 * | LCK  |      |      | CHNG |
 * `---------------------------'
 */

[_LAB] = LAYOUT_ortho_4x4(
		EEP_RST, RESET , RGB_MODE_KNIGHT ,_______,
		RGB_VAI, _______, RGB_VAD, RGB_TOG,
		RGB_MODE_RAINBOW, RGB_MODE_BREATHE, RGB_MOD, RGB_MODE_PLAIN,
		RGB_MODE_FORWARD, RGB_MODE_RGBTEST, RGB_MODE_GRADIENT, TO(_TEST)
),

/* Emoji
 * ,---------------------------.
 * |  😊  |  😂   |  😁  |   ❤️  |
 * |------+------+------+------|
 * |   😍 |   😊  |  😘  |  👌  |
 * |------+------+------+------|
 * |  👍  |  🙌   |  😢  |  😔  |
 * |------+------+------+------|
 * |  💩  |  😎   |  😉  | CHNG |
 * `---------------------------'
 */

// [_EMOJI] = LAYOUT_ortho_4x4(
//		GRIN, TJOY, SMILE, HEART,
//		EYERT, SMEYE, KISS, OKHND,
//		THMUP, CELEB, CRY2, PENSV,
//		POO, COOL, WINK, TO(_FIGMA)
//),

[_TEST] = LAYOUT_ortho_4x4(
		KC_A, KC_B, KC_C, KC_D,
		KC_E, KC_F, KC_G, KC_H,
		KC_I, KC_J, KC_K, KC_L,
		KC_M, KC_N, KC_O, TO(_FIGMA)
),
};
