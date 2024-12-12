#ifndef PRINT_HELPERS
#define PRINT_HELPERS

#include <termios.h>
#include <unistd.h>
#include "Matrix.h"
#include "Vector.h"
#include "Game.h"
#define NONE 0
#define DELAY 100000

/* перевод терминала в режим, когда: 
1) Ввод с клавиатуры не печатается в терминал
2) Не требуется наажтия Enter для ввода символа (он сразу после нажатия в stdin)
3) Выключено "мигание" курсора */
void setInputMode();

/* возврат в исходный режим */
void resetInputMode();

/*  Печатает матрицу (поле судоку) по "вектору"
Необходимо чтобы распечатанная матрица "помещалась" в поле, которое задает вектор.
Вектор и курсур будут возвращены в исходное состоянии по завершении процедуры. */
void printGame(Game* game, Vector* v);

/* печатает символ в определенной точке поля. Курсор остается там же,
где был до печати в независимости от (x, y) */
void printChar(Vector* v, int x, int y, char ch);

/* убирает [ ] с текущего положения вектора,
перемещает вектор в (a, b) и обрамляет новое положение в [ ] */
void moveCursor(Vector* v, int a, int b);

/* обрамляет текущее положение курсора в [ ] */
void showPosition(Vector* v);

/* скрывает [ ] в позиции, на которую указывает курсор */
void hidePosition(Vector* v);

/* решение судоку с анимацией. Задержка DELAY*/
int solve(Game* game, Vector* v);
#endif