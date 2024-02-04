#include <stdlib.h>
#include <string.h>

#include "mixer.h"

mixer mixer_create(unsigned short in_count) {
    mixer m = malloc(sizeof(mixer_t)+in_count*sizeof(int));
    if (m) {
        m->in_count = in_count;
        for (unsigned short i = 0; i < in_count; i++) {
            m->in_levels[i] = 100;
            m->in_values[i] = 0;
        }
    }
    return m;
};

void mixer_destroy(mixer m) {
    free(m);
};

void mixer_in(mixer m, unsigned short in_index, int value) {
    if (in_index >= m->in_count) return;
    m->in_values[in_index] = value;
};

int mixer_out(mixer m) {
    int sum = 0;
    for (unsigned short i = 0; i < m->in_count; i++) {
        sum+= m->in_levels[i] == 0 ? 0 : m->in_values[i] * (1/m->in_levels[i]);
    }
    return (int)(sum/m->in_count);
};

void mixer_set_level(mixer m, unsigned short in_index, unsigned short lvl) {
    if (in_index > m->in_count) return;
    m->in_levels[in_index] = lvl > 100 ? 100 : lvl < 0 ? 0 : lvl;
};

unsigned short mixer_get_level(mixer m, unsigned short in_index) {
    if (in_index > m->in_count) return;
    return m->in_levels[in_index];
};