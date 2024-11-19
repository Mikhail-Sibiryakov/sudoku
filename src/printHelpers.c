#include "printHelpers.h"

void set_input_mode() {
    struct termios new_termios;

    // Получаем текущее состояние терминала
    tcgetattr(STDIN_FILENO, &new_termios);

    // Устанавливаем режим неканонического ввода и отключаем эхо вывести символы
    new_termios.c_lflag &= ~(ICANON | ECHO);

    // Применяем новые настройки
    tcsetattr(STDIN_FILENO, TCSANOW, &new_termios);
}

void reset_input_mode() {
    struct termios new_termios;

    // Получаем текущее состояние терминала
    tcgetattr(STDIN_FILENO, &new_termios);

    // Восстанавливаем оригинальные настройки
    new_termios.c_lflag |= (ICANON | ECHO);

    // Применяем новые настройки
    tcsetattr(STDIN_FILENO, TCSANOW, &new_termios);
}

/*  Печатает матрицу по "вектору"
    Необходимо чтобы распечатанная матрица "помещалась" в поле, которое задает вектор.
    Вектор и курсур будут возвращены в исходное состоянии по завершении процедуры.
    */
void printMatrix(struct Matrix* matrix, struct Vector* v) {
    int oldX = v->x;
    int oldY = v->y;
    moveToPoint(v, 0, 0);
    for (int i = 0; i < matrix->n; ++i) {
        for (int j = 0; j < matrix->m; ++j) {
            if (*(*(matrix->data + i) + j) == -1) {
                printf(".");
            } else {
                printf("%d", *(*(matrix->data + i) + j));
            }
            v->x += 1;
            if (j + 1 < matrix->m) {
                printf(" ");
                v->x += 1;
            }
            // logInt(v->x);
            // logInt(v->y);
            // logPrint("\n");
        }
        if (i + 1 < matrix->n) {
            printf("\n");
            v->y += 1;
            v->x = 0;
        }
    }
    moveToPoint(v, oldX, oldY);
}