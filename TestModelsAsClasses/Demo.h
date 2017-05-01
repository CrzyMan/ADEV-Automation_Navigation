#ifndef DEMO_H
#define DEMO_H

// Uses this file as a template
#include "MovementModule.h"

// Make the demo class to be instantiated later
class Demo : public MovementModule{
  public:
    void execute();
};

/*
 * Moves forward until something is close to the front of the robot
 */
void Demo::execute(){
  // If the front reading is less than 500mm
  if (readings[_readings_front] < 500){
    // Don't move forward
    goals[_goals_forwardSpeed] = 0;
    
    // Don't turn
    goals[_goals_turningSpeed] = 0;
    
  } else {
    // Move forward at the maximum allowable speed
    goals[_goals_forwardSpeed] = 1;
    
    // Don't turn
    goals[_goals_turningSpeed] = 0;
  
  }
};

#endif // DEMO_H
