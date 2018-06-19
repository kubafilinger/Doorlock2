#include "Servo.h"

/**
 * Constructor
 *
 * @param volatile uint8_t* ddr
 * @param volatile uint8_t* port
 * @param uint8_t pin
 */
Servo::Servo(volatile uint8_t* ddr, volatile uint8_t* port, uint8_t pin)
{
	this->ddr = ddr;
	this->port = port;
	this->pin = pin;

	*(this->ddr) |= (1 << this->pin); //set out on servo pin
}

/**
 * Destructor
 */
Servo::~Servo()
{
}

/**
 * @param float position
 */
void Servo::move(float position) {
	if(position >= 0.0 && position <= 180.0) {
		this->position = position;

		const int highPulseTime = mapValue(static_cast<int>(position), 0, 180, 1000, 2000);

		for(int i = 0; i < 10; i++) {
			*(this->port) |= (1 << this->pin);
			delay_us(highPulseTime);

			*(this->port) &= ~(1 << this->pin);
			delay_us(20000 - highPulseTime);
		}
	}
}

/**
 * @return float
 */
float Servo::getPosition() {
	return this->position;
}