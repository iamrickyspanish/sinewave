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

int main(void) {

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
// Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 450;
    short *data = (short *)malloc(sizeof(short)*SAMPLE_SIZE);
    
    ioaudio audio_interface = ioaudio_create(SAMPLE_SIZE, BUFFER_SIZE); 
    osc osc1 = osc_create();
    keyboard keyboard_comp = keyboard_create(keys, KEYS_SIZE, MAX_POLYPHONY);
    InitWindow(screenWidth, screenHeight, "sinewave, yo");
    SetTargetFPS(60);
    //--------------------------------------------------------------------------------------
    // Main loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {   
        // Refill audio stream if required ioaudio_is_ready(audio_interface) && 
        if (ioaudio_is_ready_for_write(audio_interface))
        {
            osc_generate(osc1, data, BUFFER_SIZE);
            ioaudio_write(audio_interface, data, BUFFER_SIZE);
        }
        ////
        // Update
        //----------------------------------------------------------------------------------
        keyboard_listen(keyboard_comp);
        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();
            keyboard_render(keyboard_comp);
            ClearBackground(RAYWHITE);
            DrawText("Congrats! You created your first window!", 190, 200, 20, LIGHTGRAY);            
        EndDrawing();
        //----------------------------------------------------------------------------------
    }
    // De-Initialization
    //--------------------------------------------------------------------------------------
    osc_destroy(osc1);
    ioaudio_destroy(audio_interface);
    keyboard_destroy(keyboard_comp);
    free(data);
    CloseWindow();
    //--------------------------------------------------------------------------------------
    return 0;
}