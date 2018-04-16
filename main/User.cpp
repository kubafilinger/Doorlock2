#include "User.h"

User::User()
{
	this->id = 1;
	this->name = "Kuba";
	this->code = 1234;
	this->logged = 0;
}

User::~User()
{
}

/**
 * @param code
 * @return int
 */
int User::login(int code) {
	if(code == this->code) {
		this->logged = 1;
	}
	
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
 * @param code
 */
void User::setCode(int code) {
	this->code = code;
}

/**
 * @return int
 */
int User::isLogged() {
	return this->logged;
}