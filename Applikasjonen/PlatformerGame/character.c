#include "character.h"

void CreateCharacter(SDL_Renderer* renderer, Character* c, float xPos, float yPos, float width, float height, int speed, const char* imageFilePath)
{
    c->velocityY = 0;
    c->grounded = false;

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

    c->flip = SDL_FLIP_NONE;
}

bool CharacterJump(Character* c)
{
    if(c->grounded)
    {
    c->velocityY = -7;
    c->grounded = false;
    return true;
    }
    return false;
}

void UpdateCharacter(Character* c, int direction)
{
    if(!c->grounded)
    {
        c->velocityY += 0.2f;
    }else{
        c->velocityY = 0;
    }

    if(direction > 0)
    {
        c->flip = SDL_FLIP_NONE;
    }else if(direction < 0){
        c->flip = SDL_FLIP_HORIZONTAL;
    }

    changeY(&c->worldPos, c->velocityY);
    changeX(&c->worldPos, direction*c->speed);
}

void UpdateViewPos(Character* c, camera cam)
{
    c->dstRect.x = getX(c->worldPos) - cam.camRect.x;
    c->dstRect.y = getY(c->worldPos);
}

void DrawCharacter(SDL_Renderer* renderer, Character c)
{
    SDL_RenderTextureRotated(renderer, c.texture, NULL, &c.dstRect, 0, 0, c.flip);
}