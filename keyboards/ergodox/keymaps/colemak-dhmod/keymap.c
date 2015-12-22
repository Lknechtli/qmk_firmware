#include "ergodox.h"
#include "debug.h"
#include "action_layer.h"

#define BASE 0 // default layer
#define QWER 1 // querty layer
#define KEYP 2 // Keypad
#define MDIA 3 // media and symbol keys

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* Keymap 0: Basic layer
 * http://colemakmods.github.io/mod-dh/#matrix-keyboards
 * see link for rational re the letter swaps
 * ┌────────┬─────┬─────┬─────┬─────┬─────┬─────┐     ┌─────┬─────┬─────┬─────┬─────┬─────┬────────┐
 * │   =+   │ 1!  │ 2@  │ 3#  │ 4$  │ 5%  │  L1 │     │ L2  │ 6^  │ 7&  │ 8*  │ 9(  │ 0)  │ -_     │
 * ├────────┼─────┼─────┼─────┼─────┼─────┼─────┤     ├─────┼─────┼─────┼─────┼─────┼─────┼────────┤
 * │ Tab    │  Q  │  W  │  F  │  P  │  B  │ Home│     │ End │  J  │  L  │  U  │  Y  │ ;:  │ \|     │
 * ├────────┼─────┼─────┼─────╆─────╅─────┤     │     │     ├─────╆─────╅─────┼─────┼─────┼────────┤
 * │ Esc/L3 │  A  │  R  │  S  │  T  │  G  ├─────┤     ├─────┤  M  │  N  │  E  │  I  │  O  │ '"     │
 * ├────────┼─────┼─────┼─────╄─────╃─────┤Hyper│     │ Meh ├─────╄─────╃─────┼─────┼─────┼────────┤
 * │  L⇧/(  │  Z  │  X  │  C  │  D  │  V  │ [{  │     │ ]}  │  K  │  H  │  ,  │  .  │//Ctl│  R⇧/)  │
 * └─┬──────┼─────┼─────┼─────┼─────┼─────┴─────┘     └─────┴─────┼─────┼─────┼─────┼─────┼─────┬──┘
 *   │`/Ctl │ Alt │  ←  │  →  │ Esc │                             │  ↓  │  ↑  │  {  │  }  │ Ctl │
 *   └──────┴─────┴─────┴─────┴─────┘ ┌─────┬─────┐ ┌─────┬─────┐ └─────┴─────┴─────┴─────┴─────┘
 *                                    │ App │  ~  │ │ Prsc│ Play│
 *                              ┌─────┼─────┼─────┤ ├─────┼─────┼─────┐
 *                              │     │     │ Home│ │ PgUp│     │     │
 *                              │ SPC │LGui ├─────┤ ├─────┤ Ent │  ⌫  │
 *                              │ ~L⇧ │     │ End │ │ PgDn│     │     │
 *                              └─────┴─────┴─────┘ └─────┴─────┴─────┘
 */
// If it accepts an argument (i.e, is a function), it doesn't need KC_.
// Otherwise, it needs KC_*
[BASE] = KEYMAP(  // layer 0 : default
        // left hand
        KC_EQL,        KC_1,    KC_2,    KC_3,    KC_4,   KC_5, TG(QWER),
        KC_TAB,        KC_Q,    KC_W,    KC_F,    KC_P,   KC_B, KC_HOME,
   LT(KC_FN3,KC_ESC),  KC_A,    KC_R,    KC_S,    KC_T,   KC_G,
        KC_LSPO,  CTL_T(KC_Z),  KC_X,    KC_C,    KC_D,   KC_V, ALL_T(KC_LBRC),
        KC_LCTL,       KC_LALT, KC_LEFT, KC_RGHT, KC_ESC,
                                                          ALT_T(KC_APP),  KC_TILD,
                                                                          KC_HOME,
                                                   KC_SPC, KC_LGUI,        KC_END,
        // right hand
             TG(KEYP),    KC_6,   KC_7,   KC_8,   KC_9,   KC_0,             KC_MINS,
               KC_END,    KC_J,   KC_L,   KC_U,   KC_Y,   KC_SCLN,          KC_BSLS,
                          KC_M,   KC_N,   KC_E,   KC_I,   KC_O,             KC_QUOT,
        MEH_T(KC_RBRC),   KC_K,   KC_H,   KC_COMM,KC_DOT, CTL_T(KC_SLSH),   KC_RSPC,
                                  KC_DOWN,  KC_UP,KC_LBRC,KC_RBRC,          KC_RCTL,
             KC_PSCR, KC_MPLY,
             KC_PGUP,
             KC_PGDN,KC_ENT, KC_BSPC
    ),
/* Keymap 1: Basic QWERY layer (for gaming)
 *
 * ┌───────┬─────┬─────┬─────┬─────┬─────┬─────┐     ┌─────┬─────┬─────┬─────┬─────┬─────┬───────┐
 * │       │     │     │     │     │     │     │     │     │     │     │     │     │     │       │
 * ├───────┼─────┼─────┼─────┼─────┼─────┼─────┤     ├─────┼─────┼─────┼─────┼─────┼─────┼───────┤
 * │       │     │     │  E  │  R  │  T  │     │     │     │  Y  │  U  │  I  │  O  │  P  │       │
 * ├───────┼─────┼─────┼─────╆─────╅─────┤     │     │     ├─────╆─────╅─────┼─────┼─────┼───────┤
 * │       │     │  S  │  D  │  F  │     ├─────┤     ├─────┤  H  │  J  │  K  │  L  │  ;  │       │
 * ├───────┼─────┼─────┼─────╄─────╃─────┤     │     │     ├─────╄─────╃─────┼─────┼─────┼───────┤
 * │       │     │     │     │  V  │  B  │     │     │     │  N  │  M  │     │     │     │       │
 * └─┬─────┼─────┼─────┼─────┼─────┼─────┴─────┘     └─────┴─────┼─────┼─────┼─────┼─────┼─────┬─┘
 *   │     │     │     │     │ Tab │                             │     │     │     │     │     │
 *   └─────┴─────┴─────┴─────┴─────┘ ┌─────┬─────┐ ┌─────┬─────┐ └─────┴─────┴─────┴─────┴─────┘
 *                                   │     │     │ │     │     │
 *                             ┌─────┼─────┼─────┤ ├─────┼─────┼─────┐
 *                             │     │     │     │ │     │     │     │
 *                             │     │     ├─────┤ ├─────┤     │     │
 *                             │     │     │     │ │     │     │     │
 *                             └─────┴─────┴─────┘ └─────┴─────┴─────┘
 */
// If it accepts an argument (i.e, is a function), it doesn't need KC_.
// Otherwise, it needs KC_*
[QWER] = KEYMAP(  // layer 3 : default
        // left hand
        KC_TRNS,KC_TRNS,  KC_TRNS,   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS,KC_TRNS,  KC_TRNS,   KC_E,    KC_R,    KC_T,    KC_TRNS,
        KC_TRNS,KC_TRNS,  KC_S,      KC_D,    KC_F,    KC_TRNS,
        KC_TRNS,KC_TRNS,  KC_TRNS,   KC_TRNS, KC_V,    KC_B,    KC_TRNS,
        KC_TRNS,KC_TRNS,  KC_TRNS,   KC_TRNS, KC_TAB,
                                                       KC_TRNS, KC_TRNS,
                                                                KC_TRNS,
                                               KC_TRNS,KC_TRNS, KC_TRNS,
        // right hand
             KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,          KC_TRNS,
             KC_TRNS, KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,             KC_TRNS,
                      KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN,          KC_TRNS,
             KC_TRNS, KC_N,    KC_M,    KC_TRNS, KC_TRNS, KC_TRNS,          KC_TRNS,
                               KC_TRNS, KC_TRNS, KC_TRNS, KC_RBRC,          KC_TRNS,
             KC_TRNS, KC_TRNS,
             KC_TRNS,
             KC_TRNS, KC_TRNS, KC_TRNS
    ),
/* Keymap 2: Keypad Layer
 *
 * ┌───────┬─────┬─────┬─────┬─────┬─────┬─────┐     ┌─────┬─────┬─────┬─────┬─────┬─────┬───────┐
 * │       │     │     │     │     │     │     │     │     │     │ NLCK│  K/ │  K* │  K- │   =   │
 * ├───────┼─────┼─────┼─────┼─────┼─────┼─────┤     ├─────┼─────┼─────┼─────┼─────┼─────┼───────┤
 * │       │ PgUp│  ⌫  │  ↑  │  ⌦  │ PgDn│     │     │     │     │  K7 │  K8 │  K9 │  K+ │   #   │
 * ├───────┼─────┼─────┼─────╆─────╅─────┤     │     │     ├─────╆─────╅─────┼─────┼─────┼───────┤
 * │       │ Home│  ←  │  ↓  │  →  │ End ├─────┤     ├─────┤     │  K4 │  K5 │  K6 │  K+ │       │
 * ├───────┼─────┼─────┼─────╄─────╃─────┤     │     │     ├─────╄─────╃─────┼─────┼─────┼───────┤
 * │       │ Esc │ Tab │ Ins │ Ret │ Undo│     │     │     │     │  K1 │  K2 │  K3 │  K= │       │
 * └─┬─────┼─────┼─────┼─────┼─────┼─────┴─────┘     └─────┴─────┼─────┼─────┼─────┼─────┼─────┬─┘
 *   │     │     │     │     │     │                             │  K0 │  K0 │  K. │  K= │     │
 *   └─────┴─────┴─────┴─────┴─────┘ ┌─────┬─────┐ ┌─────┬─────┐ └─────┴─────┴─────┴─────┴─────┘
 *                                   │     │     │ │     │     │
 *                             ┌─────┼─────┼─────┤ ├─────┼─────┼─────┐
 *                             │     │     │     │ │     │     │     │
 *                             │     │     ├─────┤ ├─────┤     │     │
 *                             │     │     │     │ │     │     │     │
 *                             └─────┴─────┴─────┘ └─────┴─────┴─────┘
 */
[KEYP] = KEYMAP(
       // left hand
       KC_TRNS,KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS,KC_PGUP, KC_BSPC, KC_UP,   KC_DEL,  KC_PGDN, KC_TRNS,
       KC_TRNS,KC_HOME, KC_LEFT, KC_DOWN, KC_RGHT, KC_END,
       KC_TRNS,KC_ESC,  KC_TAB,  KC_INS,  KC_ENT,  KC_UNDO, KC_TRNS,
       KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
                                       KC_TRNS,KC_TRNS,
                                               KC_TRNS,
                               KC_TRNS,KC_TRNS,KC_TRNS,
       // right hand
       KC_TRNS, KC_TRNS, KC_NLCK, KC_PSLS, KC_PAST, KC_PMNS, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_P7,   KC_P8,   KC_P9,   KC_PPLS, KC_NUHS,
                KC_TRNS, KC_P4,   KC_P5,   KC_P6,   KC_PPLS, KC_SLSH,
       KC_TRNS, KC_TRNS, KC_P1,   KC_P2,   KC_P3,   KC_PENT, KC_DOT,
                         KC_P0,   KC_P0,   KC_PDOT, KC_PENT, KC_TRNS,
       KC_TRNS, KC_TRNS,
       KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS
),
/* Keymap 3: Media and symbol keys
 *
 * ┌───────┬─────┬─────┬─────┬─────┬─────┬─────┐     ┌─────┬─────┬─────┬─────┬─────┬─────┬───────┐
 * │       │ F1  │ F2  │ F3  │ F4  │ F5  │ F11 │     │ F12 │ F6  │ F7  │ F8  │ F9  │ F10 │       │
 * ├───────┼─────┼─────┼─────┼─────┼─────┼─────┤     ├─────┼─────┼─────┼─────┼─────┼─────┼───────┤
 * │       │  !  │  @  │  [  │  ]  │  |  │ Brbk│     │ +Tab│ PgUp│ VOL↑│ VOL↓│ MUTE│     │       │
 * ├───────┼─────┼─────┼─────╆─────╅─────┤     │     │     ├─────╆─────╅─────┼─────┼─────┼───────┤
 * │       │  {  │  }  │  (  │  )  │  `  ├─────┤     ├─────┤  ←  │  ↓  │  ↑  │  →  │     │       │
 * ├───────┼─────┼─────┼─────╄─────╃─────┤ Calc│     │ -Tab├─────╄─────╃─────┼─────┼─────┼───────┤
 * │       │PAUSE│ INS │ PRS │ CAPS│  ~  │     │     │     │ PgDn│Prev │Play │Next │     │       │
 * └─┬─────┼─────┼─────┼─────┼─────┼─────┴─────┘     └─────┴─────┼─────┼─────┼─────┼─────┼─────┬─┘
 *   │     │     │     │     │     │                             │     │     │     │     │     │
 *   └─────┴─────┴─────┴─────┴─────┘ ┌─────┬─────┐ ┌─────┬─────┐ └─────┴─────┴─────┴─────┴─────┘
 *                                   │     │     │ │     │     │
 *                             ┌─────┼─────┼─────┤ ├─────┼─────┼─────┐
 *                             │     │     │     │ │     │     │     │
 *                             │     │     ├─────┤ ├─────┤     │  ⌦  │
 *                             │     │     │     │ │     │     │     │
 *                             └─────┴─────┴─────┘ └─────┴─────┴─────┘
 */
// MEDIA
[MDIA] = KEYMAP(
       KC_TRNS, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F11,
       KC_TRNS, KC_EXLM, KC_AT,   KC_LBRC, KC_RBRC, KC_PIPE, KC_WBAK,
       KC_TRNS, KC_LCBR, KC_RCBR, KC_LPRN, KC_RPRN, KC_GRV,
       KC_TRNS, KC_PAUS, KC_INS,  KC_PSCR, KC_CAPS, KC_TILD, KC_CALC,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                                           KC_TRNS, KC_TRNS,
                                                    KC_TRNS,
                                  KC_TRNS, KC_TRNS, KC_TRNS,
    // right hand
       KC_F12,        KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_TRNS,
       LCTL(KC_PGUP), KC_PGUP, KC_VOLU, KC_VOLD, KC_MUTE, KC_TRNS, KC_TRNS,
                      KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, KC_TRNS, KC_TRNS,
       LCTL(KC_PGDN), KC_PGDN, KC_MPRV, KC_MPLY, KC_MNXT, KC_TRNS, KC_TRNS,
                               KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS,
       KC_TRNS,
       KC_TRNS, KC_TRNS, KC_DEL
),
};

