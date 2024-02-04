#ifndef __SNW_MIDI_H
#define __SNW_MIDI_H 

typedef struct {
    unsigned short midi_note_number;
    char name[4];
} note_t;

typedef note_t* note; 

// note notes[KEYS_SIZE] = {
//     { 48, "C3" },
//     { 49, "C#3" },
//     { 50, "D3" },
//     { 51, "D#3" },
//     { 52, "E3" },
//     { 53, "F3" },
//     { 54, "F#3" },
//     { 55, "G3" },
//     { 56, "G#3" },
//     { 57, "A3" },
//     { 58, "A#3" },
//     { 59, "B3" },
// };  



#endif