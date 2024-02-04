#include <stdlib.h>

#include "engine.h"
#include "midi.h"

engine engine_create(const unsigned short polyphony) {
    engine instance = malloc(sizeof(engine_t));
    if (instance) {
        instance->polyphony = polyphony;
        instance->voices = list_create(polyphony, sizeof(voice_t));
        instance->voice_mixer = mixer_create(polyphony);
        instance->active_midi_notes = list_create(polyphony, sizeof(note_t));
    }

    return instance;
};

void engine_destroy(engine instance) {
    list_destroy(instance->voices);
    list_destroy(instance->active_midi_notes);
    mixer_destroy(instance->voice_mixer);
    free(instance);
};