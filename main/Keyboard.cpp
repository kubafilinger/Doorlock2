#include "Keyboard.h"

Keyboard::Keyboard(volatile uint8_t * ddr, volatile uint8_t * port, volatile uint8_t * pin) {
	this->ddr = ddr;
	this->port = port;
	this->pin = pin;
	this->up = 'A';
	this->down = 'B';
	this->back = 'C';
	this->enter = 'D';
	this->key = 0;
	
	*(this->ddr) = 0b00001111;
	*(this->port) = 0b11111111;
}

Keyboard::~Keyboard() {
}

char Keyboard::catchKey() {
	int i, j;
	
	for(i = 0; i < 4; i++)
	{
		*(this->port) &= ~(1 << i);

		for(j = 0; j < 4; j++)
		{
			if(!(*(this->pin) & (1 << (j + 4))))
			{
				this->setKey(this->keyboard[3 - j][3 - i]);
				
				_delay_ms(20);
				while(!(*(this->pin) & (1 << (j + 4))));
				
				return this->key;
			}
		}

		*(this->port) |= (1 << i);
	}
	
	return 0;
}

void Keyboard::setKey(char key) {
	this->key = key;
}

char Keyboard::getKey() {
	return this->key;
}