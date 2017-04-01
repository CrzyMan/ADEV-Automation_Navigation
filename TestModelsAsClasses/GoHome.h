#ifndef GO_HOME_H
#define GO_HOME_H

#include "MovementModule.h"
#include "_forReadings.h"
#include "_forTurning.h"
#include "GoalHandler.h"

class GoHome : public MovementModule {
  private:
    int counter = 0;
    enum State {INROW, OUTOFROW, TURNTOHOME};
    State currState = INROW;
    const int upperLimit = 1000;
    const int threshold = upperLimit * 9 / 10;
  public:
    void execute();
    void outOfRow(void);
    void inRow(void);
    void turnToHome(void);
};
void GoHome::execute() {
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
    GoalHandler::setDirection(Turning::next);
  } else {
    GoalHandler::setDirection(GoalHandler::straight);
  }
  if (counter >= upperLimit) {
    counter = 0;
  }
}

void GoHome::inRow() {
  if(robotInRow()){
    if(GoalHandler::currDir != GoalHandler::straight){
      Turning::toggleNext();
    }
    GoalHandler::setDirection(GoalHandler::straight);
  }else{
    if(Turning::next != Turning::initial){
      GoalHandler::setDirection(Turning::initial);
      currState = TURNTOHOME;
    }else{
      GoalHandler::setDirection(Turning::next);
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
      reads = readings[_readings_rightSideFront];
      break;
    case GoalHandler::left:
      reads = readings[_readings_leftSideFront];
      break;
    default:
      break;
  }
  if (reads > 1000 && reads < 2500) {
    currState = OUTOFROW;
  }
}

#endif // GO_HOME_H
