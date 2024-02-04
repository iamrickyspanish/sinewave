#ifndef __SNW_IOAUDIO_H
#define __SNW_IOAUDIO_H

#include <stdbool.h>

struct ioaudio_s;
typedef struct ioaudio_s ioaudio_t;
typedef ioaudio_t* ioaudio;


ioaudio ioaudio_create(unsigned short, unsigned short);
void ioaudio_destroy(ioaudio);
bool ioaudio_is_ready(const ioaudio);
void ioaudio_write(ioaudio, const short*, const short);
bool ioaudio_is_ready_for_write(const ioaudio);
void ioaudio_set_volume(ioaudio, const float);

#endif