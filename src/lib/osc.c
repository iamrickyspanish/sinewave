#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "osc.h"

#define PI 3.14159265358979323846f

osc osc_create() {
    osc instance = malloc(sizeof(osc_t));
    if (instance) {
        instance->frequency = 440.0f;
        instance->audioFrequency = 440.0f;
        instance->waveIndex = 0.0f;
        instance->wave = WAVE_SINE;
    }
    return instance;
}

void osc_destroy(osc instance) {
    free(instance);
}

void osc_set_freq(osc instance, const float freq) {
    instance->audioFrequency = freq;
};

void osc_generate(osc instance, short* buffer, short frames) {
    instance->audioFrequency =
        instance->frequency + (instance->audioFrequency - instance->frequency)*0.95f;
    float incr = instance->audioFrequency/44100.0f;
    for (unsigned int i = 0; i < frames; i++)
    {
        buffer[i] = (short)(32000.0f*sinf(2*PI*instance->waveIndex));
        instance->waveIndex += incr;
        if (instance->waveIndex > 1.0f) instance->waveIndex -= 1.0f;        
    }
}


 short osc_out(osc o) {
    o->audioFrequency =
        o->frequency + (o->audioFrequency - o->frequency)*0.95f;
    float incr = o->audioFrequency/44100.0f;
    short out = (short)(32000.0f*sinf(2*PI*o->waveIndex));
    o->waveIndex += incr;
    if (o->waveIndex > 1.0f) o->waveIndex -= 1.0f;
    return out;
};