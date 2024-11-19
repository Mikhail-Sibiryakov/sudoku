#ifndef VECTOR_H
#define VECTOR_H
#include <stdio.h>
#define INF 2e9

typedef struct Vector {
    int x, y;
    int max_x, max_y;
} Vector;

void moveVector(Vector* v, int a, int b);

void moveToPoint(Vector* v, int x, int y);

int getXInMatrix(Vector* v);

int getYInMatrix(Vector* v);

Vector* getVector(int x, int y);

void deleteVector(Vector* v);

void backToStart(Vector* v);
#endif