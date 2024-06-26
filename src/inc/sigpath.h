#ifndef __SNW_SIGNAL_PATH_
#define __SNW_SIGNAL_PATH_

#include "osc.h"
#include "mixer.h"

#define __SNW_OSC_COUNT 2

typedef struct {
    osc osc1;
    osc osc2;
    mixer osc_mixer;
} sigpath_t;

typedef sigpath_t* sigpath;

sigpath sigpath_create();
void sigpath_destroy(sigpath);
void sigpath_set_oscs_freq(sigpath, float pitch);
void sigpath_set_osc_lvl(sigpath, unsigned short index, unsigned short lvl);
int sigpath_out(sigpath);
size_t sigpath_calc_size();

#endif

