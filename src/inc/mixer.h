#ifndef __SNW_MIXER_H
#define __SNW_MIXER_H

#include <stdlib.h>


typedef struct {
    int value;
    unsigned short level;
} mixer_channel_t;

typedef mixer_channel_t* mixer_channel;

typedef struct {
    unsigned short channel_count;
    mixer_channel_t channels[];
} mixer_t;

typedef mixer_t* mixer;

mixer mixer_create(unsigned short channel_count);
void mixer_destroy(mixer);
void mixer_in(mixer, unsigned short channel_index, int value);
int mixer_out(mixer);
void mixer_set_lvl(mixer, unsigned short channel_index, unsigned short lvl);
unsigned short mixer_get_lvl(mixer, unsigned short channel_index);
size_t mixer_calc_size(unsigned short channel_count);

#endif