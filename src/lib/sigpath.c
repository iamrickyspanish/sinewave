#include "sigpath.h"

sigpath sigpath_create() {
    sigpath sp = malloc(sizeof(sigpath_t));
    if(sp) {
        sp->oscs[0] = osc_create();
        sp->oscs[1] = osc_create();
        sp->osc_mixer = mixer_create(2);
    }
    return sp;
};

void sigpath_destroy(sigpath sp) {
    osc_destroy(sp->oscs[0]);
    osc_destroy(sp->oscs[1]);
    mixer_destroy(sp->osc_mixer);
    free(sp);
};

void sigpath_set_osc_lvl(sigpath sp, unsigned short index, unsigned short lvl) {
  mixer_set_lvl(sp->osc_mixer, index, lvl);   
};


void sigpath_set_oscs_freq(sigpath sp, float freq) {
    osc_set_freq(sp->oscs[1], freq);
    osc_set_freq(sp->oscs[2], freq);
};

int sigpath_out(sigpath sp) {
    mixer_in(sp->osc_mixer, 0, osc_out(sp->oscs[0]));
    mixer_in(sp->osc_mixer, 1, osc_out(sp->oscs[1]));
    return mixer_out(sp->osc_mixer);
};

