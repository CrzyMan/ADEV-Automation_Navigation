#ifndef _FORMOTORCONTROLH
#define _FORMOTORCONTROLH

// Servo library controls the motor
// More details covered by the controlMotors() function
#include <Servo.h>

// Servo instantiation
Servo leftMotor;
Servo rightMotor;

// Motor control stuff
//  Motor command: tells the motor to full stop
const int   MOTOR_STOP = 90;

// Constant that multiplies the maximum speed of the robot
const float SPEED_MULTI = 0.35;

// Sets the maximum forwad speed of the robot
// Is more representative than actual speed
const float MAX_FORWARD_SPEED = 0.5; // m/s

// Sets the maximum turning speed of the robot
// Is more representative than actual speed
const float MAX_ROTATIONAL_SPEED = 10; // rot/s

// This value is used to control the turning
// The bigger the value, the harder it turns
const float HALF_TANK_WIDTH = 0.55; //m

#endif // _FORMOTORCONTROLH
