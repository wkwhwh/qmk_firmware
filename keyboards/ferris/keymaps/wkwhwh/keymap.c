#include QMK_KEYBOARD_H

#define HOME G(KC_LEFT)
#define END G(KC_RGHT)
#define FWD G(KC_RBRC)
#define BACK G(KC_LBRC)
#define SW_WIN G(KC_GRV)
#define INIT C(S(A(G(KC_I))))
#define EMOJI (C(G(KC_SPACE)))
#define AE_TILE A(KC_DOT)
#define AE_ACRD A(KC_COMM)
#define AE_LNCH S(A(KC_QUOT))
#define AE_SRVC S(A(KC_SCLN))
#define AE_BACK A(KC_LBRC)
#define AE_FWRD A(KC_RBRC)
#define LA_SYM MO(SYM)
#define LA_NAV MO(NAV)

enum layers {
    DEF,
    SYM,
    NAV,
    NUM,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [DEF] = LAYOUT(
        KC_Q,          KC_W,          KC_F,          KC_P,          KC_B,              KC_J,          KC_L,          KC_U,          KC_Y,          KC_QUOT,
        KC_A,          KC_R,          KC_S,          KC_T,          KC_G,              KC_M,          KC_N,          KC_E,          KC_I,          KC_O,
        KC_Z,          KC_X,          KC_C,          KC_D,          KC_V,              KC_K,          KC_H,          KC_COMM,       KC_DOT,        KC_SCLN,
                                                     LA_NAV,        KC_LSFT,           KC_SPC,        LA_SYM
    ),
    [SYM] = LAYOUT(
        KC_ESC,        KC_LBRC,       KC_LCBR,       KC_LPRN,       KC_TILD,           KC_CIRC,       KC_RPRN,       KC_RCBR,       KC_RBRC,       KC_GRV,
        KC_MINS,       KC_ASTR,       KC_EQL,        KC_UNDS,       KC_DLR,            KC_HASH,       OSM(MOD_LGUI), OSM(MOD_LALT), OSM(MOD_LSFT), OSM(MOD_LCTL),
        KC_PLUS,       KC_PIPE,       KC_AT,         KC_SLSH,       KC_PERC,           EMOJI,         KC_BSLS,       KC_AMPR,       KC_QUES,       KC_EXLM,
                                                     _______,       _______,           _______,       _______
    ),
    [NAV] = LAYOUT(
        KC_TAB,        SW_WIN,        AE_BACK,       AE_FWRD,       AE_SRVC,           KC_MPRV,       HOME,          KC_UP,         END,           KC_DEL,
        OSM(MOD_LCTL), OSM(MOD_LSFT), OSM(MOD_LALT), OSM(MOD_LGUI), AE_LNCH,           KC_MNXT,       KC_LEFT,       KC_DOWN,       KC_RGHT,       KC_BSPC,
        AE_TILE,       AE_ACRD,       BACK,          FWD,           INIT,              KC_MPLY,       KC_PGDN,       KC_PGUP,       KC_CAPS,       KC_ENT,
                                                     _______,       _______,           _______,       _______
    ),
    [NUM] = LAYOUT(
        KC_1,          KC_2,          KC_3,          KC_4,          KC_5,              KC_6,          KC_7,          KC_8,          KC_9,          KC_0,
        OSM(MOD_LCTL), OSM(MOD_LSFT), OSM(MOD_LALT), OSM(MOD_LGUI), KC_F11,            KC_F12,        OSM(MOD_LGUI), OSM(MOD_LALT), OSM(MOD_LSFT), OSM(MOD_LCTL),
        KC_F1,         KC_F2,         KC_F3,         KC_F4,         KC_F5,             KC_F6,         KC_F7,         KC_F8,         KC_F9,         KC_F10,
                                                     _______,       _______,           _______,       _______
    ),
};

layer_state_t layer_state_set_user(layer_state_t state) {
    return update_tri_layer_state(state, SYM, NAV, NUM);
}
