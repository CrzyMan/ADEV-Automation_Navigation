#ifndef DEMO_H
#define DEMO_H

#include "MovementModule.h"

class Demo : public MovementModule{
  public:
    void execute();
};

void Demo::execute(){
  if (readings[_readings_front] < 500){
    goals[_goals_forwardSpeed] = 0;
    goals[_goals_turningSpeed] = 0;
  } else {
    goals[_goals_forwardSpeed] = 1;
    goals[_goals_turningSpeed] = 0;
  }
};

#endif // DEMO_H
