#ifndef SOUND_H
#define SOUND_H

#include <stdlib.h>
#include <SDL3/SDL.h>

typedef struct
{
    SDL_AudioStream *stream;
    Uint8 *audioBuf;
    Uint32 audioLen;
    SDL_AudioSpec spec;
} sound;

sound Create_Sound(const char *WAVPath);
bool Play_Sound(sound *s);
void Destroy_Sound(sound *s);

typedef struct
{
    sound *sounds;
    size_t size;
    size_t capacity;
} soundManager;

void initSoundManager(soundManager *sounds);
void pushBack(soundManager *sounds, const char *pathfile);
void playSounds(soundManager *sounds);
void freeSound(soundManager *sounds);
void removeAt(soundManager *sounds, size_t index);
#endif