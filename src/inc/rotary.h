#ifndef __SW_ROTARY_KNOB__
#define __SW_ROTARY_KNOB__

#define BORDER_WIDTH 5
#define RADIUS 25

#include "raylib.h"
#include <stdbool.h>

typedef void (*rotary_change_handler) (unsigned short value, void* data);
typedef struct {
    unsigned short value; // value between 0-127
    bool centered;        // if true 64 will be the starting point, otherwise 0
    int pos_x;
    int pos_y;
    bool hover;
    bool pressed;
    Vector2 last_mouse_pos;
    rotary_change_handler on_change;
} rotary_t;

typedef rotary_t* rotary;

rotary rotary_create (int pos_x,
int pos_y,
bool centered,
unsigned short initial_value,
rotary_change_handler handle_change);
void rotary_set_value (rotary, unsigned short value);
unsigned short rotary_get_value (rotary);
void rotary_listen (rotary);
void rotary_render (rotary);


#endif