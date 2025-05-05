#ifndef GROUND
#define GROUND

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include "camera.h"
#include "character.h"

typedef struct
{
    SDL_Texture *groundTex;
    SDL_FRect dstRect;
    float tileSize;
    int *map1d;
    int size;
} ground;

void MakeGround(SDL_Renderer *renderer, ground *g, int mapSize, const int *map, float tileSize, const char *filepath);
bool CollideGround(SDL_FRect recA, Character *c);
void DrawGround(SDL_Renderer *renderer, ground *g, Character *player, camera cam);
void FreeGround(ground *g);
#endif