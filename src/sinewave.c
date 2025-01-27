#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "raylib.h"
#include "ioaudio.h"
#include "engine.h"
#include "keyboard.h" 

#define SAMPLE_SIZE 512
#define BUFFER_SIZE 4096
#define MAX_POLYPHONY 8
#define KEYS_SIZE 10

note_t notes[KEYS_SIZE] = {
    { 48, "C3" },
    { 49, "C#3" },
    { 50, "D3" },
    { 51, "D#3" },
    { 52, "E3" },
    { 53, "F3" },
    { 54, "F#3" },
    { 55, "G3" },
    { 56, "G#3" },
    { 57, "A3" },
    // { 58, "A#3" },
    // { 59, "B3" },
};  

const kb_key_t keys[KEYS_SIZE] = {
    { 48, (unsigned short)KEY_ONE,"C3 " },
    { 49, (unsigned short)KEY_TWO,"C#3" },
    { 50, (unsigned short)KEY_THREE, "D3 " },
    { 51, (unsigned short)KEY_FOUR, "D#3" },
    { 52, (unsigned short)KEY_FIVE, "E3 " },
    { 53, (unsigned short)KEY_SIX, "F3 " },
    { 54, (unsigned short)KEY_SEVEN, "F#3" },
    { 55, (unsigned short)KEY_EIGHT, "G3 " },
    { 56, (unsigned short)KEY_NINE, "G#3" },
    { 57, (unsigned short)KEY_ZERO, "A3 " },
};


void handle_note_on_fn(unsigned short midi_code, void* e) {
    note n = NULL;
    for (unsigned short i = 0; i < KEYS_SIZE; i++) {
        if (notes[i].midi_note_number == midi_code) {
            n = &notes[i];
            break;
        }
    }
    if (n) {
        engine_add_active_note((engine)e, n);
    }        
};

void handle_note_off_fn(unsigned short midi_code, void* e) {
    note n = NULL;
    for (unsigned short i = 0; i < KEYS_SIZE; i++) {
        if (notes[i].midi_note_number == midi_code) {
            n = &notes[i];
            break;
        }
    }
    if (n) {
        engine_remove_active_note((engine)e, n);
    }        
};

int main(void) {


// Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 450;
    short *data = (short *)malloc(sizeof(short)*BUFFER_SIZE);
    
    ioaudio audio_interface = ioaudio_create(SAMPLE_SIZE, BUFFER_SIZE); 
    engine audio_engine = engine_create(8, SAMPLE_SIZE);

    keyboard virtual_keyboard = keyboard_create(keys, KEYS_SIZE, &handle_note_on_fn, &handle_note_off_fn);
    InitWindow(screenWidth, screenHeight, "sinewave, yo");
    SetTargetFPS(60);
    //--------------------------------------------------------------------------------------
    // Main loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {   
        // Refill audio stream if required ioaudio_is_ready(audio_interface) && 
        if (ioaudio_is_ready_for_write(audio_interface))
        {
            engine_process(audio_engine, data, BUFFER_SIZE);
            ioaudio_write(audio_interface, data, BUFFER_SIZE);
        }
        ////
        // Update
        //----------------------------------------------------------------------------------
        keyboard_listen(virtual_keyboard, audio_engine);
        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();
            // keyboard_render(virtual_keyboard);
            unsigned short l = list_get_length(audio_engine->active_midi_notes);
            ClearBackground(RAYWHITE);
            DrawText("sinewaves, yo", 190, 200, 20, LIGHTGRAY);
            DrawText(TextFormat("active note length: %d", l), 190, 220, 20, BLUE);
            // note n = (note)list_at(audio_engine->active_midi_notes, 0);
            // if (n) {
            //     DrawText(n->name, 190, 240, 20, RED);
            // }
            for (unsigned short i = 0; i < l; i++) {
                note n = (note)list_at(audio_engine->active_midi_notes, i);
                // if (n) {
                DrawText(n->name, 190+i*50, 240, 20, RED);
                // }
            }         
        EndDrawing();
        //----------------------------------------------------------------------------------
    }
    // De-Initialization
    //--------------------------------------------------------------------------------------
    // osc_destroy(osc1);
    engine_destroy(audio_engine);
    ioaudio_destroy(audio_interface);
    keyboard_destroy(virtual_keyboard);
    free(data);
    CloseWindow();
    //--------------------------------------------------------------------------------------
    return 0;
}