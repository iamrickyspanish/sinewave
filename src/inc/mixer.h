#ifndef __SNW_MIXER_H
#define __SNW_MIXER_H

#include <stdlib.h>

typedef struct {
    unsigned short in_count;
    unsigned short* in_levels;
    int* in_values;
    
} mixer_t;

typedef mixer_t* mixer;

mixer mixer_create(unsigned short in_count);
void mixer_destroy(mixer);
void mixer_in(mixer, unsigned short in_index, int value);
int mixer_out(mixer);
void mixer_set_lvl(mixer, unsigned short in_index, unsigned short lvl);
unsigned short mixer_get_lvl(mixer, unsigned short in_index);

#endif