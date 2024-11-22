
#include "Matrix.h"


int randInt(int a, int b) {
    return rand() % (b - a + 1) + a;
}

void fillMatrix(struct Matrix *matrix) {
    for (int i = 0; i < matrix->n; ++i) {
        for (int j = 0; j < matrix->m; ++j) {
            *(*(matrix->data + i) + j) = randInt(FROM, TO);
        }
    }
}

void setValue(Matrix *matrix, int i, int j, int val) {
    *(*(matrix->data + i) + j) = val;
}

int getValue(Matrix *matrix, int i, int j) {
    return *(*(matrix->data + i) + j);
}

Matrix* getMatrix(int n, int m) {
    Matrix *matrix = calloc(1, sizeof(*matrix));
    matrix->data = calloc(n, sizeof(int*));
    matrix->n = n;
    matrix->m = m;
    for (int i = 0; i < matrix->n; ++i) {
        *(matrix->data + i) = calloc(m, sizeof(int));
    }
    return matrix;
}

void deleteMatrix(Matrix* matrix) {
    for (int i = 0; i < matrix->n; ++i) {
        free(*(matrix->data + i));
    }
    free(matrix->data);
    free(matrix);
}

void nothing() {}