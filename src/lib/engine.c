#include <stdlib.h>
#include <string.h>

#include "engine.h"

size_t engine_calc_size(const unsigned short polyphony, const unsigned short sample_size) {
    // size_t voice_list_size = list_calc_size(polyphony, sizeof(voice_t));
    // size_t mixer_size  = mixer_calc_size(polyphony);
    // size_t active_midi_notes_list_size = list_calc_size(polyphony, sizeof(note_t));
    return sizeof(engine_t);//+voice_list_size+mixer_size+active_midi_notes_list_size;
};

engine engine_create(const unsigned short polyphony, const unsigned short sample_size) {
    engine e = malloc(engine_calc_size(polyphony, sample_size));

    if (e) {
        e->polyphony = polyphony;
        e->sample_size = sample_size;
        e->voices = list_create(polyphony, sizeof(voice_t));
        e->voice_mixer = mixer_create(polyphony);
        e->active_midi_notes = list_create(polyphony, sizeof(note_t));
    }

    return e;
};

void engine_destroy(engine e) {
    list_destroy(e->voices);
    list_destroy(e->active_midi_notes);
    mixer_destroy(e->voice_mixer);
    free(e);
};

bool remove_note_filter_fn(const void* note, const unsigned short i, const void* compare_note) {
    if (((note_t*)note)->midi_note_number == ((note_t*)compare_note)->midi_note_number) {
        return false;
    }
    return true;
};

void engine_add_active_note(engine e, note n) {
    list_filter(e->active_midi_notes, &remove_note_filter_fn, n);
    list_push(e->active_midi_notes, n);
};

void engine_remove_active_note(engine e, note n) {
        list_filter(e->active_midi_notes, &remove_note_filter_fn, n);
};

short engine_out(engine e) {
    for (unsigned short i = 0; i < e->polyphony; i++) {
        voice v = (voice)(e->voices->items+i*e->voices->item_size);
        // voice_out(v);
        mixer_in(e->voice_mixer,i, 0);
        mixer_in(e->voice_mixer,i, 0);
    }
    return (short)(mixer_out(e->voice_mixer));
};

void engine_process(engine e, short* buffer, unsigned short buffer_size) {
    for (unsigned short i = 0; i < e->polyphony; i++) {
        if(i >= list_get_length(e->active_midi_notes)) {
            mixer_set_lvl(e->voice_mixer, i, 0);
            continue;
        }
        note n = (note)(e->active_midi_notes->items+i*e->active_midi_notes->item_size);
        mixer_set_lvl(e->voice_mixer, i, 100);//TODO: velocity
        voice_set_note((voice)(e->voices->items+i*e->voices->item_size), n);
    }
    //TODO: do better
    
    //TODO: this crashes the app:
    for (unsigned short i = 0; i < buffer_size; i++) {
        // memcpy(buffer[0], engine_out(e), sizeof(short));
        buffer[i] = engine_out(e);
        engine_out(e);

    }
};
