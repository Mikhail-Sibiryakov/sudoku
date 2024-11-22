#ifndef PRINT_HELPERS
#define PRINT_HELPERS

#include <termios.h>
#include <unistd.h>
#include "Matrix.h"
#include "Vector.h"
#include "Game.h"

void set_input_mode();

void reset_input_mode();

void printGame(Game* game, Vector* v);

void printChar(Vector* v, int x, int y, char ch);

void moveCursor(Vector* v, int a, int b);

void showPosition(Vector* v);

void hidePosition(Vector* v);

int solve(Game* game, Vector* v);
#endif