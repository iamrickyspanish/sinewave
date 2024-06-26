#ifndef __SNW_LIST_H
#define __SNW_LIST_H

#include <stdbool.h>

typedef struct {
    unsigned short capacity;
    unsigned short length;
    unsigned short item_size;
    unsigned char items[];
 } list_t;

typedef list_t* list;

typedef bool (*list_filter_fn)(const void*, const unsigned short i, const void* data);
typedef void list_item_to_string_fn(const void*, char string[], unsigned short string_length, unsigned short item_string_length);

list list_create(const unsigned short capacity, const unsigned short item_size);
void list_destroy(list);
unsigned short list_get_length(const list);
unsigned short list_get_capacity(const list);
unsigned short list_get_item_size(const list);
void list_push(list, const void* item);
void list_pop(list, void* buffer);
void list_unshift(list, void* item);
void list_shift(list, void* buffer);
void list_filter(list, list_filter_fn fn, const void* data);
void list_to_string(list, char string[], unsigned short string_length, list_item_to_string_fn item_to_string_fn, unsigned short item_string_length);
size_t list_calc_size(const unsigned short capacity, const unsigned short item_size);
#endif