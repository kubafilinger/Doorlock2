#include "User.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "helpers.h"

User::User()
{
	this->id = 1;
	this->name = "Kubas";
	this->code = "4321";
	this->logged = 0;
	this->role = USER;
}

/**
 * Constructor
 * Validation buffor size and name, code max length was omitted, becouse these are things read from EEPROM and their correctness has already been confirmed before
 *
 * @param char *
 */
User::User(char *serial) {
	char buffor[SMALL_BUFFER_SIZE];
	uint8_t buffIndex = 0;
	uint8_t actionIndex = 0;

	for(serial; *serial; ++serial) {
		if(*serial == ',') {
			buffor[buffIndex++] = '\0';

			switch (actionIndex++)
			{
				case 0:
					this->id = atoi(buffor);
					break;

				case 1:
					this->name = stringCopy(buffor);
					break;

				case 2:
					this->setStringRole(buffor);
					break;

				case 3:
					this->code = stringCopy(buffor);
					break;
			}

			buffIndex = 0;
		} else {
			buffor[buffIndex++] = *serial;
		}
	}
}

User::~User()
{
// free name
// free code
// free others....
}

/**
 * @param code
 * @return int
 */
int User::login(char *code) {
	//todo: tutaj byla zmiana zobaczyc czy dziala ok
	if(!strcmp(code, this->code))
		this->logged = 1;

	return this->isLogged();
}

void User::logout() {
	this->logged = 0;
}

void User::remove() {

}

/**
 * @param name
 */
void User::setName(char *name) {
	//todo:
	//validate name?

	this->name = name;
}

/**
 * @return char*
 */
char *User::getName() {
	return this->name;
}

/**
 * @return char*
 */
char *User::getCode() {
	return this->code;
}

/**
 * @param code
 */
void User::setCode(char *code) {
	this->code = code;
}

/**
 * @return int
 */
int User::isLogged() {
	return this->logged;
}

Roles User::getRole() {
	return this->role;
}

char *User::getStringRole() {
	char* result;

	switch(this->role) {
		case USER:
			result = "USER";
			break;
		case SUPER_ADMIN:
			result = "SUPER_ADMIN";
			break;
		case LOL:
			result = "LOL";
			break;
		default:
			result = "";
	}

	return result;
}

void User::setStringRole(char *stringRole) {
	if(!strcmp(stringRole, "USER"))
		this->role = USER;
	else if(!strcmp(stringRole, "SUPER_ADMIN"))
		this->role = SUPER_ADMIN;
	else
		this->role = USER;
}

void User::setRole(Roles role) {
	this->role = role;
}

void User::save() {

}

char *User::toString(char *txt) {

	sprintf(txt, "%d,%s,%s,%s,\0", this->id, this->name, this->getStringRole(), this->code);

	return txt;
}

int User::getId() {
	return this->id;
}