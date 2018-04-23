#include "User.h"

User::User()
{
	this->id = 1;
	this->name = "Kubas";
	this->code = "1234";
	this->logged = 0;
	this->role = SUPER_ADMIN;
}

User::~User()
{
}

/**
 * @param code
 * @return int
 */
int User::login(char *code) {
	int size = sizeof(this->code) / sizeof(*(this->code));
	
	for(unsigned i = 0; i < size; i++) {
		if(code[i] != (this->code)[i])
			break;
			
		if(i + 1 == size)
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
void User::setCode(char *code) {
	this->code = code;
}

/**
 * @return int
 */
int User::isLogged() {
	return this->logged;
}

Role User::getRole() {
	return this->role;
}

void User::setRole(Role role) {
	this->role = role;
}