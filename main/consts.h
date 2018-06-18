#ifndef CONSTS_H_
#define CONSTS_H_

#define F_CPU 8000000L

/**
 * Ports
 */
#define G1 PINB3
#define LED_RED PINB1
#define LED_GREEN PINB2
#define SERVO_PIN PINB0

/**
 * Keyboard
 */
#define UP 'A'
#define DOWN 'B'
#define BACK 'C'
#define ENTER 'D'

/**
 * Sizes
 */
#define BUFFER_SIZE 512
#define SMALL_BUFFER_SIZE 256
#define MAX_NUM_OF_USERS 10

/**
 * Validators
 */
#define MAX_NAME_LENGTH 16
#define MAX_CODE_LENGTH 4

/**
 * Types
 */
enum States {
	DISPLAY,
	WAIT,
	ALERT
};
enum Info {
	NONE,
	BAD_CODE,
	SAME_CODE,
	ACCESS_DENIED,
	USER_ADDED,
	CODE_CHANGED
};

#endif