#ifndef CAMERA
#define CAMERA

#include <SDL3/SDL.h>
#include "vector2d.h"

typedef struct
{
    SDL_FRect camRect;
    int mapWidth;
} camera;

void InitCamera(camera *cam, int width, int height, int mapWidth);
void UpdateCamPos(camera *cam, Vector2D targetPos);

#endif