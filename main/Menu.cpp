#include "Menu.h"

Menu::Menu()
{
	this->choose = NO_OPTIONS;
	this->position = 0;
}

Menu::~Menu()
{
}

/**
 * @return int
 */
int Menu::countFields() {
	return sizeof(this->fields)/sizeof(*this->fields);
}

/**
 *
 * @param Values choose
 */
void Menu::setChoose(Values choose) {
	this->choose = choose;
}

/**
 *
 * @return Values
 */
Values Menu::getChoose() {
	return this->choose;
}

/**
 *
 * @return char*
 */
char *Menu::getLang() {
	return this->langs[this->position];
}

/**
 *
 * @return int
 */
int Menu::getPostion() {
	return this->position;
}

int Menu::levelUp() {
	if(this->position > 0) this->position--;
}

int Menu::levelDown() {
	if(this->position + 1 < this->countFields()) this->position++;
}

/**
 * @return Values
 */
Values Menu::getField() {
	return this->fields[this->position];
}

void Menu::reset() {
	this->choose = NO_OPTIONS;
	this->position = 0;
}