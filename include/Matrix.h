#ifndef MATRIX_H
#define MATRIX_H

#include <stdlib.h>
#include <time.h>
#define FROM 0
#define TO 9

/* двумерный целочисленный массив размера n строк, m столбцов*/
typedef struct Matrix {
    int **data;
    int n;
    int m;
} Matrix;

/* случайное целое число из отрезка [a, b] */
int randInt(int a, int b);

/* заполнить матрицу случ. цел. числами из [FROM, TO] */
void fillMatrix(Matrix *matrix);

/* matrix[i][j] = val */
void setValue(Matrix *matrix, int i, int j, int val);

/* return matrix[i][j] */
int getValue(Matrix *matrix, int i, int j);

/* конструктор матрицы n строк, m столбцов */
Matrix* getMatrix(int n, int m);

/* деструктор матрицы */
void deleteMatrix(Matrix* matrix);

#endif