#ifndef __SERVO_H__
#define __SERVO_H__

#include <inttypes.h>

class Servo
{
	uint8_t port;
	float position;

public:
	Servo(uint8_t);
	~Servo();
	void move(float);
	float getPosition();
};

#endif //__SERVO_H__
