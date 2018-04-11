#include "Servo.h"

Servo::Servo(uint8_t port)
{
	this->port = port;
}

Servo::~Servo()
{
}

void Servo::move(float position) {
	//todo:
	// weryfikacja czy podany kat jest odpowiedni
	
	this->position = position;
	// todo: map angle to adc and move servo
	
}

float Servo::getPosition() {
	return this->position;
}