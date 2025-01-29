#include <math.h>
#include <stdlib.h>
#include <string.h>

#include "midi.h"
#include "voice.h"

// TODO: move to midi.h/midi.c, use a lookup table
float note_to_frequency (note n) {
    float f = 440.0f * (pow (2, (n->midi_note_number - 69) / 12));
    return f;
}

size_t voice_calc_size () {
    return sizeof (voice_t) + sigpath_calc_size ();
};


voice voice_create () {

    voice v = malloc (voice_calc_size ());
    if (v) {
        v->path = sigpath_create ();
        v->n    = NULL;
    }
    return v;
};

void voice_destroy (voice v) {
    sigpath_destroy (v->path);
    free (v);
};

void voice_set_note (voice v, note n) {
    v->n = n;
    // memcpy(v->n, n, sizeof(note_t));
};

int voice_out (voice v) {
    if (v->n) {
        sigpath_set_oscs_freq (v->path, note_to_frequency (v->n));
    }
    return sigpath_out (v->path);
};
