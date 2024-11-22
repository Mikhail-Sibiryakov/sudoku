#include "Matrix.h"
#include "Vector.h"
#include "printHelpers.h"
#include "Game.h"
#include "time.h"

#define SZ 9


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

int main() {
    srand(time(NULL));
    printf("Some information\n");
    printf("Some information\n");
    int n = SZ, m = SZ;
    struct Vector* v = getVector(2*m + 1, n);
    char c;

    // Устанавливаем режим ввода
    set_input_mode();
    moveToPoint(v, 1, 0);


    Game* game = getGame(SZ);
    startGame(game);
    printGame(game, v);
    showPosition(v);

    int tmp = 0;
    int u = 1;
    while (1) {
        c = getchar();
        if (c == 'a') {
            // moveVector(v, -2, 0);
            moveCursor(v, -2, 0);
        } else if (c == 'd') {
            // moveVector(v, 2, 0);
            moveCursor(v, 2, 0);
        } else if (c == 'w') {
            // moveVector(v, 0, -1);
            moveCursor(v, 0, -1);
        } else if (c == 's') {
            // moveVector(v, 0, 1);
            moveCursor(v, 0, 1);
        } else if (c == 'q' || c == 'Q') {
            break;
        } else if (c == '\b'|| c == 127) {
            removeNumb(game, getXInMatrix(v), getYInMatrix(v));
            printGame(game, v);
            // if (getValue(game->access, getYInMatrix(v), getXInMatrix(v))) {
            //     setValue(game->matrix, getYInMatrix(v), getXInMatrix(v), 0);
            //     printGame(game, v);
            // }
        } else if (c == 'p') {
            // fillMatrix(matrix);
            // printMatrix(matrix, v);
        } else if (c >= '0' && c <= '9') {
            setNumb(game, getXInMatrix(v), getYInMatrix(v), getInt(c));
            // if (getValue(game->matrix, getYInMatrix(v), getXInMatrix(v)) == 0) {
            //     setValue(game->matrix, getYInMatrix(v), getXInMatrix(v), c - '0');
            // }
            printGame(game, v);
        } else if (c == 'k') {
            if (isCorrect(game)) {
                tmp = game->cntNumbers;
                break;
            }
        } else if (c == 'l') {
            if (check(game)) {
                break;
            }
        } else if (c == 'm') {
            reset(game);
            printGame(game, v);
        }
        // if (c == 'a' || c == 's' || c == 'd' || c == 'w') {
        //     showPosition(v);
        // }
    }
    hidePosition(v);
    backToStart(v);
    reset_input_mode();
    deleteGame(game);
    deleteVector(v);
    return 0;
}
