#ifndef PICKING_H
#define PICKING_H

#include "MovementModel.h"
#include "_forReadings.h"
#include "_forTurning.h"
#include "GoalHandler.h"

class Picking : public MovementModel {
  private:
    enum State {TURNING, STRAIGHT};
    State currState = State::STRAIGHT;
  public:
    Picking(int *d): MovementModel(d) {};
    void execute(float goals[2]);
    void straight(void);
    void turning(void);
};

void Picking::execute(float goals[2]) {
  switch (currState) {
    case State::TURNING:
      turning();
      break;

    case State::STRAIGHT:
      goingStraight();
      break;
      
    default:
        break;
  }
};

void Picking::goingStraight(){

};

void Picking::turning(){

};

#endif // PICKING_H