#include "rotary.h"


#include <stdio.h>
#include <stdlib.h>

rotary rotary_create (int pos_x, int pos_y, bool centered, rotary_change_handler handle_change) {
    rotary r               = malloc (sizeof (rotary_t));
    Vector2 last_mouse_pos = { 0, 0 };
    if (r) {
        r->pos_x          = pos_x;
        r->pos_y          = pos_y;
        r->centered       = centered;
        r->on_change      = handle_change;
        r->value          = 64;
        r->hover          = false;
        r->pressed        = false;
        r->last_mouse_pos = last_mouse_pos;
    }
    return r;
};

void rotary_set_value (rotary r, unsigned short value) {
    r->value = value > 127 ? 127 : value;
};

void rotary_listen (rotary r) {
    Vector2 mouse_pos = GetMousePosition ();
    Vector2 center    = { r->pos_x, r->pos_y };
    r->hover          = CheckCollisionPointCircle (mouse_pos, center, RADIUS);
    if (r->hover && IsMouseButtonDown (MOUSE_BUTTON_LEFT) && !r->pressed) {
        /* || (GetGestureDetected() == GESTURE_DRAG*)*/
        r->last_mouse_pos = mouse_pos;
        r->pressed        = true;
    }
    if (IsMouseButtonReleased (MOUSE_BUTTON_LEFT) && r->pressed) {
        r->pressed = false;
    }

    if (r->pressed) {
        // int delta_x            = r->last_mouse_pos.x - mouse_pos.x;
        int delta_y            = r->last_mouse_pos.y - mouse_pos.y;
        bool fine              = IsKeyDown (KEY_LEFT_CONTROL);
        unsigned short divider = fine ? 4 : 2;
        int new_value          = r->value + delta_y / divider;
        r->value = new_value < 0 ? 0 : new_value > 127 ? 127 : new_value;
        r->last_mouse_pos = mouse_pos;
    }
};

void rotary_render (rotary r) {
    // int perimeter = 2 * RADIUS * PI;
    // int value_on_perimeter = (perimeter / 127) * r->value;
    int min_degree        = -220;
    int max_degree        = 40;
    int available_degrees = max_degree - min_degree;
    int value_as_degree   = min_degree + (available_degrees / 127 * r->value);

    Vector2 center;
    center.x = r->pos_x;
    center.y = r->pos_y;
    DrawCircle (r->pos_x, r->pos_y, RADIUS, BLUE);
    DrawCircle (r->pos_x, r->pos_y, RADIUS - BORDER_WIDTH,
    r->hover || r->pressed ? LIGHTGRAY : WHITE);
    DrawCircle (r->pos_x, r->pos_y, BORDER_WIDTH - BORDER_WIDTH / 2, WHITE);
    DrawCircleSectorLines (
    center, RADIUS, value_as_degree - 1, value_as_degree + 1, 2, BLUE);
};