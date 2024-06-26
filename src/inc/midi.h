#ifndef __SNW_MIDI_H
#define __SNW_MIDI_H 

typedef struct {
    unsigned short midi_note_number;
    char name[4];
} note_t;

typedef note_t* note; 



#endif