#include "_forMotorControl.h"
int lastLeftCommand = 0;
int lastRightCommand = 0;
// Indices for the goals array
const char _goals_turningSpeed = 0;
const char _goals_forwardSpeed = 1;

void controlMotors(float goals[2]){
  float rotationalSpeed = MAX_ROTATIONAL_SPEED*goals[_goals_turningSpeed];
  float leftPercent = goals[_goals_forwardSpeed] * SPEED_MULTI - HALF_TANK_WIDTH * rotationalSpeed/MAX_ROTATIONAL_SPEED;
  float rightPercent = goals[_goals_forwardSpeed] * SPEED_MULTI + HALF_TANK_WIDTH * rotationalSpeed/MAX_ROTATIONAL_SPEED;
  float leftCommand   = 95.0 - leftPercent * 70.0;
  float rightCommand  = 95.0 - rightPercent * 70.0;
  sendMotorCommands((int) leftCommand, (int) rightCommand);
}

void sendMotorCommands(int leftCommand, int rightCommand){
  if (leftCommand != lastLeftCommand){
    leftMotor.write(leftCommand);
    lastLeftCommand = leftCommand;
    Serial.println(leftCommand);
  }
  if (rightCommand != lastRightCommand){
    rightMotor.write(rightCommand);
    lastRightCommand = rightCommand;
    Serial.println(rightCommand);
  }
}
