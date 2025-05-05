#include "coin.h"
#include <stdlib.h>

void InitCoinManager(SDL_Renderer *renderer, coinManager *coins, const char *coinImage)
{

    SDL_Surface *tmpImage = IMG_Load(coinImage);
    coins->coinTex = SDL_CreateTextureFromSurface(renderer, tmpImage);
    SDL_DestroySurface(tmpImage);
    SDL_SetTextureScaleMode(coins->coinTex, SDL_SCALEMODE_NEAREST);

    coins->coins = malloc(sizeof(coin) * 4);
    coins->size = 0;
    coins->capacity = 4;

    coins->coinRec.w = 32;
    coins->coinRec.h = 32;
}

void AddCoin(coinManager *coins, float xPos, float yPos, int value)
{
    coin c;
    c.value = value;
    setX(&c.worldPos, xPos);
    setY(&c.worldPos, yPos);
    c.active = true;

    if (coins->size >= coins->capacity)
    {
        coins->capacity *= 2;
        coins->coins = realloc(coins->coins, sizeof(coin) * coins->capacity);
    }
    coins->coins[coins->size++] = c;

    SDL_Log("Coin added");
}

int CollideCoins(coinManager c, SDL_FRect recB, camera cam)
{
    int amountOfCollisions = 0;
    SDL_FRect recA = c.coinRec;
    for (int i = 0; i < c.size; i++)
    {
        if (c.coins[i].active)
        {
            recA.x = getX(c.coins[i].worldPos) - cam.camRect.x;
            recA.y = getY(c.coins[i].worldPos) - cam.camRect.y;
            if (recA.x < recB.x + recB.w &&
                recA.x + recA.w > recB.x &&
                recA.y < recB.y + recB.h &&
                recA.y + recA.h > recB.y)
            {
                DestroyCoin(&c, i);
                SDL_Log("Collided with coin");
                amountOfCollisions++;
            }
        }
    }
    return amountOfCollisions;
}

void DestroyCoin(coinManager *c, size_t index)
{
    if (index >= c->size)
        return;

    c->coins[index].active = false;
}

void RenderCoins(SDL_Renderer *renderer, coinManager *c, camera cam)
{
    for (int i = 0; i < c->size; i++)
    {
        if (c->coins[i].active)
        {
            c->coinRec.x = getX(c->coins[i].worldPos) - cam.camRect.x;
            c->coinRec.y = getY(c->coins[i].worldPos) - cam.camRect.y;
            if (c->coinRec.x + c->coinRec.w > 0 &&
                c->coinRec.x < cam.camRect.w)
            {
                SDL_RenderTexture(renderer, c->coinTex, NULL, &c->coinRec);
            }
        }
    }
}

void FreeCoins(coinManager *coins)
{
    if (!coins)
        return;

    if (coins->coins)
    {
        free(coins->coins);
    }

    if (coins->coinTex)
    {
        SDL_DestroyTexture(coins->coinTex);
        coins->coinTex = NULL;
    }

    coins->size = 0;
    coins->capacity = 0;
}

void MakeCoinMap(coinManager *coins, int posX, int posY, const int *map2d, size_t rows, size_t perRow)
{
    for (int r = 0; r < rows; r++)
    {
        for (int p = 0; p < perRow; p++)
        {
            if (map2d[r * perRow + p] == 1)
            {
                AddCoin(coins, p * 50 + posX, r * 50 + posY, 1);
            }
        }
    }
}

void ResetCoins(coinManager *coins)
{
    for (int i = 0; i < coins->size; i++)
    {
        coins->coins[i].active = true;
    }
}