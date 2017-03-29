#ifndef GO_HOME_H
#define GO_HOME_H

#include "MovementModel.h"
#include "_forReadings.h"
#include "_forTurning.h"
#include "GoalHandler.h"

class GoHome : public MovementModel {
  private:
    int counter = 0;
    enum State {INROW, OUTOFROW, TURNTOHOME};
    State currState = INROW;
    const int upperLimit = 1000;
    const int threshold = upperLimit * 9 / 10;
  public:
    GoHome(int *d): MovementModel(d) {};
    void execute(float goals[2]);
    void outOfRow(void);
    void inRow(void);
};
void GoHome::execute(float goals[2]) {
  switch (currState) {
    case INROW:
      inRow();
      break;
    case OUTOFROW:
      outOfRow();
      break;
    case TURNTOHOME:
      turnToHome();
      break;
  }
};

void GoHome::outOfRow() {
  counter++;
  if (counter > threshold) {
    GoalHandler::setDirection(_turning_next);
  } else {
    GoalHandler::setDirection(GoalHandler::straight);
  }
  if (counter >= upperLimit) {
    counter = 0;
  }
}

void GoHome::inRow() {
  if(readings[_readings_frontSideRight] <= 2000 && readings[_readings_frontSideLeft] <= 2000]){
    if(GoalHandler::currDir != GoalHandler::straight){
      _forTurning::toggleTurn();
    }
    GoalHandler::setDirection(GoalHandler::straight);
  }else{
    if(_forTurning::_turning_next != _forTurning::_turning_initial){
      GoalHandler::setDirection(_forTurning::_turning_initial);
      currState = TURNTOHOME;
    }else{
      GoalHandler::setDirection(_forTurning::_turning_next);
    }
  }
  /*check readings to see if at end of row
    if not at end of row
      if currDir isn't straight
        toggle next turn
      go straight
    else:
      if next turn != initial turn
        setDirection(initial turn)
        change state to turn_to_home
      else
        setDirection(next turn)
  */
}

void GoHome::turnToHome() {
  int reads = 0;
  switch (GoalHandler::currDir) {
    case GoalHandler::right:
      reads = readings[_readings_frontSideRight];
      break;
    case GoalHandle::left:
      reads = readings[_readings_frontSideLeft];
      break;
    default:
  }
  if (reads > 1000 && reads < 2500) {
    currState = OUTOFROW;
  }
}

#endif // GO_HOME_H
