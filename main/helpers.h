#ifndef HELPERS_H_
#define HELPERS_H_

#include "consts.h"
#include <stdlib.h>
#include <util/delay.h>

void * operator new(size_t);
void * operator new[](size_t);
void operator delete(void *);
void operator delete[](void *);

int mapValue(int, int, int, int, int);
float mapValue(float, float, float, float, float);
void delay_ms(int);
void delay_us(int);

#endif