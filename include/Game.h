#ifndef GAME_H
#define GAME_H

#include "Matrix.h"

typedef struct Game {
    Matrix* matrix;
    Matrix* access;
    int cntNumbers;
} Game;

Game* getGame(int size);

int getInt(char ch);

void deleteGame(Game* game);

void startGame(Game* game, int mode);

void finishGame(Matrix* game);

void removeNumb(Game* game, int x, int y);

void setNumb(Game* game, int x, int y, int val);

int isCorrect(Game* game);

int check(Game* game);

void generateBoard(Game* game);

void clearBoard(Game* game);

void reset(Game* game);

int findSolution(Game* game);

int isValid(Game* game, int i, int j, int val);
#endif