#include "Vector.h"
#include <stdlib.h>

int getCorrectOffset(int l, int r, int base, int offset) {
    if (base + offset >= l && base + offset <= r) {
        return offset;
    } else if (base + offset < l) {
        // base + offset == l
        return l - base;
    } else if (base + offset > r) {
        // base + offset == r
        return r - base;
    }
    return -INF;
}

void moveVector(Vector* v, int a, int b) {
    int na = getCorrectOffset(0, v->max_x, v->x, a);
    int nb = getCorrectOffset(0, v->max_y, v->y, b);
    if (na != a || nb != b) {
        return;
    }
    v->x += a;
    v->y += b;
    if (a > 0) {
        printf("\033[%dC", a);
    } else if (a < 0) {
        printf("\033[%dD", -a);
    }
    if (b > 0) {
        printf("\033[%dB", b);
    } else if (b < 0) {
        printf("\033[%dA", -b);
    }
}

void moveToPoint(Vector* v, int x, int y) {
    // v->x + ? == x
    // v->y + ? == y
    moveVector(v, x - v->x, y - v->y);
}

int getXInMatrix(Vector* v) {
    return (v->x - 1) / 2;
}

int getYInMatrix(Vector* v) {
    return v->y;
}

// In fact Vector would be a Singleton...
Vector* getVector(int x, int y) {
    Vector* vec = malloc(sizeof(Vector));
    // Vector* vec = malloc(sizeof(*vec)); What is better?
    for (int i = 0; i < y; ++i) {
        for (int j = 0; j < x; ++j) {
            printf("-");
        }
        printf("\n");
    }
    vec->x = 0;
    vec->y = y - 1;
    vec->max_x = x - 1;
    vec->max_y = y - 1;
    printf("\033[1A");
    return vec;
}

void deleteVector(Vector* v) {
    moveToPoint(v, 0, v->max_y);
    printf("\033[1B");
    free(v);
}

void backToStart(Vector* v) {
    moveToPoint(v, 0, v->max_y);
}