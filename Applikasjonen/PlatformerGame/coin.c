#include "coin.h"
#include <stdlib.h>

void InitCoinManager(SDL_Renderer* renderer, coinManager* coins, const char* coinImage)
{

    SDL_Surface* tmpImage = IMG_Load(coinImage);
    coins->coinTex = SDL_CreateTextureFromSurface(renderer, tmpImage);
    SDL_DestroySurface(tmpImage);
    SDL_SetTextureScaleMode(coins->coinTex, SDL_SCALEMODE_NEAREST);

    coins->coins = malloc(sizeof(coin) * 4);
    coins->size = 0;
    coins->capacity = 4;

    coins->coinRec.w = 10;
    coins->coinRec.h = 20;
}

void AddCoin(coinManager* coins, float xPos, float yPos, int value)
{
    coin c;
    c.value = value;
    setX(&c.worldPos,xPos);
    setY(&c.worldPos,yPos);
    c.active = true;

    if(coins->size >= coins->capacity){
        coins->capacity *= 2;
        coins->coins = realloc(coins->coins, sizeof(coin) * coins->capacity);
    }
    coins->coins[coins->size++] = c;

    SDL_Log("Coin added");
}

int CollideCoins(coinManager c, SDL_FRect recB, camera cam)
{
    SDL_FRect recA = c.coinRec;
    for(int i = 0; i < c.size; i++){
        recA.x = getX(c.coins[i].worldPos) - cam.camRect.x;
        recA.y = getY(c.coins[i].worldPos) - cam.camRect.x;
    if(recA.x < recB.x + recB.w &&
       recA.x + recA.w > recB.x &&
       recA.y < recB.y + recB.h &&
       recA.y + recA.h > recB.y){
        DestroyCoin(&c, i);
        SDL_Log("Collided with coin");
        return c.coins[i].value;
       }
    }
    return 0;
}

void DestroyCoin(coinManager* c, size_t index)
{
    if(index >= c->size) return;

    for(size_t i = index; i < c->size - 1; i++) {
        c->coins[i] = c->coins[i + 1];
    }
    
    memset(&c->coins[c->size - 1], 0, sizeof(coin));

    c->size--;

    c->coins[index].active = false;
}

void RenderCoins(SDL_Renderer* renderer, coinManager* c, camera cam)
{
    for(int i = 0;i<c->size;i++)
    {
        if(c->coins[i].active){
        c->coinRec.x = getX(c->coins[i].worldPos) - cam.camRect.x;
        c->coinRec.y = getY(c->coins[i].worldPos) - cam.camRect.y;
        SDL_RenderTexture(renderer, c->coinTex, NULL, &c->coinRec);
    }
    }
}