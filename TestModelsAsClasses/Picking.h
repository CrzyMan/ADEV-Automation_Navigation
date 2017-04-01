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
    case State::STRAIGHT:
      goingStraight();
      break;

   case State::TURNING:
      turning();
      break;

    default:
        break;
  }
};

void Picking::goingStraight(){
  //Go straight
  GoalHandler::setDirection(GoalHandler::straight);

  //If not in a row
  //  switch state to turning
  if (!robotInRow()) currState = State::turning;

};

void Picking::turning(){
  //Turn in the next direction
  GoalHandler::setDirection(Turning::next);

  //If in a row
  //  toggle next turning
  //  switch state to going straight
  if (robotInRow()){
    Turning::toggleNext();
    currState = State::straight;
  }

};

#endif // PICKING_H