/*
Copyright 2019 @foostan
Copyright 2020 Drashna Jaelre <@drashna>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include QMK_KEYBOARD_H
#include <stdio.h>

#define altT(x)    LALT_T(x)
#define shiftT(x) LSFT_T(x)
#define ctrlT(x)  LCTL_T(x)

#define UNDO    G(KC_Z)
#define CUT     G(KC_X)
#define COPY    G(KC_C)
#define PASTE   G(KC_V)
#define PREVAPP SGUI(KC_TAB)
#define NEXTAPP G(KC_TAB)
#define PREVTAB S(KC_TAB)
#define NEXTTAB KC_TAB

enum layers {
    _default = 0,
    _right,
    _left,
    _keypad,
    _function,
    _hold,
    _debug,
    _blank
};

enum tapdancers {
    T_BR = 0, // [, ]
    T_PA, // (, )
    T_CU, // {, }
    T_SL, // slash, backslash
    T_COMM, // comma, dash
};

// Tap Dance Definitions
//
qk_tap_dance_action_t tap_dance_actions[] = {
    [T_BR] = ACTION_TAP_DANCE_DOUBLE(KC_LBRC, KC_RBRC),
    [T_PA] = ACTION_TAP_DANCE_DOUBLE(KC_LPRN, KC_RPRN),
    [T_CU] = ACTION_TAP_DANCE_DOUBLE(KC_LCBR, KC_RCBR),
    [T_SL] = ACTION_TAP_DANCE_DOUBLE(KC_SLSH, KC_BSLS),

    [T_COMM] = ACTION_TAP_DANCE_DOUBLE(KC_COMM, KC_MINS)
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

////////////////////////////////////////////////////////////////////////////////
// DEFAULT
////////////////////////////////////////////////////////////////////////////////

[_default] = LAYOUT_split_3x6_3(
KC_TAB,         KC_Q,  KC_W,  KC_F,  KC_P,  KC_G,  /**/  KC_J,  KC_L,  KC_U,        KC_Y,    KC_SCLN,  XXXXXXX,
ctrlT(KC_ESC),  KC_A,  KC_R,  KC_S,  KC_T,  KC_D,  /**/  KC_H,  KC_N,  KC_E,        KC_I,    KC_O,     KC_QUOT,
KC_LSPO,        KC_Z,  KC_X,  KC_C,  KC_V,  KC_B,  /**/  KC_K,  KC_M,  TD(T_COMM),  KC_DOT,  KC_SLSH, KC_RSPC,

KC_LGUI, OSL(_left),  altT(KC_ENT),    altT(KC_SPC), OSL(_right), KC_RGUI // TO(_debug),
),

////////////////////////////////////////////////////////////////////////////////
// QUICK
////////////////////////////////////////////////////////////////////////////////

[_right] = LAYOUT_split_3x6_3(
// want {} [] &* @! := |....*
// maybe - _ : ;
KC_GRV,   KC_EXLM,  KC_AT,     KC_HASH,  KC_DLR,   KC_PERC,    /**/  KC_CIRC,  KC_AMPR,  KC_ASTR,  KC_9,  KC_EQL,  TO(_default),
XXXXXXX,  KC_SCLN,  KC_COLON,  KC_LCBR,  KC_RCBR,  TO(_right), /**/  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  KC_BSLS,
_______,  KC_EXLM,  XXXXXXX,   KC_LBRC,  KC_RBRC,  TO(_left),  /**/  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  _______,

_______,  _______,  KC_MINS,  /**/  KC_MINS,  _______,  _______
),

////////////////////////////////////////////////////////////////////////////////
// NAVIGATION
////////////////////////////////////////////////////////////////////////////////

[_left] = LAYOUT_split_3x6_3(
// arrows home end pgup pgdn M-tab C-tab C-S-tab cmd-[ cmd-]
XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  /**/  KC_HOME,  KC_PGUP,  KC_PGDN,  KC_END,   XXXXXXX, TO(_default),
KC_LCTL,  XXXXXXX,  XXXXXXX,  XXXXXXX,  KC_BSPC,  KC_DEL,  /**/   KC_1,     KC_2,     KC_3,     KC_4,     KC_5,    _______,
KC_LSFT,  UNDO,     CUT,      COPY,     PASTE,    XXXXXXX,  /**/  KC_6,     KC_7,     KC_8,     KC_9,     KC_0,    _______,

_______,  _______,  _______,  /**/      _______,  _______,  _______
),

////////////////////////////////////////////////////////////////////////////////
// KEYPAD
////////////////////////////////////////////////////////////////////////////////

