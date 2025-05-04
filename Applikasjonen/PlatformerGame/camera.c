#include "camera.h"

void InitCamera(camera* cam, int width, int height, int mapWidth)
{
    cam->camRect.x = 0;
    cam->camRect.y = 0;
    cam->camRect.w = width;
    cam->camRect.h = height;

    cam->mapWidth = mapWidth;
}

void UpdateCamPos(camera* cam, Vector2D targetPos)
{
    cam->camRect.x = targetPos.x - (cam->camRect.w/2);
    if(cam->camRect.x < 0)
    {
        cam->camRect.x = 0;
    }else if(cam->camRect.x + cam->camRect.w > cam->mapWidth)
    {
        cam->camRect.x = cam->mapWidth - cam->camRect.w;
    }
}