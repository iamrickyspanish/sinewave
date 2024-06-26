#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "keyboard.h"
#include "raylib.h"

#define ITEM_STRING_SIZE 5

keyboard keyboard_create(const kb_key_t keys[], const unsigned short keys_size, note_on_handler handle_note_on, note_off_handler handle_note_off) {
    keyboard kb = malloc(sizeof(*kb)+sizeof(kb_key_t)*keys_size);
    
    if(kb) {
        kb->handle_note_on = handle_note_on;
        kb->handle_note_off = handle_note_off;
        kb->keys_size = keys_size;
        kb->keys = malloc(sizeof(kb_key_t)*keys_size);
        memcpy(kb->keys, keys, keys_size*sizeof(kb_key_t));
    };

    return kb;
};

void keyboard_destroy(keyboard kb) {
    free(kb->keys);
    free(kb);
};

bool remove_key_filter_fn(const void* pressed_key, const unsigned short i,const void* compare_key) {
    if (((kb_key)pressed_key)->midi_code == ((kb_key)compare_key)->midi_code) {
        return false;
    }
    return true;
};

void keyboard_listen(keyboard kb, void* data) {
    for (unsigned short i = 0; i < kb->keys_size; i++) {
        if(IsKeyPressed(kb->keys[i].key_code)) {            
            kb->handle_note_on(kb->keys[i].midi_code, data);
        } else if(IsKeyReleased((int)(kb->keys[i].key_code))) {
            kb->handle_note_off(kb->keys[i].midi_code, data);
        }
    }
};

void item_to_string_fn(const void* kb,char string[], unsigned short string_length, unsigned short item_string_length) {      
    strcpy(string, strlen(string) != 0 ? " " : "");
    if (item_string_length < ITEM_STRING_SIZE)
     return;
    strcat(string, ((kb_key)kb)->label);
};

// void keyboard_render(keyboard kb) {
//     unsigned short string_length = list_get_length(kb->pressed_keys)*ITEM_STRING_SIZE;
//     char* pressed_keys_string = malloc((string_length+1)*sizeof(char));
//     strcpy(pressed_keys_string, "");
//     list_to_string(kb->pressed_keys, pressed_keys_string, string_length, &item_to_string_fn, ITEM_STRING_SIZE);
//     puts(pressed_keys_string);
//     free(pressed_keys_string);
// }