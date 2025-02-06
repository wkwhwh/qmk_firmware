#include "midi.h"
#include "quantum/midi/qmk_midi.h"

extern MidiDevice midi_device;

bool process_midi_cc_keycode(uint16_t keycode, keyrecord_t *record) {
    uint8_t cc_number;

    // Convert keycode to CC number (1-based)
    if (keycode >= MI_CC1 && keycode <= MI_CC30) {
        cc_number = keycode - MI_CC1 + 1;

        if (record->event.pressed) {
            midi_send_cc(&midi_device, midi_config.channel, cc_number, MIDI_CC_ON);
        } else {
            midi_send_cc(&midi_device, midi_config.channel, cc_number, MIDI_CC_OFF);
        }
        return true;
    }
    return false;
}
