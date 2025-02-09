#ifndef __SNW_ENGINE_H
#define __SNW_ENGINE_H

#include "list.h"
#include "midi.h"
#include "mixer.h"
#include "voice.h"

#define __SW_ENGINE_POLYPHONY_POS = 0
#define __SW_ENGINE_SAMPLESIZE_POS = 1

typedef struct {
    unsigned short polyphony;
    unsigned short sample_size;
    mixer voice_mixer;
    list voices;
} engine_t;

typedef engine_t* engine;

engine engine_create (const unsigned short polyphony, const unsigned short sample_size);
void engine_destroy (engine);
void engine_add_active_note (engine, note n);
void engine_remove_active_note (engine, note n);
void engine_set_voice_state_attr (engine, const unsigned short index, voice_state_attr, voice_state_value);
void engine_set_voice_state (engine, const unsigned short index, voice_state state);
const voice_state engine_get_voice_state (engine, const unsigned short index);
// void engine_set_cc(engine, unsigned short cc, unsigned short value);
void engine_process (engine, short* out, unsigned short out_size);
short engine_out (engine);
size_t engine_calc_size (const unsigned short polyphony, const unsigned short sample_size);

#endif
