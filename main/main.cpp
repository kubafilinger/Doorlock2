#include "consts.h"
#include <avr/io.h>
#include <avr/eeprom.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "HD44780.c"
#include "helpers.h"
#include "User.h"
#include "Door.h"
#include "Servo.h"
#include "Keyboard.h"
#include "Menu.h"

enum States {
	DISPLAY,
	WAIT
};

EEMEM char stringUsers[SMALL_BUFFER_SIZE	];

User* users[MAX_NUM_OF_USERS];
uint8_t usersIndex = 0;

int main(void)
{
	DDRB = (1 << LED_RED) | (1 << LED_GREEN) | (1 << SERVO_PIN) | (1 << G1);
	PORTB = ~((1 << LED_RED) | (1 << LED_GREEN) | (1 << SERVO_PIN));

	User *loggedUser = NULL;
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
	Menu *mainMenu = new Menu();

	char buffor[SMALL_BUFFER_SIZE];
	char* tmpBuff = new char[SMALL_BUFFER_SIZE]; // todo: jakos inaczej to rozwiazac, bo ja juz nie bede potrzebowal tej zmiennej po odczytaniu userow
	uint8_t buffIndex = 0, tmpBuffIndex = 0;

	eeprom_read_block(buffor, stringUsers, sizeof(stringUsers));

	for(char* serial = buffor; *serial; ++serial) {
		if(*serial == ';') {
			tmpBuff[tmpBuffIndex++] = '\0';

			users[usersIndex++] = new User(tmpBuff);

			tmpBuffIndex = 0;
		} else {
			tmpBuff[tmpBuffIndex++] = *serial;
		}
	}

	delete tmpBuff; // czy nie trzeba przypadkiem delete []tempBuff

	//todo: zczytanie z pamieci EEPROM zserializowanych userow i zapisanie ich do tablicy
	users[usersIndex++] = new User();
	(users[usersIndex - 1])->setCode("5555");
	(users[usersIndex - 1])->setName("Kubiszon");

    while (1) {
		if(state == WAIT) { // wait for user interaction
			if(keyboard->catchKey()) {
				char key = keyboard->getKey();

				if(loggedUser != NULL && loggedUser->isLogged()) {
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
								loggedUser->logout();
							}
							else {
								mainMenu->setChoose(NO_OPTIONS);
							}

							state = DISPLAY;
							break;

						case ENTER: // go to in or apply operation
							mainMenu->setChoose(mainMenu->getField());

							if(mainMenu->getChoose() == ADD_USER && buffIndex == MAX_CODE_LENGTH) {
								/*
									todo: wprowadzenie oraz sprawdzenie unikalnosci kodu i zapisanie do eeprom usera
								*/

								User *newUser = new User();
								users[usersIndex++] = newUser;

								newUser->setCode(buffor);
								newUser->setName("oczek");

								for(int i = 0; i < usersIndex; i++) {
									char serializedUser[SMALL_BUFFER_SIZE];

									users[i]->toString(serializedUser);

									strcat(buffor, serializedUser);
									strcat(buffor, ";");
								}

								eeprom_write_block(buffor, stringUsers, sizeof(buffor));

								LCD_Clear();
								LCD_WriteText(newUser->getName());
							} else if(mainMenu->getChoose() == LOGOUT) {
								loggedUser->logout();
								mainMenu->reset();
							}

							// always clear buffor after entered action
							buffIndex = 0;

							state = DISPLAY;
							break;

						default:
							if(mainMenu->getChoose() == ADD_USER) {
								if(buffIndex < MAX_CODE_LENGTH) {
									LCD_WriteData('*');
									buffor[buffIndex++] = key;
								}
							} else {
								buffor[buffIndex++] = key;
							}

							buffor[buffIndex] = '\0';

							break;
					}
				} else {
					switch(key) {
						case BACK:
							buffIndex = 0;
							state = DISPLAY;
							break;

						case ENTER:
							for(int i = 0; i < usersIndex; i++) {
								if(users[i]->login(buffor)) {
									loggedUser = users[i];
								}
							}

							buffIndex = 0;
							state = DISPLAY;
							break;

						default:
							if(buffIndex < MAX_CODE_LENGTH) {
								LCD_WriteData('*');
								buffor[buffIndex++] = key;
							}

							buffor[buffIndex] = '\0';
					}
				}
			}
		} else if(state == DISPLAY) { // display information
			if(loggedUser != NULL && loggedUser->isLogged()) {
				LCD_Clear();
				LCD_Home();

				if(mainMenu->getChoose() == NO_OPTIONS) {
					char txt[200];
					sprintf(txt, "Witaj %s", loggedUser->getName());

					LCD_WriteText(txt);
					LCD_GoTo(0, 1);
					//LCD_WriteText(static_cast<char>(mainMenu.pos + 48));
					LCD_WriteText(mainMenu->getLang());
				} else if(mainMenu->getChoose() == ADD_USER) {
					char txt[200];
					sprintf(txt, "<- %s", mainMenu->getLang());

					LCD_WriteText("<- Dodaj usera");
					LCD_GoTo(0, 1);
					LCD_WriteText("Kod:");
				}

				PORTB |= 1 << LED_GREEN;
				PORTB &= ~(1 << LED_RED);

				state = WAIT;

				//todo: display menu
			} else {
				LCD_Clear();
				LCD_Home();
				LCD_WriteText("PIN:"); //todo: datatime display
				LCD_GoTo(0, 1);
				//char txt[200];
				//sprintf(txt, "%d %d %d", sizeof(User), sizeof(Keyboard) ,sizeof(Door));
				//LCD_WriteText(txt);

				PORTB |= 1 << LED_RED;
				PORTB &= ~(1 << LED_GREEN);

				state = WAIT;
			}
		}
	}
}