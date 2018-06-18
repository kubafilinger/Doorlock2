#include "User.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "helpers.h"
#include "HD44780.h"

User::User()
{
	this->id = 1;
	setName("Name");
	setCode("4321");
	this->logged = 0;
	this->role = USER;
}

/**
 * Constructor
 *
 * @param char* serial
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
					//this->name = "Bambo";
					this->setName(buffor);
					break;

				case 2:
					this->setStringRole(buffor);
					break;

				case 3:
					this->code = "5555";
					//this->setCode(buffor);
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
	delete[] this->name;
	delete[] this->code;
}

/**
 * @param char* code
 * @return int
 */
int User::login(char* code) {
	if(!strcmp(code, this->code))
		this->logged = 1;

	return this->isLogged();
}

void User::logout() {
	this->logged = 0;
}

/**
 * @param char* name
 */
void User::setName(char* name) {
	this->name = new char[strlen(name) + 1];
	strcpy(this->name, name);
}

/**
 * @return char*
 */
char* User::getName() {
	return this->name;
}

/**
 * @param char* code
 */
void User::setCode(char* code) {
	this->code = new char[strlen(code) + 1];
	strcpy(this->code, code);
}

/**
 * @return char*
 */
char* User::getCode() {
	return this->code;
}

/**
 * @return int
 */
int User::isLogged() {
	return this->logged;
}

/**
 * @return Roles
 */
Roles User::getRole() {
	return this->role;
}

/**
 * @return char*
 */
char* User::getStringRole() {
	char* result;

	switch(this->role) {
		case USER:
			result = "USER";
			break;
		case SUPER_ADMIN:
			result = "SUPER_ADMIN";
			break;
		default:
			result = "";
	}

	return result;
}

/**
 * @param char* stringRole
 */
void User::setStringRole(char* stringRole) {
	if(!strcmp(stringRole, "USER"))
		this->role = USER;
	else if(!strcmp(stringRole, "SUPER_ADMIN"))
		this->role = SUPER_ADMIN;
	else
		this->role = USER;
}

/**
 * @param Roles role
 */
void User::setRole(Roles role) {
	this->role = role;
}

/**
 * @param char* txt
 * @return char*
 */
char* User::toString(char* txt) {

	sprintf(txt, "%d,%s,%s,%s,\0", this->id, this->name, this->getStringRole(), this->code);

	return txt;
}

/**
 * @return int
 */
int User::getId() {
	return this->id;
}