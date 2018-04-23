#define F_CPU 8000000L
#define G1 PINB3
#define LED_RED PINB1
#define LED_GREEN PINB2
#define SERVO_PIN PINB0
#define UP 'A'
#define DOWN 'B'
#define BACK 'C'
#define ENTER 'D'
#define MAX_CODE_LENGTH 4

#include <avr/io.h>
#include <stdio.h>
#include <stdlib.h>
#include "HD44780.c"
#include "User.h"
#include "Door.h"
#include "Servo.h"
#include "Keyboard.h"
#include "Menu.h"

void * operator new(size_t size);
void operator delete(void * ptr);

enum States {
	DISPLAY,
	WAIT
};

struct Code {
	char *code;
	uint8_t pos;	
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


// test otwierania drzwi
	//door->open();
	/*
	if(servo->getPosition() == 160)
		PORTB |= (1 << LED_GREEN);
	else 
		PORTB |= (1 << LED_RED);
*/
	
	States state = DISPLAY;
	Code enteredCode;
	Menu *mainMenu = new Menu();
	
	enteredCode.code = "";
	enteredCode.pos = 0;

    while (1) {
		if(state == WAIT) { // wait for user interaction
			if(keyboard->catchKey()) {
				char key = keyboard->getKey();
				
				if(user->isLogged()) {
					switch(key) {
						case UP: // up in menu
							mainMenu->levelUp();
								
							state = DISPLAY;
							break;
						
						case DOWN: // down in menu
							mainMenu->levelDown();
								
							state = DISPLAY;
							break;
						
						case BACK: // back in menu and cancel operation
							if(mainMenu->getChoose() == NO_OPTIONS) { // you have not selected any menu fiels
								user->logout();
							}
							else {
								mainMenu->setChoose(NO_OPTIONS);
							}
							
							state = DISPLAY;
							break;
							
						case ENTER: // go to in or apply operation
							mainMenu->setChoose(mainMenu->getField());
							
							state = DISPLAY;
							break;
					
						default:
							break;
					}
				} else {
					switch(key) {
						case BACK:
							enteredCode.pos = 0;
							enteredCode.code = "";
							state = DISPLAY;
							break;
							
						case ENTER:
							user->login(enteredCode.code);
							enteredCode.pos = 0;
							enteredCode.code = "";
							state = DISPLAY;
							break;
							
						default:
							if(enteredCode.pos < MAX_CODE_LENGTH) {
								LCD_WriteData('*');
								enteredCode.code[enteredCode.pos++] = key;
							}
					}
				}
			}
		} else if(state == DISPLAY) { // display information
			if(user->isLogged()) {
				LCD_Clear();
				LCD_Home();
				
				if(mainMenu->getChoose() == NO_OPTIONS) {
					char txt[200];
					sprintf(txt, "Witaj %s", user->getName());
				
					LCD_WriteText(txt);
					LCD_GoTo(0, 1);
					//LCD_WriteText(static_cast<char>(mainMenu.pos + 48));
					LCD_WriteText(mainMenu->getLang());
				} else if(mainMenu->getChoose() == ADD_USER) {
					char txt[200];
					sprintf(txt, "<- %s", mainMenu->getLang());

					LCD_WriteText("<- Dodaj usera");
					LCD_GoTo(0, 1);
					LCD_WriteText("Nazwa: ");
				}
				
				PORTB |= 1 << LED_GREEN;
				PORTB &= ~(1 << LED_RED);
				
				state = WAIT;
			
				//todo: display menu
			} else {
				LCD_Clear();
				LCD_Home();
				LCD_WriteText("PIN:"); //todo: datatime display
				LCD_GoTo(5, 0);
				
				PORTB |= 1 << LED_RED;
				PORTB &= ~(1 << LED_GREEN);
				
				state = WAIT;
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