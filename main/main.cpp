#define F_CPU 8000000L

#include <avr/io.h>
#include <stdio.h>
#include <stdlib.h>
#include "HD44780.c"
#include "User.h"
#include "Door.h"
#include "Servo.h"
#include "Keyboard.h"

#define G1 PINB3
#define LED_RED PINB1
#define LED_GREEN PINB2
#define SERVO_PIN PINB0
#define UP 'A'
#define DOWN 'B'
#define BACK 'C'
#define ENTER 'D'
#define MAX_CODE_LENGTH 4

void * operator new(size_t size);
void operator delete(void * ptr);

struct Menu {
	uint8_t level;
	uint8_t wait;
	};

int main(void)
{
	DDRB = (1 << LED_RED) | (1 << LED_GREEN) | (1 << SERVO_PIN) | (1 << G1);
	PORTB = ~((1 << LED_RED) | (1 << LED_GREEN) | (1 << SERVO_PIN));
	
    User *user = new User;
	Servo *servo = new Servo(SERVO_PIN);
	Door *door = new Door(servo);
	Keyboard *keyboard = new Keyboard(&DDRC, &PORTC, &PINC);
	
	LCD_Initalize();

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

	Menu menu;
	menu.level = 0;
	menu.wait = 0; // zabezpieczenie przed ciaglym ustawianiu wyswietlacza

	char *code = "";
	int code_pos = 0;

    while (1) {
		if(menu.wait) {
			if(user->isLogged()) {
				
			} else {
				if(keyboard->catchKey()) {
					char key = keyboard->getKey();
					
					switch(key) {
						case ENTER:
							LCD_Clear();
							LCD_WriteText(code);
							
							if(user->login(code)) {
								menu.wait = 0;
							}
							
							code_pos = 0;
							code = "";
							
							//todo: check pin
							break;
						case BACK:
							LCD_Clear();
							LCD_WriteText("back");
							
							code_pos = 0;
							code = "";
							
							//todo: reset pin
							break;
						default:
							LCD_Clear();
							LCD_WriteText("cyfra");
							
							if(code_pos < MAX_CODE_LENGTH) {
								code[code_pos++] = key;
							}
							
							break;
					}
				}
			}
		} else {
			if(user->isLogged()) {
				LCD_Clear();
				LCD_Home();
				char txt[200];
				sprintf(txt, "Witaj %s", user->getName());
				
				LCD_WriteText(txt);
				//LCD_GoTo(1, 0);
			
				menu.wait = 1;
			
				// display menu
			} else {
				LCD_Clear();
				LCD_Home();
				LCD_WriteText("Data:"); //todo: datatime display
			
				menu.wait = 1;
			}
		}
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