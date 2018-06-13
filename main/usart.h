#ifndef USART_H_
#define USART_H_

#ifndef F_CPU
#define F_CPU 8000000L
#endif

#include <avr/interrupt.h>
#include <avr/io.h>

volatile char* usartMsg;

void defineBaud();

/*
Data bits:
	5-bit:
	6-bit: (1 << UCSZ0)
	7-bit: (1 << UCSZ1)
	8-bit: (1 << UCSZ1) | (1 << UCSZ0)
	9-bit: (1 << UCSZ2) | (1 << UCSZ1) | (1 << UCSZ0)

Stop bits:
	1-bit:
	2-bit: (1 << USBS)

Asynchronous:
Synchronous: (1 << UMSEL)
*/
void usartInit();
void send(char*);

#endif