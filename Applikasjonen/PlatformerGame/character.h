#ifndef CHARACTER
#define CHARACTER

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include "vector2d.h"

typedef struct{
    SDL_Texture* texture;
    SDL_FlipMode flip;
    SDL_FRect dstRect;
    Vector2D worldPos;
    int speed;
    float velocityY;
    bool grounded;
}Character;

void CreateCharacter(SDL_Renderer* renderer, Character* c, float xPos, float yPos, float width, float height, int speed, const char* imageFilePath);
bool CharacterJump(Character* c);
void UpdateCharacter(Character* c, int direction);
void UpdateViewPos(Character* c);
void DrawCharacter(SDL_Renderer* renderer, Character c);

#endif