[_keypad] =
LAYOUT_split_3x6_3(
XXXXXXX,  XXXXXXX,  XXXXXXX,  OSL(_function),  XXXXXXX,  XXXXXXX,  /**/  KC_COLN,    KC_P7,  KC_P8,  KC_P9,  KC_KP_PLUS,      TO(_default),
XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,         XXXXXXX,  TO(_keypad),  /**/  KC_KP_DOT,  KC_P4,  KC_P5,  KC_P6,  KC_KP_MINUS,     KC_KP_SLASH,
XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,         XXXXXXX,  XXXXXXX,  /**/  KC_P0,      KC_P1,  KC_P2,  KC_P3,  KC_KP_ASTERISK,  KC_KP_ENTER,

XXXXXXX,  _______,  XXXXXXX,  /**/  XXXXXXX,  _______,  XXXXXXX
),

////////////////////////////////////////////////////////////////////////////////
// FUNCTION
////////////////////////////////////////////////////////////////////////////////

[_function] =
LAYOUT_split_3x6_3(
XXXXXXX,        XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  /**/     KC_F12,  KC_F7,  KC_F8,  KC_F9,  XXXXXXX,  TO(_default),
ctrlT(KC_ESC),  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  TO(_function),  /**/     KC_F11,  KC_F4,  KC_F5,  KC_F6,  XXXXXXX,  XXXXXXX,
KC_LSFT,        XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  /**/     KC_F10,  KC_F1,  KC_F2,  KC_F3,  XXXXXXX,  XXXXXXX,

KC_LGUI,  _______,  KC_LALT,  /**/  XXXXXXX,  _______,  XXXXXXX
),

// test   !=!==!=  ==!=!=!=
/*2NNrstpppp    \|    ls -1 |1211355iin12354654:
  300300300300300:=;ientsier;nreistnierstn;resti rt rest     rsntirnst;neirnstienisr:= rnsterisnt{}  []  #$^@!:!z
  if v, ok rx;={[;=;={[;=;=rx;=;=;=;r{}]{}};{;{;{{}{}{}arx;:riestnrse:rnsietrs:;nrstiet;:'

  2002  2020 2022-03-09
  [_right] = LAYOUT_split_6_()  bbbb bbbbbbb200200    bb bbb bbb
 */

// tap dance does not work with OSL
//}{}   {{c{c

[_hold] = LAYOUT_split_3x6_3(
XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  TD(T_PA),  KC_G,  /**/  XXXXXXX,  XXXXXXX,  KC_UNDS,  XXXXXXX,  XXXXXXX,  TO(_default),
XXXXXXX,  XXXXXXX,  XXXXXXX,  TD(T_SL),  XXXXXXX,  KC_MINS,  /**/  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,
XXXXXXX,  XXXXXXX,  XXXXXXX,  TD(T_CU),  XXXXXXX,  TD(T_BR),  /**/  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,
XXXXXXX,  XXXXXXX,  XXXXXXX,  /**/  XXXXXXX,  XXXXXXX,  XXXXXXX
),

[_debug] = LAYOUT_split_3x6_3(
  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  /**/  XXXXXXX,  DT_UP,     XXXXXXX,  XXXXXXX,  XXXXXXX,  TO(_default),
  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  /**/  XXXXXXX,  DT_PRNT,   XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,
  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  /**/  XXXXXXX,  DT_DOWN,   XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,

  XXXXXXX,  XXXXXXX,  XXXXXXX,  /**/  XXXXXXX,  XXXXXXX,  XXXXXXX
  ),

[_blank] = LAYOUT_split_3x6_3(
  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  /**/  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  TO(_default),
  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  /**/  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,
  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  /**/  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,
  XXXXXXX,  XXXXXXX,  XXXXXXX,  /**/  XXXXXXX,  XXXXXXX,  XXXXXXX
 ),
};


/*

  Leaders don't work for fast typing, maybe for macros
LEADER_EXTERNS();

void matrix_scan_user(void) {
    LEADER_DICTIONARY() {
        leading = false;
        leader_end();

        SEQ_ONE_KEY(KC_SPC) {
            SEND_STRING("-");
        }
        SEQ_ONE_KEY(KC_ENT) {
            SEND_STRING("_");
        }
        SEQ_TWO_KEYS(KC_A, KC_S) {
            register_code(KC_LGUI);
            register_code(KC_S);
            unregister_code(KC_S);
            unregister_code(KC_LGUI);
        }
    }
}

*/
