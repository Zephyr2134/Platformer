#include "character.h"

void CreateCharacter(SDL_Renderer* renderer, Character* c, float xPos, float yPos, float width, float height, int speed, const char* imageFilePath)
{
    c->velocityY = 0;
    c->grounded = true;

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
    c->velocityY = -10;
    return true;
    }
    return false;
}

void UpdateViewPos(Character* c)
{
    c->dstRect.x = getX(c->worldPos);
    c->dstRect.y = getY(c->worldPos);
}

void UpdateCharacter(Character* c, int direction)
{
    if(getY(c->worldPos) + c->dstRect.h < 500)
    {
        c->grounded = false;
    }else{
        if(getY(c->worldPos) + c->dstRect.h + c->velocityY >= 500)
        {
            setY(&c->worldPos, 500 - c->dstRect.h);
            c->velocityY = 0;
            c->grounded = true;
        }
    }
    if(!c->grounded)
    {
        c->velocityY += 0.2f;
    }

    if(direction > 0)
    {
        c->flip = SDL_FLIP_NONE;
    }else if(direction < 0){
        c->flip = SDL_FLIP_HORIZONTAL;
    }

    changeY(&c->worldPos, c->velocityY);
    changeX(&c->worldPos, direction*c->speed);
    
    UpdateViewPos(c);
}

void DrawCharacter(SDL_Renderer* renderer, Character c)
{
    SDL_RenderTextureRotated(renderer, c.texture, NULL, &c.dstRect, 0, 0, c.flip);
}