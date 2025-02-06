#pragma once

#include QMK_KEYBOARD_H
#include "quantum/midi/qmk_midi.h"

#define MIDI_CC_OFF 0
#define MIDI_CC_ON  127

enum custom_keycodes {
    MI_CC1 = SAFE_RANGE,
    MI_CC2,
    MI_CC3,
    MI_CC4,
    MI_CC5,
    MI_CC6,
    MI_CC7,
    MI_CC8,
    MI_CC9,
    MI_CC10,
    MI_CC11,
    MI_CC12,
    MI_CC13,
    MI_CC14,
    MI_CC15,
    MI_CC16,
    MI_CC17,
    MI_CC18,
    MI_CC19,
    MI_CC20,
    MI_CC21,
    MI_CC22,
    MI_CC23,
    MI_CC24,
    MI_CC25,
    MI_CC26,
    MI_CC27,
    MI_CC28,
    MI_CC29,
    MI_CC30,
    NEW_SAFE_RANGE
};

bool process_midi_cc_keycode(uint16_t keycode, keyrecord_t *record);
