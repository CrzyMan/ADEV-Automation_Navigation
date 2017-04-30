#include "_forMotorControl.h"
#include "_forReadings.h"

// Variables to track commands sent to motors
int lastLeftCommand = 0;
int lastRightCommand = 0;

/*
 * This function, controlMotors(), calculates the rotational speed based on the goals and the percentages
 * to calculate the commands for each motor. The calculated commands are then passed to the motors via the
 * sendMotorCommands() function.
 */
void controlMotors(){
  // Calculate rotational speed from goals
  float rotationalSpeed = MAX_ROTATIONAL_SPEED*goals[_goals_turningSpeed];
  // Calculate the percentages to calculate commands
  float leftPercent = goals[_goals_forwardSpeed] * SPEED_MULTI - HALF_TANK_WIDTH * rotationalSpeed/MAX_ROTATIONAL_SPEED;
  float rightPercent = goals[_goals_forwardSpeed] * SPEED_MULTI + HALF_TANK_WIDTH * rotationalSpeed/MAX_ROTATIONAL_SPEED;
  // Calculate commands for each motor
  float leftCommand   = 95.0 - leftPercent * 70.0;
  float rightCommand  = 95.0 - rightPercent * 70.0;
  // Send commands to motors
  sendMotorCommands((int) leftCommand, (int) rightCommand);
}

/*
 * The arguments for the function, sendMotorCommands(), are two commands one for the left motor and the right motor.
 * The arguments are only passed on to the motors if they are different than what was last passed.
 */
void sendMotorCommands(int leftCommand, int rightCommand){
  //Check if repeat command
  if (leftCommand != lastLeftCommand){
    leftMotor.write(leftCommand);
    lastLeftCommand = leftCommand;
    //Printing left command for debugging
    Serial.println(leftCommand);
  }
  //Check if repeat command
  if (rightCommand != lastRightCommand){
    rightMotor.write(rightCommand);
    lastRightCommand = rightCommand;
    //Printing right command for debugging
    Serial.println(rightCommand);
  }
}

/*  
 * This function, motorSetup(), is responsible for attaching the motors to the associated pins on the arduino.  
 */
void motorSetup(){
  // Left motor output through pin 2
  leftMotor.attach(2);

  // Right motor output through pin 8
  rightMotor.attach(8);

  // Send initial commands to motors, stopped
  sendMotorCommands(MOTOR_STOP, MOTOR_STOP);
}
