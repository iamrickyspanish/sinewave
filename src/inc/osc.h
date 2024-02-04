#ifndef __SNW_OSC_H
#define __SNW_OSC_H

#define WAVE_SINE 1

typedef struct {
    float frequency;
    float audioFrequency;
    float audioFrequencyOffset;
    float waveIndex;
    short wave; 
} osc_t;

typedef osc_t* osc;

osc osc_create();
void osc_destroy(osc);
void osc_set_freq(osc, const float freq);
void osc_generate(osc, short* buffer, short frames);
short osc_out(osc);

#endif