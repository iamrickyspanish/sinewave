#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "midi.h"
#include "voice.h"

// TODO: move to midi.h/midi.c, use a lookup table
// float note_to_frequency (note n) {
//     float f = 110.0f * (pow (2, (n->midi_note_number - 69) / 12));
//     return f;
// }

size_t voice_calc_size () {
    return sizeof (voice_t) + sigpath_calc_size ();
};


voice voice_create (sigpath_state init_sigpath_state) {

    voice v = malloc (voice_calc_size ());

    if (v) {
        v->path = sigpath_create (init_sigpath_state);
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
};

int voice_out (voice v) {
    if (v->n) {
        sigpath_state_value value;
        value.float_val = v->n->freq; // * 4.0f;
        // printf ("%s - %d:  %f\n", v->n->name, v->n->midi_note_number, v->n->freq);
        sigpath_set_state (v->path, OSC1_FREQ, value);
        sigpath_set_state (v->path, OSC2_FREQ, value);
    }
    return sigpath_out (v->path);
};