const uint16_t PROGMEM fn_actions[] = {
  [QWER] = ACTION_LAYER_TAP_TOGGLE(QWER),                // FN1 - Momentary Layer 1 (Querty)
  [KEYP] = ACTION_LAYER_TAP_TOGGLE(KEYP),                // FN2 - Momentary Layer 2 (Keypad)
  [MDIA] = ACTION_LAYER_TAP_TOGGLE(MDIA)                // FN3 - Momentary Layer 3 (Media/Symbol)
};

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
  // MACRODOWN only works in this function
      switch(id) {
        case 0:
        if (record->event.pressed) {
          register_code(KC_RSFT);
        } else {
          unregister_code(KC_RSFT);
        }
        break;
      }
    return MACRO_NONE;
};

// Runs just one time when the keyboard initializes.
void matrix_init_user(void) {
  /* ergodox_led_all_on(); */
  /* wait_ms(1000); */
  /* ergodox_led_all_off(); */
};

// Runs constantly in the background, in a loop.
void matrix_scan_user(void) {

    uint8_t layer = biton32(layer_state);

    ergodox_board_led_off();
    ergodox_right_led_1_off();
    ergodox_right_led_2_off();
    ergodox_right_led_3_off();
    switch (layer) {
      // TODO: Make this relevant to the ErgoDox EZ.
        case 1:
            ergodox_right_led_1_on();
            break;
        case 2:
            ergodox_right_led_2_on();
            break;
        default:
            // none
            break;
    }

};
