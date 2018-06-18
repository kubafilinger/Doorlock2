#include "Door.h"

/**
 * @param servo
 */
Door::Door(Servo* servo)
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

/**
 * @return bool
 */
bool Door::getState() {
	return this->state;
}

/**
 * @return bool
 */
bool Door::getLock() {
	return this->lock;
}