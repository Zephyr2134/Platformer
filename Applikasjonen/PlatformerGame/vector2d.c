#include "vector2d.h"

void MakeVector(Vector2D* vector, float xValue, float yValue)
{
    vector->x = xValue;
    vector->y = yValue;
}

void setX(Vector2D* vector, float xValue)
{
    vector->x = xValue;
}
void setY(Vector2D* vector, float yValue)
{
    vector->y = yValue;
}

void changeX(Vector2D* vector, float xValue)
{
    vector->x += xValue;
}
void changeY(Vector2D* vector, float yValue)
{
    vector->y += yValue;
}

float getX(Vector2D vector)
{
    return vector.x;
}
float getY(Vector2D vector)
{
    return vector.y;
}