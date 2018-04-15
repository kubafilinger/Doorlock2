#include "User.h"

User::User()
{
	this->id = 1;
	this->name = "Kuba";
	this->code = 1234;
}

User::~User()
{
}

/**
 * @param code
 * @return bool
 */
bool User::login(int code) {
	if(code == this->code) {
		return 1;
	}
	
	return 0;
}

void User::logout() {
	
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
