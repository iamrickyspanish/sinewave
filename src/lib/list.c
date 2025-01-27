#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "list.h"

#include "keyboard.h"

size_t list_calc_size(const unsigned short capacity, const unsigned short item_size) {
    return sizeof(list_t) + capacity * item_size;
};

list list_create(const unsigned short capacity, const unsigned short item_size) {
    list l = malloc(list_calc_size(capacity, item_size));
    if (l) {
        l->capacity = capacity;
        l->item_size = item_size;
        l->length = 0;
    }
    return l;
};

void list_destroy(list l) {
    free(l);    
};

unsigned short list_get_length(const list l) {
    return l->length;
};

unsigned short list_get_capacity(const list l) {
    return l->capacity;
};

unsigned short list_get_item_size(const list l) {
    return l->item_size;
};

void list_push(list l, const void* item) {
    if (l->length >= l->capacity) {
        return;
    };
    memcpy(l->items + l->item_size*l->length, item, l->item_size);
    l->length++;
};

void list_pop(list l, void* buffer) {
    if (l->length <= 0) {
        return;
    }
    memcpy(buffer, l->items + l->length*l->item_size, l->item_size);
    l->length--;
};

void list_unshift(list l, void* item) {
    if (l->length >= l->capacity) {
        return;
    };
    for (unsigned short i = 0; i < l->length-1; i++) {
        memcpy(l->items+(i+1)*l->item_size, l->items+i*l->item_size, l->item_size);
    }
    memcpy(l->items, item, l->item_size);
    l->length++;
};

void list_shift(list l, void* buffer) {
    memcpy(buffer, l->items, l->item_size);
    for (unsigned short i = 0; i < l->length-1; i++) {
        memcpy(l->items+i*l->item_size, l->items+(i+1)*l->item_size, l->item_size);
    }
    l->length--;
};

void list_filter(list l, list_filter_fn fn, const void* data) {
    for (unsigned short i = 0; i < l->length; i++) {
        if (!(*fn)(l->items+i*l->item_size, i, data)) {
            for (unsigned short j = i; j < l->length -1; j++) {
                memcpy(l->items+j*l->item_size, l->items+(j+1)*l->item_size, l->item_size);
            }            
            l->length--;
        };
    }
};

void list_to_string(list l, char string[], unsigned short string_length, list_item_to_string_fn item_to_string_fn, unsigned short item_string_length) {
    char items_as_string[l->length][item_string_length];    
    strcpy(string, "");
    if (l->length == 0) {
        return;
    }
    unsigned short relevant_item_count = (item_string_length == 0) ? 0: string_length/item_string_length;
    if (relevant_item_count == 0) {
        return;
    }
    for (unsigned short i = 0; i < relevant_item_count; i++) {
        (*item_to_string_fn)(l->items+i*l->item_size, items_as_string[i], string_length,  item_string_length);
        strcat(string, items_as_string[i]);
    }
};

void* list_at(list l, const unsigned short index) {
    return index < l->length ? l->items+index*l->item_size : NULL;
};
