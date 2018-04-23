#include "Menu.h"

Menu::Menu()
{
	this->choose = NO_OPTIONS;
	this->position = 0;
}

Menu::~Menu()
{
}

int Menu::countFields() {
	return sizeof(this->fields)/sizeof(*this->fields);
}

void Menu::setChoose(Values choose) {
	this->choose = choose;
}

Values Menu::getChoose() {
	return this->choose;
}

char *Menu::getLang() {
	return this->langs[this->position]; 
}

int Menu::getPostion() {
	return this->position;
}

int Menu::levelUp() {
	if(this->position > 0) this->position--;
}

int Menu::levelDown() {
	if(this->position + 1 < this->countFields()) this->position++;
}

Values Menu::getField() {
	return this->fields[this->position];
}