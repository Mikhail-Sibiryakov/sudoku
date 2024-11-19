#include <termios.h>
#include <unistd.h>
#include "Matrix.h"
#include "Vector.h"

void set_input_mode();

void reset_input_mode();

void printMatrix(Matrix* matrix, Vector* v);