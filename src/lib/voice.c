#include "voice.h"

size_t voice_calc_size () {
    size_t mixer_size = mixer_calc_size (__SNW_OSC_COUNT);
    return sizeof (voice_t) + mixer_size;
};

voice voice_create (const voice_state init_state) {
    voice sp = malloc (voice_calc_size ());
    if (sp) {
        sp->osc1            = osc_create ();
        sp->osc2            = osc_create ();
        sp->state           = malloc (sizeof (voice_state_t));
        sp->state->osc1Freq = init_state ? init_state->osc1Freq : 0;
        sp->state->osc2Freq = init_state ? init_state->osc2Freq : 0;
        sp->state->osc1Lvl  = init_state ? init_state->osc1Lvl : 0;
        sp->state->osc2Lvl  = init_state ? init_state->osc2Lvl : 0;
        sp->state->lvl      = init_state ? init_state->lvl : 0;
        sp->osc_mixer       = mixer_create (__SNW_OSC_COUNT);
    }
    return sp;
};

void voice_destroy (voice sp) {
    osc_destroy (sp->osc1);
    osc_destroy (sp->osc2);
    mixer_destroy (sp->osc_mixer);
    free (sp);
};

void voice_set_state (voice sp, voice_state state) {
    memcpy (sp->state, state, sizeof (voice_state_t));
};

void voice_set_state_attr (voice sp, voice_state_attr attr, voice_state_value value) {
    switch (attr) {
    case OSC1_FREQ: sp->state->osc1Freq = value.float_val; break;
    case OSC2_FREQ: sp->state->osc2Freq = value.float_val; break;
    case OSC1_LVL: sp->state->osc1Lvl = value.ushort_val; break;
    case OSC2_LVL: sp->state->osc2Lvl = value.ushort_val; break;
    case LVL:
        sp->state->lvl = value.ushort_val > 100 ? 100 : value.ushort_val;
        break;
    }
};

int voice_out (voice sp) {
    osc_set_freq (sp->osc1, sp->state->osc1Freq);
    osc_set_freq (sp->osc2, sp->state->osc2Freq);
    mixer_set_lvl (sp->osc_mixer, 1, sp->state->osc1Lvl);
    mixer_set_lvl (sp->osc_mixer, 2, sp->state->osc2Lvl);
    ///
    mixer_in (sp->osc_mixer, 0, osc_out (sp->osc1));
    mixer_in (sp->osc_mixer, 1, osc_out (sp->osc2));
    return (mixer_out (sp->osc_mixer) / 100 * sp->state->lvl);
};
