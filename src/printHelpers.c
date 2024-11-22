#include "printHelpers.h"
#define NONE 0

void setInputMode() {
    struct termios new_termios;

    // Получаем текущее состояние терминала
    tcgetattr(STDIN_FILENO, &new_termios);

    // Устанавливаем режим неканонического ввода и отключаем эхо вывести символы
    new_termios.c_lflag &= ~(ICANON | ECHO);

    // Применяем новые настройки
    tcsetattr(STDIN_FILENO, TCSANOW, &new_termios);
    printf("\e[?25l");
}

void resetInputMode() {
    struct termios new_termios;

    // Получаем текущее состояние терминала
    tcgetattr(STDIN_FILENO, &new_termios);

    // Восстанавливаем оригинальные настройки
    new_termios.c_lflag |= (ICANON | ECHO);

    // Применяем новые настройки
    tcsetattr(STDIN_FILENO, TCSANOW, &new_termios);
    printf("\e[?25h");
}

/*  Печатает матрицу по "вектору"
    Необходимо чтобы распечатанная матрица "помещалась" в поле, которое задает вектор.
    Вектор и курсур будут возвращены в исходное состоянии по завершении процедуры.
    */
void printGame(Game* game, Vector* v) {
    Matrix* matrix = game->matrix;
    int oldX = v->x;
    int oldY = v->y;
    moveToPoint(v, 0, 0);
    for (int i = 0; i < matrix->n; ++i) {
        printf(" ");
        v->x += 1;
        for (int j = 0; j < matrix->m; ++j) {
            if (*(*(game->access->data + i) + j)) {
                printf("\033[1;32m");
            } else {
                printf("\033[1;31m");
            }
            if (*(*(matrix->data + i) + j) == NONE) {
                printf(". ");
            } else {
                printf("%d ", *(*(matrix->data + i) + j));
            }
            printf("\033[0m");
            v->x += 2;
        }
        if (i + 1 < matrix->n) {
            printf("\n");
            v->y += 1;
            v->x = 0;
        }
    }
    moveToPoint(v, oldX, oldY);
    showPosition(v);
}

void printChar(Vector* v, int x, int y, char ch) {
    int oldX = v->x;
    int oldY = v->y;
    moveToPoint(v, x, y);
    printf("%c", ch);
    v->x += 1;
    moveToPoint(v, oldX, oldY);
}

void showPosition(Vector* v) {
    printChar(v, v->x - 1, v->y, '[');
    printChar(v, v->x + 1, v->y, ']');
}

void hidePosition(Vector* v) {
    printChar(v, v->x - 1, v->y, ' ');
    printChar(v, v->x + 1, v->y, ' ');
}

void moveCursor(Vector* v, int a, int b) {
    hidePosition(v);
    moveVector(v, a, b);
    showPosition(v);
}

int solve(Game* game, Vector* v) {
    hidePosition(v);
    int n = game->matrix->n;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (getValue(game->matrix, i, j) == NONE) {
                for (int var = 1; var <=n; ++var) {
                    if (isValid(game, i, j, var)) {
                        setValue(game->matrix, i, j, var);
                        printGame(game, v);
                        usleep(100000);
                        ++game->cntNumbers;
                        if (solve(game, v)) {
                            return 1;
                        }
                    }
                    setValue(game->matrix, i, j, NONE);
                    --game->cntNumbers;
                }
                return 0;
            }
        }
    }
    return 1;
}