#include "sigpath.h"

size_t sigpath_calc_size () {
    size_t mixer_size = mixer_calc_size (__SNW_OSC_COUNT);
    return sizeof (sigpath_t) + mixer_size;
};

sigpath sigpath_create () {
    sigpath sp = malloc (sigpath_calc_size ());
    if (sp) {
        sp->osc1      = osc_create ();
        sp->osc2      = osc_create ();
        sp->osc_mixer = mixer_create (__SNW_OSC_COUNT);
    }
    return sp;
};

void sigpath_destroy (sigpath sp) {
    osc_destroy (sp->osc1);
    osc_destroy (sp->osc2);
    mixer_destroy (sp->osc_mixer);
    free (sp);
};

void sigpath_set_osc_lvl (sigpath sp, unsigned short index, unsigned short lvl) {
    mixer_set_lvl (sp->osc_mixer, index, lvl);
};


void sigpath_set_oscs_freq (sigpath sp, float freq) {
    osc_set_freq (sp->osc1, freq);
    osc_set_freq (sp->osc2, freq);
};

int sigpath_out (sigpath sp) {
    mixer_in (sp->osc_mixer, 0, osc_out (sp->osc1));
    mixer_in (sp->osc_mixer, 1, osc_out (sp->osc2));
    return mixer_out (sp->osc_mixer);
};
