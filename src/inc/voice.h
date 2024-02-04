#ifndef __SNW_VOICE_H
#define __SNW_VOICE_H

#include "sigpath.h"

typedef struct {
    sigpath path;
    note n;
} voice_t;

typedef voice_t* voice;

voice voice_create();
void voice_destroy(voice);
void voice_set_note(voice, note n);
int voice_out(voice);

#endif