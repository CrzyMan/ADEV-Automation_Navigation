#ifndef IDLE_H
#define IDLE_H

#include "MovementModule.h"
#include "_forReadings.h"
#include "_forTurning.h"
#include "GoalHandler.h"

class Idle : public MovementModule {
  public:
    void execute();
};
void Idle::execute() {
  //Set goals for no movement
  goals[_goals_turningSpeed] = 0.0;
  goals[_goals_forwardSpeed] = 0.0;

  //Send out a message for dire circumstances (dead battery, can't move,...)
};
#endif // IDLE_H
