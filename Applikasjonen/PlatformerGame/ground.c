#include "ground.h"
#include <stdlib.h>

void MakeGround(SDL_Renderer* renderer, ground* g, int mapSize, const int* map, float tileSize, const char* filepath)
{
    g->dstRect.w = tileSize;
    g->dstRect.h = tileSize;
    g->dstRect.y = 550 - tileSize;

    g->size = mapSize;
    g->map1d = malloc(mapSize * sizeof(int));
    g->map1d = map;

    SDL_Surface* image = IMG_Load(filepath);
    g->groundTex = SDL_CreateTextureFromSurface(renderer, image);
    SDL_SetTextureScaleMode(g->groundTex, SDL_SCALEMODE_NEAREST);
    SDL_DestroySurface(image);
}

void DrawGround(SDL_Renderer* renderer, ground* g)
{
    for(int i = 0; i < g->size; i++)
    {
        if(g->map1d[i] == 1)
        {
        g->dstRect.x = i * g->dstRect.w;
        SDL_RenderTexture(renderer, g->groundTex, NULL, &g->dstRect);
        }
    }
}