#include <stdlib.h>
#include <string.h>

#include "ioaudio.h"
#include "raylib.h"

struct ioaudio_s {
    AudioStream stream;
    // short* write_buffer;
    unsigned short sample_size;
    unsigned short buffer_size;
    unsigned short buffer_pos_read;
    unsigned short buffer_pos_write;
} ;

typedef struct ioaudio_s ioaudio_t;

ioaudio ioaudio_create(unsigned short sample_size, unsigned short buffer_size) {
    InitAudioDevice();
    SetAudioStreamBufferSizeDefault(buffer_size);
    ioaudio instance = malloc(sizeof(instance)+sizeof(AudioStream));
    if (instance) {
        instance->stream = LoadAudioStream(44100, 16, 1);
        instance->sample_size = sample_size;
        instance->buffer_size = buffer_size;
        // instance->buffer_pos_read = 0;
        // instance->buffer_pos_write = 0;
    }
    PlayAudioStream(instance->stream);
    return instance;
}

bool ioaudio_is_ready(const ioaudio instance) {
    return IsAudioDeviceReady() && IsAudioStreamReady(instance->stream);
}

void ioaudio_destroy(ioaudio instance) {
    UnloadAudioStream(instance->stream);
    CloseAudioDevice();
    // free(instance->write_buffer);
    free(instance);
}

void ioaudio_write(ioaudio instance, const short* data, const short size) {
    // memcpy(instance->write_buffer, data, size*sizeof(short));
    UpdateAudioStream(instance->stream, data /*instance->write_buffer*/, size);    
}

bool ioaudio_is_ready_for_write(ioaudio instance) {
    return IsAudioStreamProcessed(instance->stream);
}

void ioaudio_set_volume(ioaudio instance, const float vol) {
    SetAudioStreamVolume(instance->stream, vol);
}