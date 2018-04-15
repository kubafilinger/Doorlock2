#include "Door.h"

Door::Door(Servo *servo)
{
	this->servo = servo;
	this->close();
}

Door::~Door()
{
}

void Door::open() {
	this->servo->move(160);
	this->lock = false;
}

void Door::close() {
	this->servo->move(20);
	this->lock = true;
}

bool Door::getState() {
	return this->state;
}

bool Door::getLock() {
	return this->lock;
}