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

EEMEM char stringUsers[SMALL_BUFFER_SIZE	];

User* users[MAX_NUM_OF_USERS];
uint8_t usersIndex = 0;

void readUsersFromEeprom();
void writeUsersToEeprom();

int main(void)
{
	DDRB = (1 << LED_RED) | (1 << LED_GREEN) | (1 << SERVO_PIN) | (1 << G1);
	PORTB = ~((1 << LED_RED) | (1 << LED_GREEN) | (1 << SERVO_PIN));

	User *loggedUser = NULL;
	Servo *servo = new Servo(SERVO_PIN);
	Door *door = new Door(servo);
	Keyboard *keyboard = new Keyboard(&DDRC, &PORTC, &PINC);
	States state = DISPLAY;
	Menu *mainMenu = new Menu();
	Info info = NONE;

	char buffor[SMALL_BUFFER_SIZE];
	uint8_t buffIndex = 0;


	LCD_Initalize();

	// test otwierania drzwi
	//door->open();
	/*
	if(servo->getPosition() == 160)
		PORTB |= (1 << LED_GREEN);
	else
		PORTB |= (1 << LED_RED);
	*/

	//readUsersFromEeprom();

	//todo: do usuniecia gdzy zadzia³a eeprom
	users[usersIndex++] = new User();
	(users[usersIndex - 1])->setCode("5555");
	(users[usersIndex - 1])->setName("Kuba");
	(users[usersIndex - 1])->setRole(SUPER_ADMIN);

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
							if(mainMenu->getChoose() == NO_OPTIONS) { // you have not selected any menu fields
								loggedUser->logout();
								loggedUser = NULL;
							}
							else {
								mainMenu->setChoose(NO_OPTIONS);
							}

							state = DISPLAY;
							break;

						case ENTER: // go to in or apply operation
							mainMenu->setChoose(mainMenu->getField());

							if(mainMenu->getChoose() == ADD_USER) {
								if(loggedUser->getRole() == SUPER_ADMIN) {
									if(buffIndex == MAX_CODE_LENGTH) {
										for(int i = 0; i < usersIndex; i++) {
											if(!strcmp(users[i]->getCode(), buffor)) {
												// always clear buffor after entered action
												buffIndex = 0;

												info = SAME_CODE;
												state = ALERT;
												break;
											}
										}

										if(state == ALERT)
											break;

										User *newUser = new User();
										users[usersIndex++] = newUser;

										newUser->setCode(buffor);
										newUser->setName("Nowy");

										//writeUsersToEeprom();

										buffIndex = 0;

										info = USER_ADDED;
										state = ALERT;
										break;
									}
								} else {
									mainMenu->reset();

									info = ACCESS_DENIED;
									state = ALERT;
									break;
								}
							} else if(mainMenu->getChoose() == LOGOUT) {
								loggedUser->logout();
								loggedUser = NULL;
								mainMenu->reset();
							} else if(mainMenu->getChoose() == CHANGE_CODE) {
								if(buffIndex == MAX_CODE_LENGTH) {
									for(int i = 0; i < usersIndex; i++) {
										if(!strcmp(users[i]->getCode(), buffor)) {
											buffIndex = 0;

											info = SAME_CODE;
											state = ALERT;
											break;
										}
									}

									if(state == ALERT)
										break;

									loggedUser->setCode(buffor);

									//writeUsersToEeprom();

									buffIndex = 0;

									info = CODE_CHANGED;
									state = ALERT;
									break;
								}
							}

							// always clear buffor after entered action
							buffIndex = 0;

							state = DISPLAY;
							break;

						default:
							if(mainMenu->getChoose() == ADD_USER || mainMenu->getChoose() == CHANGE_CODE) {
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

						case ENTER: // loggin
							for(int i = 0; i < usersIndex; i++) {
								if(users[i]->login(buffor)) {
									loggedUser = users[i];
								}
							}

							if(loggedUser != NULL) {
								state = DISPLAY;
							} else {
								info = BAD_CODE;
								state = ALERT;
							}

							buffIndex = 0;
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
					LCD_WriteText(mainMenu->getLang());
				} else if(mainMenu->getChoose() == ADD_USER) {
					char txt[200];
					sprintf(txt, "<- %s", mainMenu->getLang());

					LCD_WriteText("<- Dodaj usera");
					LCD_GoTo(0, 1);
					LCD_WriteText("Kod:");
				} else if(mainMenu->getChoose() == CHANGE_CODE) {
					char txt[200];
					sprintf(txt, "<- %s", mainMenu->getLang());

					LCD_WriteText("<- Zmien kod");
					LCD_GoTo(0, 1);
					LCD_WriteText("Now kod:");
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

				PORTB |= 1 << LED_RED;
				PORTB &= ~(1 << LED_GREEN);

				state = WAIT;
			}
		} else if(state == ALERT) {
			LCD_Clear();
			LCD_Home();

			if(info == BAD_CODE) {
				LCD_WriteText("ERROR:");
				LCD_GoTo(0, 1);
				LCD_WriteText("Zly pin");
			} else if(info == SAME_CODE) {
				LCD_WriteText("ERROR:");
				LCD_GoTo(0, 1);
				LCD_WriteText("Kod juz istnieje");
			} else if(info == ACCESS_DENIED) {
				LCD_WriteText("ERROR:");
				LCD_GoTo(0, 1);
				LCD_WriteText("Brak dostepu");
			} else if(info == USER_ADDED) {
				LCD_WriteText("INFO:");
				LCD_GoTo(0, 1);
				LCD_WriteText("User dodany");
			} else if(info == CODE_CHANGED) {
				LCD_WriteText("INFO:");
				LCD_GoTo(0, 1);
				LCD_WriteText("Kod zmieniony");
			} else {
				LCD_WriteText("Nieznany");
			}

			_delay_ms(3000);
			state = DISPLAY;
		}
	}
}

void readUsersFromEeprom() {
	char buffor[SMALL_BUFFER_SIZE];
	char tmpBuff[SMALL_BUFFER_SIZE];
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
}

void writeUsersToEeprom() {
	char buffor[SMALL_BUFFER_SIZE];
	uint8_t buffIndex = 0;

	for(int i = 0; i < usersIndex; i++) {
		char serializedUser[SMALL_BUFFER_SIZE];
		serializedUser[0] = '\0';

		users[i]->toString(serializedUser);

		strcat(buffor, serializedUser);
		strcat(buffor, ";");
	}

	eeprom_write_block(buffor, stringUsers, sizeof(buffor));
}