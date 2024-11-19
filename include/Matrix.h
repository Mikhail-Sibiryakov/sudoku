#ifndef MATRIX_H
#define MATRIX_H

#include <stdlib.h>
#define FROM 0
#define TO 9

typedef struct Matrix {
    int **data;
    int n;
    int m;
} Matrix;

void fillMatrix(Matrix *matrix);

void setValue(Matrix *matrix, int i, int j, int val);

int getValue(Matrix *matrix, int i, int j);

Matrix* getMatrix(int n, int m);

void deleteMatrix(Matrix* matrix);

#endif