#ifndef COIN
#define COIN

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include "vector2d.h"
#include "camera.h"

typedef struct{
    Vector2D worldPos;
    int value;
    bool active;
}coin;

typedef struct{
    coin* coins;
    SDL_FRect coinRec;
    SDL_Texture* coinTex;
    size_t size;
    size_t capacity;
}coinManager;

void InitCoinManager(SDL_Renderer* renderer, coinManager* coins, const char* coinImage);
void AddCoin(coinManager* coins, float xPos, float yPos, int value);
int CollideCoins(coinManager c,SDL_FRect recB, camera cam);
void DestroyCoin(coinManager* c, size_t index);
void RenderCoins(SDL_Renderer* renderer, coinManager* c, camera cam);
void FreeCoins(coinManager* coins);
void MakeCoinMap(coinManager* coins, int posX, int posY, const int* map2d, size_t rows, size_t perRow);


#endif