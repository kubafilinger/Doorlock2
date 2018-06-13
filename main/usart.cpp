#include "usart.h"

// Interrupt generated when transmission buffer is already empty
ISR(USART_UDRE_vect)
{
	UDR = *usartMsg++;

	if(*usartMsg == 0)
		UCSRB &= ~(1 << UDRIE); //disable interrupt
}

void defineBaud()
{
	#define BAUD 9600
	#include <util/setbaud.h>

	UBRRH = UBRRH_VALUE;
	UBRRL = UBRRL_VALUE;
	#if USE_2X
	UCSRA |= (1 << U2X);
	#else
	UCSRA &= ~(1 << U2X);
	#endif
}

void usartInit()
{
	defineBaud();

	UCSRC = (1 << URSEL) | (1 << UCSZ1) | (1 << UCSZ0);

	// enable only TX
	UCSRB = (1 << TXEN);
}

void send(char* ch)
{
	usartMsg = ch;
	UCSRB |= (1 << UDRIE); // enable interrupt of send
} 