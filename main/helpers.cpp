#include "helpers.h"

void * operator new(size_t size)
{
	return malloc(size);
}

void * operator new[](size_t size)
{
	return malloc(size);
}

void operator delete(void * ptr)
{
	(ptr);
}

char * stringCopy(char *txt) {
	char *copy = new char[SMALL_BUFFER_SIZE]();
	int index = 0;

	for(txt; *txt; ++txt) {
		if(index >= SMALL_BUFFER_SIZE)
			break;

		copy[index++] = *txt;
	}

	return copy;
}