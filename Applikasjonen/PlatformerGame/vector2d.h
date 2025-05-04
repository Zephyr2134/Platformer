#ifndef VECTOR2D
#define VECTOR2D

typedef struct{
    float x;
    float y;
}Vector2D;

void MakeVector(Vector2D* vector, float xValue, float yValue);

void setX(Vector2D* vector, float xValue);
void setY(Vector2D* vector, float yValue);

void changeX(Vector2D* vector, float xValue);
void changeY(Vector2D* vector, float yValue);

float getX(Vector2D vector);
float getY(Vector2D vector);

#endif