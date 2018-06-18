#ifndef HELPERS_H_
#define HELPERS_H_

#include "consts.h"
#include <stdlib.h>

void * operator new(size_t);
void * operator new[](size_t);
void operator delete(void *);
void operator delete[](void *);

#endif