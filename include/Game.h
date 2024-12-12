#ifndef GAME_H
#define GAME_H

#include "Matrix.h"

/* внутренний (логический) объект игры. Не осведомлен о терминале */
typedef struct Game {
    Matrix* matrix; // само поле с числами
    Matrix* access; // булева матрица. 1 - можно редактировать, 0 - число из условия
    int cntNumbers; // кол-во чисел в судоку
} Game;

/* конструктор судоку размера size.
Будет корректно инициализированы поля (в т. ч. матриц)
Поле останется не заполненным */
Game* getGame(int size);

/* получение int из char в смысле '5' == 5 */
int getInt(char ch);

/* деструктор */
void deleteGame(Game* game);

/* Заполнение поле судоку. mode == 
1 - поле из датасета 
2 - поле будет сгенерировано случайно */
void startGame(Game* game, int mode);

/* убрать число из судоку на соотв. позиции */
void removeNumb(Game* game, int x, int y);

/* вписать число из судоку на соотв. позицию */
void setNumb(Game* game, int x, int y, int val);

/* 1 - если в поле нет противоречий 3-мя правилами судоку
(нет повторов чисел в строке/столбце/квадрате) 
0 - есть противоречие */
int isCorrect(Game* game);

/* 1 - судоку решено
0 - судоку не решено */
int check(Game* game);

/* сгенерировать поле */
void generateBoard(Game* game);

/* делает поле судоку пустым, без каких-либо заранее заданных чисел */
void clearBoard(Game* game);

/* вернуть игру к состоянию до всяких изменений пользователем */
void reset(Game* game);

/* решить судоку. Поле будет заполнено числами-ответами (будто пользователем)*/
int findSolution(Game* game);

/* будет ли поле непротиворечивым, если вставить val в i-ю строку, j-ий столбец 
1 - корректно 
0 - будет противоречие */
int isValid(Game* game, int i, int j, int val);
#endif