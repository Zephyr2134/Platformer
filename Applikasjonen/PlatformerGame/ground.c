#include "ground.h"
#include "vector2d.h"
#include <stdlib.h>

void MakeGround(SDL_Renderer* renderer, ground* g, int mapSize, const int* map, float tileSize, const char* filepath)
{
    g->dstRect.w = tileSize;
    g->dstRect.h = tileSize;
    g->dstRect.y = 550 - 50;

    g->size = mapSize;
    g->map1d = malloc(mapSize * sizeof(int));
    g->map1d = map;

    SDL_Surface* image = IMG_Load(filepath);
    g->groundTex = SDL_CreateTextureFromSurface(renderer, image);
    SDL_SetTextureScaleMode(g->groundTex, SDL_SCALEMODE_NEAREST);
    SDL_DestroySurface(image);
}

bool CollideGround(SDL_FRect recA, Character* c)
{
    if(recA.x <= c->dstRect.x + c->dstRect.w &&
       recA.x + recA.w >= c->dstRect.x &&
       recA.y <= c->dstRect.y + c->dstRect.h + c->velocityY &&
       recA.y >= c->dstRect.y + 30)
    {
        setY(&c->worldPos, recA.y - c->dstRect.h);
        return true;
    }
    return false;
}

void DrawGround(SDL_Renderer* renderer, ground* g, Character* player, camera cam)
{
    bool returnVal = false;
    for(int i = 0; i < g->size; i++)
    {
        if(g->map1d[i] == 1)
        {
        g->dstRect.x = (i * g->dstRect.w) - cam.camRect.x;
        if(CollideGround(g->dstRect, player)){returnVal=true;}
        SDL_RenderTexture(renderer, g->groundTex, NULL, &g->dstRect);
        }
    } 
    player->grounded = returnVal;
}

void FreeGround(ground* g)
{
    if(g == NULL) return;

    if(g->groundTex != NULL)
    {
        SDL_DestroyTexture(g->groundTex);
        g->groundTex = NULL;
    }

    if(g->map1d != NULL)
    {
        free(g->map1d);
        g->map1d = NULL;
    }
}