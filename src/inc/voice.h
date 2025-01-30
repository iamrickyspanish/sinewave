#ifndef __SNW_VOICE_H
#define __SNW_VOICE_H

#include "midi.h"
#include "sigpath.h"

typedef struct {
    note n;
    sigpath path;
} voice_t;

typedef voice_t* voice;

voice voice_create ();
void voice_destroy (voice);
void voice_set_note (voice, note n);
int voice_out (voice);
size_t voice_calc_size ();

#endif