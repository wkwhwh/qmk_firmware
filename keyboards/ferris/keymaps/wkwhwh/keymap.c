#include QMK_KEYBOARD_H
#include "oneshot.h"
#include "midi.h"

#define HOME G(KC_LEFT)
#define END G(KC_RGHT)
#define FWD G(KC_RBRC)
#define BACK G(KC_LBRC)
#define AE_TILE A(KC_DOT)
#define AE_ACRD A(KC_COMM)
#define AE_LNCH S(A(KC_QUOT))
#define AE_SRVC S(A(KC_SCLN))
#define LA_SYM MO(SYM)
#define LA_NAV MO(NAV)
#define LA_MI1 TG(MI1)
#define LA_MI2 TG(MI2)
#define LOCK G(C(KC_Q))
#define SLEEPD S(C(KC_PWR))

enum layers {
    DEF,
    SYM,
    NAV,
    NUM,
    MI1,
    MI2,
};

enum keycodes {
    OS_SHFT = NEW_SAFE_RANGE,
    OS_CTRL,
    OS_ALT,
    OS_CMD,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [DEF] = LAYOUT(
        KC_Q,    KC_W,    KC_F,    KC_P,    KC_G,    KC_J,    KC_L,    KC_U,    KC_Y,    KC_QUOT,
        KC_A,    KC_R,    KC_S,    KC_T,    KC_D,    KC_H,    KC_N,    KC_E,    KC_I,    KC_O,
        KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_K,    KC_M,    KC_COMM, KC_DOT,  KC_SCLN,
                                   LA_NAV,  KC_LSFT, KC_SPC,  LA_SYM
    ),
    [SYM] = LAYOUT(
        KC_ESC,  KC_LBRC, KC_LCBR, KC_LPRN, KC_TILD, KC_CIRC, KC_RPRN, KC_RCBR, KC_RBRC, KC_GRV,
        KC_MINS, KC_ASTR, KC_EQL,  KC_UNDS, KC_DLR,  KC_HASH, OS_CMD,  OS_ALT,  OS_SHFT, OS_CTRL,
        KC_PLUS, KC_PIPE, KC_AT,   KC_SLSH, KC_PERC, XXXXXXX, KC_BSLS, KC_AMPR, KC_QUES, KC_EXLM,
                                   _______, _______, _______, _______
    ),
    [NAV] = LAYOUT(
        KC_TAB,  AE_TILE, AE_ACRD, KC_VOLD, KC_VOLU, QK_BOOT, HOME,    KC_UP,   END,     KC_DEL,
        OS_CTRL, OS_SHFT, OS_ALT,  OS_CMD,  KC_MPLY, SLEEPD,  KC_LEFT, KC_DOWN, KC_RGHT, KC_BSPC,
        AE_LNCH, AE_SRVC, BACK,    FWD,     XXXXXXX, LOCK,    KC_PGDN, KC_PGUP, KC_CAPS, KC_ENT,
                                   _______, _______, _______, _______
    ),
    [NUM] = LAYOUT(
        KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,
        OS_CTRL, OS_SHFT, OS_ALT,  OS_CMD,  KC_F11,  KC_F12,  OS_CMD,  OS_ALT,  OS_SHFT, OS_CTRL,
        KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,
                                   _______, _______, _______, _______
    ),
    [MI1] = LAYOUT(
        MI_Db,   MI_Eb,   XXXXXXX, MI_Gb,   MI_Ab,   MI_Bb,   XXXXXXX, MI_Db1,  MI_Eb1,  XXXXXXX,
        MI_C,    MI_D,    MI_E,    MI_F,    MI_G,    MI_A,    MI_B,    MI_C1,   MI_D1,   MI_E1,
        MI_OCTD, MI_OCTU, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, LA_MI1,
                                   _______, _______, _______, _______
    ),
    [MI2] = LAYOUT(
        MI_CC1, MI_CC2, MI_CC3, MI_CC4,  MI_CC5,  MI_CC6,  MI_CC7,  MI_CC8,  MI_CC9,  MI_CC10,
        MI_CC11,MI_CC12,MI_CC13,MI_CC14, MI_CC15, MI_CC16, MI_CC17, MI_CC18, MI_CC19, MI_CC20,
        MI_CC21,MI_CC22,MI_CC23,MI_CC24, MI_CC25, MI_CC26, MI_CC27, MI_CC28, MI_CC29, MI_CC30,
                                   _______, _______, _______, _______
    ),
   };

bool is_oneshot_cancel_key(uint16_t keycode) {
    switch (keycode) {
    case LA_SYM:
    case LA_NAV:
        return true;
    default:
        return false;
    }
}

bool is_oneshot_ignored_key(uint16_t keycode) {
    switch (keycode) {
    case LA_SYM:
    case LA_NAV:
    case KC_LSFT:
    case OS_SHFT:
    case OS_CTRL:
    case OS_ALT:
    case OS_CMD:
        return true;
    default:
        return false;
    }
}

bool sw_win_active = false;
oneshot_state os_shft_state = os_up_unqueued;
oneshot_state os_ctrl_state = os_up_unqueued;
oneshot_state os_alt_state = os_up_unqueued;
oneshot_state os_cmd_state = os_up_unqueued;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (process_midi_cc_keycode(keycode, record)) {
        return true;
    }

    update_oneshot(
        &os_shft_state, KC_LSFT, OS_SHFT,
        keycode, record
    );
    update_oneshot(
        &os_ctrl_state, KC_LCTL, OS_CTRL,
        keycode, record
    );
    update_oneshot(
        &os_alt_state, KC_LALT, OS_ALT,
        keycode, record
    );
    update_oneshot(
        &os_cmd_state, KC_LCMD, OS_CMD,
        keycode, record
    );

    switch (keycode) {
    case KC_LSFT:
        if (record->event.pressed) {
            if (layer_state_is(NAV)) {
                layer_invert(MI1);
                if (layer_state_is(MI2)) layer_off(MI2);
                return false;
            }
        }
        break;
    case KC_SPC:
        if (record->event.pressed) {
            if (layer_state_is(SYM)) {
                layer_invert(MI2);
                if (layer_state_is(MI1)) layer_off(MI1);
                return false;
            }
        }
        break;
    }
    return true;
}

layer_state_t layer_state_set_user(layer_state_t state) {
    return update_tri_layer_state(state, SYM, NAV, NUM);
}
