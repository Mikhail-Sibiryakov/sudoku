#include "Matrix.h"
#include "Vector.h"
#include "printHelpers.h"
#include "Game.h"
#include "time.h"

#define END '\0'
#define INF 2e9

int main() {
    srand(time(NULL));
    printf("----------Sudoku----------\n");
    int n = 0;
    while (n != 4 && n != 9) {
        printf("Select size of board...   ");
        scanf("%d", &n);
    }
    int mode = 0;
    while (n == 9 && mode != 1 && mode != 2) {
        if (n == 9) {
            printf("Select a mode:\n");
            printf("1: board from dataset\n");
            printf("2: generate right now!\n");
            scanf("%d", &mode);
        }
    }
    if (n == 4) {
        mode = 2;
    }
    printf("Press 'q' to exit\n");
    printf("Press 'r' to reset board \n");
    printf("Press 'm' to auto solve (with animation) \n");
    printf("Press 'i' to auto solve instantly \n");
    Vector* v = getVector(2*n + 1, n);
    char c;

    setInputMode();
    moveToPoint(v, 1, 0);


    Game* game = getGame(n);
    startGame(game, mode);
    printGame(game, v);
    showPosition(v);

    int result = 0;
    while (1) {
        c = getchar();
        if (c == 'a') {
            moveCursor(v, -2, 0);
        } else if (c == 'd') {
            moveCursor(v, 2, 0);
        } else if (c == 'w') {
            moveCursor(v, 0, -1);
        } else if (c == 's') {
            moveCursor(v, 0, 1);
        } else if (c == 'q' || c == 'Q') {
            break;
        } else if (c == '\b'|| c == 127) {
            removeNumb(game, getXInMatrix(v), getYInMatrix(v));
            printGame(game, v);
        } else if (c == 'i') {
            reset(game);
            findSolution(game);
            printGame(game, v);
        } else if (c >= '0' && c <= '9') {
            setNumb(game, getXInMatrix(v), getYInMatrix(v), getInt(c));
            printGame(game, v);
        } else if (c == 'l') {
            if (check(game)) {
                break;
            }
        } else if (c == 'r') {
            reset(game);
            printGame(game, v);
        } else if (c == 'm') {
            reset(game);
            solve(game, v);
            printGame(game, v);
            showPosition(v);
        }
        if (check(game)) {
            result = 1;
            break;
        }
    }
    int tmp = game->cntNumbers;
    hidePosition(v);
    backToStart(v);
    resetInputMode();
    deleteGame(game);
    deleteVector(v);
    if (result) {
        printf("Great solution !\n");
    }
    return 0;
}
