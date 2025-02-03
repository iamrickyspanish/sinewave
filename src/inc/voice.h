#ifndef __SNW_VOICE_
#define __SNW_VOICE_

#include "mixer.h"
#include "osc.h"

#define __SNW_OSC_COUNT 2

typedef enum { OSC1_FREQ, OSC2_FREQ, OSC1_LVL, OSC2_LVL, LVL } voice_state_attr;

typedef union {
    float float_val;
    unsigned short ushort_val;
    // int int_val;
} voice_state_value;

typedef struct {
    float osc1Freq;
    float osc2Freq;
    unsigned short osc1Lvl;
    unsigned short osc2Lvl;
    unsigned short lvl;
} voice_state_t;

typedef voice_state_t* voice_state;

typedef struct {
    osc osc1;
    osc osc2;
    voice_state state;
    mixer osc_mixer;
} voice_t;

typedef voice_t* voice;

voice voice_create (const voice_state init_state);
void voice_destroy (voice);
void voice_set_state (voice, voice_state state);

void voice_set_state_attr (voice, voice_state_attr attr, voice_state_value value);
int voice_out (voice);
size_t voice_calc_size ();

#endif
