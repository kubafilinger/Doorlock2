#ifndef __KEYBOARD_H__
#define __KEYBOARD_H__

#ifndef F_CPU
#define F_CPU 8000000L
#endif

#include <util/delay.h>

class Keyboard
{
	volatile uint8_t* ddr;
	volatile uint8_t* port;
	volatile uint8_t* pin;
	char key;
	char keyboard[4][4] = {
		{'1', '2', '3', 'A'},
		{'4', '5', '6', 'B'},
		{'7', '8', '9', 'C'},
		{'*', '0', '#', 'D'}
	};

public:
	Keyboard(volatile uint8_t*, volatile uint8_t*, volatile uint8_t*);
	~Keyboard();
	char catchKey();
	char getKey();
	void setKey(char);
};

#endif //__KEYBOARD_H__
