#ifndef __DOOR_H__
#define __DOOR_H__

#include "Servo.h"

class Door
{
	Servo *servo;
	bool state; // open or close
	bool lock; // lock or unlock

public:
	Door(Servo*);
	~Door();
	void open();
	void close();
	bool getState();
	bool getLock();	
};

#endif //__DOOR_H__
