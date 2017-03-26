#ifndef _FORMOTORCONTROLH
#define _FORMOTORCONTROLH

// Servo library controls the motor
// More details covered by the controlMotors() function
#include <Servo.h>

// Servo instantiation
Servo leftMotor;
Servo rightMotor;

// Motor control stuff
const int   MOTOR_STOP = 90;
const float SPEED_MULTI = 0.35;
const float MAX_FORWARD_SPEED = 0.5; // m/s
const float MAX_ROTATIONAL_SPEED = 10; // rot/s
const float HALF_TANK_WIDTH = 0.5; //m

#endif // _FORMOTORCONTROLH
