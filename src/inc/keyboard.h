#ifndef __SNW_KEYBOARD_H
#define __SNW_KEYBOARD_H

#include <stdbool.h>

#include "list.h"

typedef struct {
    unsigned short midi_code;
    unsigned short key_code;
    char label[4];
} kb_key_t;

typedef kb_key_t* kb_key;

typedef void (*note_on_handler)(unsigned short midi_code, void* data);
typedef void (*note_off_handler)(unsigned short midi_code, void* data);

typedef struct {
    unsigned short keys_size;
    // list pressed_keys;
    kb_key_t* keys;
    note_on_handler handle_note_on;
    note_off_handler handle_note_off;
    
} keyboard_t;

typedef keyboard_t* keyboard;

keyboard keyboard_create(
    const kb_key_t* keys,
    const unsigned short keys_size,
    note_on_handler handle_note_on,
    note_off_handler handle_note_off
);
void keyboard_destroy(keyboard);
void keyboard_listen(keyboard, void* data);
// void keyboard_render(keyboard);

#endif