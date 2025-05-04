#include "soundManager.h"

sound Create_Sound(const char* WAVPath){
    sound sound;
    if(SDL_LoadWAV(WAVPath, &sound.spec, &sound.audioBuf, &sound.audioLen))
        {
            sound.stream = SDL_OpenAudioDeviceStream(SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK, &sound.spec, NULL, NULL);
            if(!sound.stream)
            {
            SDL_Log("Failed to open audio stream %s", SDL_GetError());
            SDL_free(sound.audioBuf);
            sound.audioBuf = NULL;
            }
        }else{
            SDL_Log("Failed to load WAV file: %s", SDL_GetError());
        }
        return sound;
}

bool Play_Sound(sound* s){
    if(!s->stream || !s->audioBuf)
        {
            SDL_Log("Error: Attempted to play sound on an invalid stream of buffer!");
            return true;
        }
        if(!SDL_PutAudioStreamData(s->stream, s->audioBuf, s->audioLen))
        {
            SDL_Log("Failes to queue audio data: %s", SDL_GetError());
            return false;
        }else{
        SDL_Log("KaBoom");
        SDL_ResumeAudioStreamDevice(s->stream);
        return true;
    }
}

void Destroy_Sound(sound* s){
    if(s->stream) SDL_DestroyAudioStream(s->stream);
    if(s->audioBuf) SDL_free(s->audioBuf);
}

void initSoundManager(soundManager* sounds){
    sounds->sounds = malloc(sizeof(sound)*4);
    sounds->size = 0;
    sounds->capacity = 4;
}

void pushBack(soundManager* sounds, const char* filepath){
    sound s = Create_Sound(filepath);
    if(sounds->size >= sounds->capacity){
        sounds->capacity *= 2;
        sounds->sounds = realloc(sounds->sounds, sizeof(sound) * sounds->capacity);
    }
    sounds->sounds[sounds->size++] = s;
}

void removeAt(soundManager* sounds, size_t index){
    if(index >= sounds->size) return;

    for(size_t i = index; i < sounds->size; i++){
        sounds->sounds[i] = sounds->sounds[i+1];
    }
    sounds->size--;
}

void playSounds(soundManager* sounds){
    for(int i = 0; i<sounds->size;i++){
        if(Play_Sound(&sounds->sounds[i])){
            removeAt(sounds, i);
        }
    }
}

void freeSound(soundManager* sounds){
    free(sounds->sounds);
    sounds->sounds = NULL;
    sounds->size = 0;
    sounds->capacity = 0;
}