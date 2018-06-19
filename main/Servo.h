#ifndef __SERVO_H__
#define __SERVO_H__

#include "consts.h"
#include "helpers.h"

class Servo
{
	volatile uint8_t* ddr;
	volatile uint8_t* port;
	uint8_t pin;
	float position;

public:
	Servo(volatile uint8_t*, volatile uint8_t*, uint8_t);
	~Servo();
	void move(float);
	float getPosition();
};

#endif //__SERVO_H__
