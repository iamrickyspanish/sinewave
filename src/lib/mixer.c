#include <stdlib.h>
#include <string.h>

#include "mixer.h"

size_t mixer_calc_size(unsigned short channel_count) {
    return sizeof(mixer_t)+channel_count*sizeof(mixer_channel_t);
};

mixer mixer_create(unsigned short channel_count) {
    mixer m = malloc(mixer_calc_size(channel_count));
    if (m) {
        m->channel_count = channel_count;
        for (unsigned short i = 0; i < channel_count; i++) {
            m->channels[i].level = 100;
            m->channels[i].value = 0;
        }
    }
    return m;
};

void mixer_destroy(mixer m) {
    free(m);
};

void mixer_in(mixer m, unsigned short channel_index, int value) {
    if (channel_index >= m->channel_count) return;
    m->channels[channel_index].value = value;
};

int mixer_out(mixer m) {
    int sum = 0;
    for (unsigned short i = 0; i < m->channel_count; i++) {
        sum+= m->channels[i].level == 0 ? 0 : ((m->channels[i].value/100) * m->channels[i].level);
    }
    return (int)(sum/m->channel_count);
};

void mixer_set_lvl(mixer m, unsigned short channel_index, unsigned short lvl) {
    if (channel_index > m->channel_count) return;
    m->channels[channel_index].level = lvl > 100 ? 100 : lvl < 0 ? 0 : lvl;
};

unsigned short mixer_get_lvl(mixer m, unsigned short channel_index) {
    if (channel_index > m->channel_count) return 0;
    return m->channels[channel_index].level;
};

