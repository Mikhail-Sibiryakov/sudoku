#include "Matrix.h"
#include "Vector.h"
#include <termios.h>
#include <unistd.h>

//TODO: Camel style!!!



#define END '\0'
#define INF 2e9
#define FILE_LOG "log.txt"

void logPrint(char* str) {
    FILE* fp = fopen(FILE_LOG, "a");
    fputs(str, fp);
    fclose(fp);
}

void logInt(int a) {
    char buffer[10];
    buffer[0] = '0' + a;
    buffer[1] = ' ';
    buffer[2] = END;
    logPrint(buffer);
}

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

int main() {
    // for (int i = 0; i < 10; ++i) {
    //     logInt(i);
    // }
    printf("Some information\n");
    printf("Some information\n");
    int n = 3, m = 3;
    scanf("%d%d", &n, &m);
    struct Vector* v = getVector(2*m - 1, n);
    char c;

    // Устанавливаем режим ввода
    set_input_mode();
    moveToPoint(v, 0, 0);

    struct Matrix* matrix = getMatrix(n, m);
    // fillMatrix(matrix);
    // printMatrix(matrix, v);

    int u = 1;
    while (1) {
        c = getchar();
        if (c == 'a') {
            moveVector(v, -2, 0);
        } else if (c == 'd') {
            // if (u) { printMatrix(matrix, v); u = 1;}
            moveVector(v, 2, 0);
            // char buffer[10];
            // buffer[0] = '0' + (v->x);
            // buffer[1] = ' ';
            // buffer[2] = '0' + (v->y);
            // buffer[3] = END;
            // logPrint(buffer);
        } else if (c == 'w') {
            moveVector(v, 0, -1);
        } else if (c == 's') {
            moveVector(v, 0, 1);
        } else if (c == 'q' || c == 'Q') {
            break;
        } else if (c == '\b'|| c == 127) {
            setValue(matrix, getYInMatrix(v), getXInMatrix(v), -1);
            // backToStart(v);
            printMatrix(matrix, v);
        } else if (c == 'p') {
            fillMatrix(matrix);
            printMatrix(matrix, v);
        } else if (c >= '0' && c <= '9') {
            // logInt(getValue(matrix, getYInMatrix(v), getXInMatrix(v)));
            if (getValue(matrix, getYInMatrix(v), getXInMatrix(v)) == -1) {
                setValue(matrix, getYInMatrix(v), getXInMatrix(v), c - '0');
            }
            printMatrix(matrix, v);
        }
    }
    backToStart(v);
    reset_input_mode();
    deleteMatrix(matrix);
    deleteVector(v);
    return 0;
}
