#ifndef __SNW_SIGNAL_PATH_
#define __SNW_SIGNAL_PATH_

#include "mixer.h"
#include "osc.h"

#define __SNW_OSC_COUNT 2

typedef enum {
    OSC1_FREQ,
    OSC2_FREQ,
    OSC1_LVL,
    OSC2_LVL,
} sigpath_state_attr;

typedef union {
    float float_val;
    unsigned short ushort_val;
} sigpath_state_value;

typedef struct {
    float osc1Freq;
    float osc2Freq;
    unsigned short osc1Lvl;
    unsigned short osc2Lvl;
} sigpath_state_t;

typedef sigpath_state_t* sigpath_state;

typedef struct {
    osc osc1;
    osc osc2;
    sigpath_state state;
    mixer osc_mixer;
} sigpath_t;

typedef sigpath_t* sigpath;

sigpath sigpath_create (const sigpath_state init_state);
void sigpath_destroy (sigpath);
void sigpath_set_state (sigpath, sigpath_state_attr attr, sigpath_state_value value);
int sigpath_out (sigpath);
size_t sigpath_calc_size ();

#endif
