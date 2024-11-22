#include "Game.h"
#include <stdio.h>
#define DATA_FILE "../data/data.txt"
#define SIZE_BF 100
#define NONE 0

int getInt(char ch) {
    return ch - '0';
}

int mySqrt(int n) {
    int d = 1;
    for (; d * d <= n; ++d) {
        if (d * d == n) {
            return d;
        }
    }
    return -1;
}

Game* getGame(int size) {
    Game* game = (Game*)malloc(sizeof(Game));
    game->matrix = getMatrix(size, size);
    game->access = getMatrix(size, size);
    return game;
}

void deleteGame(Game* game) {
    deleteMatrix(game->matrix);
    free(game);
}

void loadBoard(Game* game) {
    char buffer[SIZE_BF];
    FILE *fp = fopen(DATA_FILE, "r");
    int q = randInt(1, 10000);
    if (fp) {
        for (int i = 0; i < q; ++i) {
            fgets(buffer, SIZE_BF, fp);
            // printf("%s\n", buffer);
            int n = game->matrix->n;
            for (int i = 0; i < n * n; ++i) {
                int value = getInt(buffer[i]);
                setValue(game->matrix, i / n, i % n, value);    
                setValue(game->access, i / n, i % n, (value == NONE ? 1 : 0));    
                game->cntNumbers += (value == NONE ? 0 : 1);
            }
        }
        fclose(fp);
    }
}

void startGame(Game* game, int mode) {
    clearBoard(game);
    if (mode == 1) {
        loadBoard(game);
    } else if (mode == 2) {
        generateBoard(game);
    }
}

void finishGame(Matrix* m) {
    
}

void removeNumb(Game* game, int x, int y) {
    if (getValue(game->access, y, x) && getValue(game->matrix, y, x) != NONE) {
        setValue(game->matrix, y, x, NONE);
        --game->cntNumbers;
    }
}

void setNumb(Game* game, int x, int y, int val) {
    if (getValue(game->access, y, x)) {
        game->cntNumbers += (getValue(game->matrix, y, x) == NONE ? 1 : 0);
        setValue(game->matrix, y, x, val);
    }
}

void clear(int* ptr, int n) {
    for (int i = 0; i < n; ++i) {
        *(ptr + i) = 0;
    }
}

int isCorrect(Game* game) {
    int n = 10;
    int cnt[n];
    int sz = game->matrix->n;
    
    // rows
    for (int i = 0; i < sz; ++i) {
        clear(cnt, n);
        for (int j = 0; j < sz; ++j) {
            if (getValue(game->matrix, i, j) == NONE) {
                continue;
            }
            ++cnt[getValue(game->matrix, i, j)];
            if (cnt[getValue(game->matrix, i, j)] > 1) {
                return 0;
            }
        }
    }

    // columns
    for (int j = 0; j < sz; ++j) {
        clear(cnt, n);
        for (int i = 0; i < sz; ++i) {
            if (getValue(game->matrix, i, j) == NONE) {
                continue;
            }
            ++cnt[getValue(game->matrix, i, j)];
            if (cnt[getValue(game->matrix, i, j)] > 1) {
                return 0;
            }
        }
    }

    // squares
    int sq = mySqrt(sz);
    int offset_i = 0;
    int offset_j = 0;
    for (int q = 0; q < sz; ++q) {
        clear(cnt, n);
        for (int i = 0; i < sq; ++i) {
            for (int j = 0; j < sq; ++j) {
                if (getValue(game->matrix, i + offset_i, j + offset_j) == NONE) {
                    continue;
                }
                ++cnt[getValue(game->matrix, i + offset_i, j + offset_j)];
                if (cnt[getValue(game->matrix, i + offset_i, j + offset_j)] > 1) {
                    return 0;
                }
            }
        }

        // end of for
        offset_j += sq;
        if (offset_j >= sq * sq) {
            offset_j = 0;
            offset_i += sq;
        }
    }

    return 1;
}

int check(Game* game) {
    return (isCorrect(game) && game->cntNumbers == game->matrix->n * game->matrix->n);
}

int isValid(Game* game, int i, int j, int val) {
    int n = game->matrix->n;

    // row
    for (int k = 0; k < n; ++k) {
        if (getValue(game->matrix, i, k) == val) {
            return 0;
        }
    }

    // col
    for (int k = 0; k < n; ++k) {
        if (getValue(game->matrix, k, j) == val) {
            return 0;
        }
    }

    // square
    int sq = mySqrt(n);
    int offset_i = i - i % sq;
    int offset_j = j - j % sq;
    for (int k1 = 0; k1 < sq; ++k1) {
        for (int k2 = 0; k2 < sq; ++k2) {
            if (getValue(game->matrix, k1 + offset_i, k2 + offset_j) == val) {
                return 0;
            }
        }
    }
    return 1;
}

void clearBoard(Game* game) {
    game->cntNumbers = 0;
    int n = game->matrix->n;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            setValue(game->matrix, i, j, NONE);
            setValue(game->access, i, j, 1);
        }
    }
}

void reset(Game* game) {
    int n = game->matrix->n;
    int cnt = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (getValue(game->access, i, j)) {
                setValue(game->matrix, i, j, NONE);
            } else {
                ++cnt;
            }
        }
    }
    game->cntNumbers = cnt;
}

void generateBoard(Game* game) {
    int n = game->matrix->n;
    int from = 29;
    int to = 37;
    if (n != 9) {
        from = 5;
        to = 8;
    }
    int cntNumbers = randInt(from, to);

    while (1) {
        int i = randInt(0, n - 1);
        int j = randInt(0, n - 1);
        if (getValue(game->matrix, i, j) == NONE) {
            int tmp = randInt(1, n);
            if (isValid(game, i, j, tmp)) {
                setValue(game->matrix, i, j, tmp);
                setValue(game->access, i, j, 0);
                ++game->cntNumbers;
            }
        }
        
        if (game->cntNumbers == cntNumbers) {
            if (findSolution(game)) {
                reset(game);
                break;
            } else {
                clearBoard(game);
            }
        }
    }
}


int findSolution(Game* game) {
    int n = game->matrix->n;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (getValue(game->matrix, i, j) == NONE) {
                for (int var = 1; var <=n; ++var) {
                    if (isValid(game, i, j, var)) {
                        setValue(game->matrix, i, j, var);
                        ++game->cntNumbers;
                        if (findSolution(game)) {
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