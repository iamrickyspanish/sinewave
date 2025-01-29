#include "engine.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//
// unsigned short _engine_get_polyphony(engine e) {
//     return (unsigned short)e;
// };

// void _engine_set_polyphony(engine e, unsigned short polyphony) {
//     memcpy(e, polyphony, sizeof(unsigned short));
// }

// unsigned short _engine_get_sample_size(engine e) {
//     return (unsigned short)e+sizeof(unsigned short);
// };

// void _engine_set_sample_size(engine e, const unsigned short size) {
//     memcpy(e+sizeof(unsigned short), size, sizeof(unsigned short));
// }

// list _engine_get_voice_list(engine e) {
//     return (list)e+2*sizeof(unsigned short);
// }

// void _engine_set_voice_list(engine e, list l) {
//     const polyphony = _engine_get_polyphony(e);
//     memcpy(e->voices, l, list_calc_size(polyphony, voice_calc_size()));
// }

// mixer _engine_get_mixer(engine e) {
//     return (mixer)e+2*sizeof(unsigned short)+list_calc_size(_engine_get_polyphony(e), voice_calc_size());
// }

// void _engine_set_mixer(engine e, mixer m) {
//     memcpy(e+sizeof(unsigned short), e+2*sizeof(unsigned short)+list_calc_size(_engine_get_polyphony(e), voice_calc_size()), sizeof(unsigned short));
// }

//


size_t engine_calc_size (const unsigned short polyphony, const unsigned short sample_size) {
    // size_t voice_list_size = list_calc_size(polyphony, voice_calc_size());
    // size_t mixer_size  = mixer_calc_size(polyphony);
    // size_t active_midi_notes_list_size = list_calc_size(polyphony, sizeof(note_t));
    return sizeof (engine_t); // + voice_list_size + mixer_size + active_midi_notes_list_size;
};

engine engine_create (const unsigned short polyphony, const unsigned short sample_size) {
    engine e = malloc (engine_calc_size (polyphony, sample_size));

    if (e) {
        // _engine_set_polyphony(e, polyphony);
        // _engine_set_sample_size(e, sample_size);
        // _engine_set_voice_list(e, list_create(polyphony, voice_calc_size()), list_calc_size(polyphony, voice_calc_size()));
        // _engine_set_mixer(e, mixer_create(polyphony));
        e->polyphony   = polyphony;
        e->sample_size = sample_size;
        e->voice_mixer = mixer_create (polyphony);
        e->voices      = list_create (polyphony, voice_calc_size ());
        // memcpy(e->voices, list_create(polyphony, voice_calc_size()), list_calc_size(polyphony, voice_calc_size()));
        for (unsigned short i = 0; i < polyphony; i++) {
            list_push (e->voices, voice_create ());
        }
        e->active_midi_notes = list_create (polyphony, sizeof (note_t));
        // for (unsigned short i = 0; i < polyphony; i++) {
        //     list_push(e->active_midi_notes, NULL);
        // }
    }

    return e;
};

void engine_destroy (engine e) {
    list_destroy (e->voices);
    for (unsigned short i = 0; i < e->polyphony; i++) {
        voice_destroy ((voice)(e->voices + i * sizeof (voice_t)));
    }
    list_destroy (e->active_midi_notes);
    mixer_destroy (e->voice_mixer);
    free (e);
};


bool remove_note_filter_fn (const void* note, const unsigned short i, const void* compare_note) {
    if (((note_t*)note)->midi_note_number == ((note_t*)compare_note)->midi_note_number) {
        return false;
    }
    return true;
};

void engine_add_active_note (engine e, note n) {
    list_filter (e->active_midi_notes, &remove_note_filter_fn, n);
    list_push (e->active_midi_notes, n);
};

void engine_remove_active_note (engine e, note n) {
    list_filter (e->active_midi_notes, &remove_note_filter_fn, n);
};

short engine_out (engine e) {
    for (unsigned short i = 0; i < e->polyphony; i++) {
        voice v = (voice)(e->voices->items + i * e->voices->item_size);
        mixer_in (e->voice_mixer, i, voice_out (v));
    }
    return (short)(mixer_out (e->voice_mixer));
};

void engine_process (engine e, short* buffer, unsigned short buffer_size) {
    unsigned short l = list_get_length (e->active_midi_notes);
    for (unsigned short i = 0; i < e->polyphony; i++) {
        voice v = (voice)list_at (e->voices, i);
        if (i >= l) {
            mixer_set_lvl (e->voice_mixer, i, 0);
            voice_set_note (v, NULL);
            continue;
        }
        note n = (note)(e->active_midi_notes->items + i * e->active_midi_notes->item_size);
        mixer_set_lvl (e->voice_mixer, i, 100); // TODO: velocity
        voice_set_note (v, n);
    }

    for (unsigned short i = 0; i < buffer_size; i++) {
        buffer[i] = engine_out (e);
    }
};
