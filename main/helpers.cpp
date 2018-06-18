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