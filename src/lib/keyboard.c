#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "keyboard.h"
#include "raylib.h"

#define ITEM_STRING_SIZE 5

keyboard keyboard_create(const kb_key_t keys[], const unsigned short keys_size, const unsigned short polyphony) {
    // long unsigned int size = sizeof(keyboard_t)+sizeof(kb_key_t)*keys_size+polyphony*sizeof(kb_key_t)+sizeof(list_t);
    keyboard instance = malloc(sizeof(*instance)+sizeof(kb_key_t)*keys_size+polyphony*sizeof(kb_key_t)+sizeof(list_t));
    
    if(instance) {
        instance->keys_size = keys_size;
        instance->pressed_keys = list_create(polyphony, sizeof(kb_key_t));    
        instance->keys = malloc(sizeof(kb_key_t)*keys_size);
        memcpy(instance->keys, keys, keys_size*sizeof(kb_key_t));
    };

    return instance;
};

void keyboard_destroy(keyboard instance) {
    list_destroy(instance->pressed_keys);
    free(instance->keys);
    free(instance);
};

bool remove_key_filter_fn(const void* pressed_key, const unsigned short i,const void* compare_key) {
    if (((kb_key)pressed_key)->midi_code == ((kb_key)compare_key)->midi_code) {
        return false;
    }
    return true;
};

void keyboard_listen(keyboard instance) {

    for (unsigned short i = 0; i < instance->keys_size; i++) {
        if(IsKeyPressed(instance->keys[i].key_code)) {            
            // add note to active notes
            list_filter(instance->pressed_keys, &remove_key_filter_fn, &instance->keys[i]);
            kb_key_t k = instance->keys[i];
            list_push(instance->pressed_keys, &k);            
        } else if(IsKeyReleased((int)(instance->keys[i].key_code))) {
            // remove note from active notes
            list_filter(instance->pressed_keys, &remove_key_filter_fn, &instance->keys[i]);
        }
    }
};

void item_to_string_fn(const void* k,char string[], unsigned short string_length, unsigned short item_string_length) {      
    strcpy(string, strlen(string) != 0 ? " " : "");
    if (item_string_length < ITEM_STRING_SIZE)
     return;
    strcat(string, ((kb_key)k)->label);
};

void keyboard_render(keyboard instance) {
    unsigned short string_length = list_get_length(instance->pressed_keys)*ITEM_STRING_SIZE;
    char* pressed_keys_string = malloc((string_length+1)*sizeof(char));
    strcpy(pressed_keys_string, "");
    list_to_string(instance->pressed_keys, pressed_keys_string, string_length, &item_to_string_fn, ITEM_STRING_SIZE);
    puts(pressed_keys_string);
    free(pressed_keys_string);
}