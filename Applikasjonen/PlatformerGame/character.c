#include "character.h"

void CreateCharacter(SDL_Renderer* renderer, Character* c, float xPos, float yPos, float width, float height, int speed, const char* imageFilePath)
{
    c->speed = speed;

    c->dstRect.x = 0;
    c->dstRect.y = 0;
    c->dstRect.w = width;
    c->dstRect.h = height;

    setX(&c->worldPos, xPos);
    setY(&c->worldPos, yPos);

    SDL_Surface* image = IMG_Load(imageFilePath);
    c->texture = SDL_CreateTextureFromSurface(renderer, image);
    SDL_SetTextureScaleMode(c->texture, SDL_SCALEMODE_NEAREST);
    SDL_DestroySurface(image);
}

void UpdateCharacter(Character* c, int direction)
{
    changeX(&c->worldPos, direction*c->speed);
}

void UpdateViewPos(Character* c)
{
    c->dstRect.x = getX(c->worldPos);
    c->dstRect.y = getY(c->worldPos);
}

void DrawCharacter(SDL_Renderer* renderer, Character c)
{
    SDL_RenderTexture(renderer, c.texture, NULL, &c.dstRect);
}