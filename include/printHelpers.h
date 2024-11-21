#include <termios.h>
#include <unistd.h>
#include "Matrix.h"
#include "Vector.h"

void set_input_mode();

void reset_input_mode();

void printMatrix(Matrix* matrix, Vector* v);

void printChar(Vector* v, int x, int y, char ch);

void moveCursor(Vector* v, int a, int b);

void showPosition(Vector* v);

void hidePosition(Vector* v);