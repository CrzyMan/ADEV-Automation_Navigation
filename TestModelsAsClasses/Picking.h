#ifndef PICKING_H
#define PICKING_H

#include "MovementModule.h"
#include "_forReadings.h"
#include "_forTurning.h"
#include "GoalHandler.h"

class Picking : public MovementModule {
  private:
    enum State {TURNING, STRAIGHT};
    State currState = State::STRAIGHT;
  public:
    void execute();
    void goingStraight(void);
    void turning(void);
};

void Picking::execute() {
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
  if (!robotInRow()) currState = State::TURNING;

};

void Picking::turning(){
  //Turn in the next direction
  GoalHandler::setDirection(Turning::next);

  //If in a row
  //  toggle next turning
  //  switch state to going straight
  if (robotInRow()){
    Turning::toggleNext();
    currState = State::STRAIGHT;
  }

};

#endif // PICKING_H
