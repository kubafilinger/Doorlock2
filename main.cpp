#define F_CPU 8000000L

#include <avr/io.h>
#include <stdio.h>
#include <stdlib.h>
#include "User.h"
#include "Door.h"
#include "Servo.h"

#define G1 PINB3
#define LED_RED PINB1
#define LED_GREEN PINB2
#define SERVO_PIN PINB0

void * operator new(size_t size);
void operator delete(void * ptr);

int main(void)
{
	DDRB = (1 << LED_RED) | (1 << LED_GREEN) | (1 << SERVO_PIN) | (1 << G1);
	PORTB = ~((1 << LED_RED) | (1 << LED_GREEN) | (1 << SERVO_PIN));
	
    User *kuba = new User;
	Servo *servo = new Servo(SERVO_PIN);
	Door *door = new Door(servo);

//logowanie
/*
    if(kuba->login(1234)) {
		PORTB |= (1 << LED_GREEN);
    } else {
		PORTB |= (1 << LED_RED);
	}
	*/

// test otwierania drzwi
	//door->open();
	
	if(servo->getPosition() == 160)
		PORTB |= (1 << LED_GREEN);
	else 
		PORTB |= (1 << LED_RED);

    while (1) {
		
	}
}

void * operator new(size_t size)
{
	return malloc(size);
}

void operator delete(void * ptr)
{
	free(ptr);
}