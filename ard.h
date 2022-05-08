#ifndef ARD_H_INCLUDED
#define ARD_H_INCLUDED
#include "gamehead.h"

int arduinoWriteData(int x);
int arduinoReadData(int *x);
int arduinoReadDataJoyStickPos(int *x, int *y, int *state);
#endif