#include "helpers.h"

/**
 * @param size_t size
 * @return
 */
void * operator new(size_t size)
{
	return malloc(size);
}

/**
 * @param size_t size
 * @return
 */
void * operator new[](size_t size)
{
	return malloc(size);
}

/**
 * @param void* ptr
 */
void operator delete(void * ptr)
{
	free(ptr);
}

/**
 * @param void* ptr
 */
void operator delete[](void * ptr)
{
	free(ptr);
}

int mapValue(int val, int fromMin, int fromMax, int toMin, int toMax)
{
	return (val - fromMin) * (toMax - toMin) / (fromMax - fromMin) + toMin;
}

float mapValue(float val, float fromMin, float fromMax, float toMin, float toMax)
{
	return (val - fromMin) * (toMax - toMin) / (fromMax - fromMin) + toMin;
}

void delay_ms(int ms) {
	for(int i = 0; i < ms; i++)
		_delay_ms(1);
}

void delay_us(int us) {
	for(int i = 0; i < us; i++)
		_delay_us(1);
}