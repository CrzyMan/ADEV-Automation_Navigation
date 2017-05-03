#ifndef GO_HOME_H
#define GO_HOME_H

#include "MovementModule.h"
#include "_forReadings.h"
#include "_forTurning.h"
#include "GoalHandler.h"

class GoHome : public MovementModule {
  private:
    // Set up states and set currState to INROW
    enum State {INROW, OUTOFROW, TURNTOHOME};
    State currState = INROW;
    // Variables for out of row navigation bias
    int counter = 0;
    const int upperLimit = 1000;
    const int threshold = upperLimit * 9 / 10;
  public:
    void execute();
    void outOfRow(void);
    void inRow(void);
    void turnToHome(void);
};
/*
 * Executes behavior based on currState
 */
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

/*
 * While the robot is out of the row and moving towards home, it turns toward the row a certain precentage
 * (once a counter reaches a threshold)of the time. This biases the robot toward the row rather than straying
 * from the row.
 */
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
  //Check to to see if at end of row
  if(robotInRow()){
    // if currDir isn't straight, toggle next turn
    if(GoalHandler::currDir != GoalHandler::straight){
      Turning::toggleNext();
    }
    // if currDir is straight, setDirection to straight
    GoalHandler::setDirection(GoalHandler::straight);
  }else{
    // if next turn != initial turn, setDirection(initial turn), change state to turn_to_home
    if(Turning::next != Turning::initial){
      GoalHandler::setDirection(Turning::initial);
      currState = TURNTOHOME;
    }else{
      // set direction to next turn
      GoalHandler::setDirection(Turning::next);
    }
  }
}

void GoHome::turnToHome() {
  int reads = 0;
  // A switch to evaluate diagonal feelers readings based on turning direction
  switch (GoalHandler::currDir) {
    case GoalHandler::right:
      reads = readings[_readings_rightSideFront];
      break;
    case GoalHandler::left:
      reads = readings[_readings_leftSideFront];
      break;
    default:
      // Do nothing
      break;
  }
  // if a diagonal feeler catches the edge of a row, it is out of the row
  if (reads > 1000 && reads < 2500) {
    currState = OUTOFROW; //Set currState to OutOfRow
  }
}

#endif // GO_HOME_H
