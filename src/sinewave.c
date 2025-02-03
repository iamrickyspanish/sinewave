#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "engine.h"
#include "ioaudio.h"
#include "keyboard.h"
#include "midi.h"
#include "raylib.h"
#include "voice.h"

#define SAMPLE_SIZE 512
#define BUFFER_SIZE 4096
#define MAX_POLYPHONY 4
#define KEYS_SIZE 10

note_t notes[KEYS_SIZE] = {
    { 48, "C3", 130.81f }, { 49, "C#3", 138.59 }, { 50, "D3", 146.83 },
    { 51, "D#3", 155.56 }, { 52, "E3", 164.81 }, { 53, "F3", 174.61 },
    { 54, "F#3", 185.00 }, { 55, "G3", 196.00 }, { 56, "G#3", 207.65 }, { 57, "A3", 220.00 },
    // { 58, "A#3" },
    // { 59, "B3" },
};

const kb_key_t keys[KEYS_SIZE] = {
    { 48, (unsigned short)KEY_ONE, "C3 " },
    { 49, (unsigned short)KEY_TWO, "C#3" },
    { 50, (unsigned short)KEY_THREE, "D3 " },
    { 51, (unsigned short)KEY_FOUR, "D#3" },
    { 52, (unsigned short)KEY_FIVE, "E3 " },
    { 53, (unsigned short)KEY_SIX, "F3 " },
    { 54, (unsigned short)KEY_SEVEN, "F#3" },
    { 55, (unsigned short)KEY_EIGHT, "G3 " },
    { 56, (unsigned short)KEY_NINE, "G#3" },
    { 57, (unsigned short)KEY_ZERO, "A3 " },
};

bool remove_note_filter_fn (const void* note, const unsigned short i, const void* compare_note) {
    if (((note_t*)note)->midi_note_number == ((note_t*)compare_note)->midi_note_number) {
        return false;
    }
    return true;
};

void handle_note_on_fn (unsigned short midi_code, void* active_notes) {
    note n = NULL;
    for (unsigned short i = 0; i < KEYS_SIZE; i++) {
        if (notes[i].midi_note_number == midi_code) {
            n = &notes[i];
            break;
        }
    }
    if (n) {
        list_filter ((list)active_notes, &remove_note_filter_fn, n);
        list_push ((list)active_notes, n);
    }
};


void handle_note_off_fn (unsigned short midi_code, void* active_notes) {
    note n = NULL;
    for (unsigned short i = 0; i < KEYS_SIZE; i++) {
        if (notes[i].midi_note_number == midi_code) {
            n = &notes[i];
            break;
        }
    }
    if (n) {
        list_filter ((list)active_notes, &remove_note_filter_fn, n);
    }
};

int main (void) {


    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth  = 800;
    const int screenHeight = 450;
    short* data            = (short*)malloc (sizeof (short) * BUFFER_SIZE);

    ioaudio audio_interface = ioaudio_create (SAMPLE_SIZE, BUFFER_SIZE);
    engine audio_engine     = engine_create (MAX_POLYPHONY, SAMPLE_SIZE);
    list active_midi_notes  = list_create (MAX_POLYPHONY, sizeof (note_t));
    keyboard virtual_keyboard =
    keyboard_create (keys, KEYS_SIZE, &handle_note_on_fn, &handle_note_off_fn);
    InitWindow (screenWidth, screenHeight, "sinewave, yo");
    SetTargetFPS (60);


    // int osc_i = 0;
    //--------------------------------------------------------------------------------------
    // Main loop
    while (!WindowShouldClose ()) // Detect window close button or ESC key
    {
        // Refill audio stream if required ioaudio_is_ready(audio_interface) &&
        if (ioaudio_is_ready_for_write (audio_interface)) {
            engine_process (audio_engine, data, BUFFER_SIZE);
            ioaudio_write (audio_interface, data, BUFFER_SIZE);
        }
        ////
        // Update
        //----------------------------------------------------------------------------------
        keyboard_listen (virtual_keyboard, active_midi_notes);
        // voice_state curr_state;
        unsigned short notes_length = list_get_length (active_midi_notes);
        for (unsigned short i = 0; i < audio_engine->polyphony; i++) {
            voice_state_value val;
            if (i >= notes_length) {
                val.ushort_val = 0;
                engine_set_voice_state_attr (audio_engine, i, LVL, val);
                continue;
            }
            note n        = (note)list_at (active_midi_notes, i);
            val.float_val = n->freq;
            engine_set_voice_state_attr (audio_engine, i, OSC1_FREQ, val);
            engine_set_voice_state_attr (audio_engine, i, OSC2_FREQ, val);
            val.ushort_val = 100;
            engine_set_voice_state_attr (audio_engine, i, LVL, val);
        }
        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing ();
        // keyboard_render(virtual_keyboard);
        unsigned short l = list_get_length (active_midi_notes);
        ClearBackground (RAYWHITE);
        DrawText ("sinewaves, yo", 190, 200, 20, LIGHTGRAY);
        DrawText (TextFormat ("active note length: %d", l), 190, 220, 20, BLUE);
        for (unsigned short i = 0; i < l; i++) {
            note n = (note)list_at (active_midi_notes, i);
            DrawText (n->name, 190 + i * 70, 240, 20, RED);
        }
        for (unsigned short i = 0; i < MAX_POLYPHONY; i++) {
            voice_state vs = engine_get_voice_state (audio_engine, i);
            // voice v = (voice)list_at (audio_engine->voices, i);
            DrawText (vs ? TextFormat ("%.2f", vs->osc1Freq) : "-",
            190 + i * 70, 260, 20, GREEN);
        }
        for (unsigned short i = 0; i < MAX_POLYPHONY; i++) {
            voice_state vs = engine_get_voice_state (audio_engine, i);
            DrawText (vs ? TextFormat ("%d", vs->lvl) : "-", 190 + i * 70, 280, 20, BROWN);
        }
        // oscilloscope
        for (int i = 0; i < BUFFER_SIZE; i++) {
            if (i % (BUFFER_SIZE / screenWidth) == 0) {
                DrawText (".", i / (BUFFER_SIZE / screenWidth),
                350 + data[i] / 100, 20, BLACK);
            }
        }

        EndDrawing ();
        //----------------------------------------------------------------------------------
    }
    // De-Initialization
    //--------------------------------------------------------------------------------------
    // osc_destroy(osc1);
    engine_destroy (audio_engine);
    ioaudio_destroy (audio_interface);
    keyboard_destroy (virtual_keyboard);
    free (data);
    CloseWindow ();
    //--------------------------------------------------------------------------------------
    return 0;
}