#ifndef PICKING_H
#define PICKING_H

#include "MovementModule.h"
#include "_forReadings.h"
#include "_forTurning.h"
#include "GoalHandler.h"

class Picking : public MovementModule {
  private:
    int counter = 0;
    int counterThreshold = 5000;
    float movingThreshold = 0.25;
    boolean reachEoF = false;
    enum State {TURNING, STRAIGHT}; // Instantiate the different states within picking
    State currState = State::STRAIGHT;  // Set default state to straight
  public:
    void execute();
    void goingStraight(void);
    void turning(void);
};

void Picking::execute() {
  switch (currState) {
    case State::STRAIGHT:
      goingStraight();  // Enact the goStraight behavior
      break;
   case State::TURNING:
      turning();  // Enact the turning behavior
      break;
    default:
      // Do nothing
        break;
  }
};

// GoingStraight behavior
void Picking::goingStraight(){
  //Go straight
  GoalHandler::setDirection(GoalHandler::straight);

  //If not in a row, switch state to turning
  if (!robotInRow()) currState = State::TURNING;
};

// Turning behavior
void Picking::turning(){
  //Turn in the next direction
  GoalHandler::setDirection(Turning::next);
  //If in a row, toggle next turning, switch state to going straight
  if (robotInRow()){
    // Toggle next turn to keep moving down field
    Turning::toggleNext();
    // Increment number of rows picked
    Turning::rows_picked += 1;
    // Reset counter
    counter = 0;
    // If robot has reached end of field
    if(reachEoF){
      // Toggle next turn, reset flag, send goHome request
      Turning::toggleNext();
      reachEoF = false;
      FlagProtocol::setFlag(FlagProtocol::Flags::goHomeRequest);
    }
    // Set current state to straight
    currState = State::STRAIGHT;
  }else{
    // If moving and hasn't reached end of the field yet
    if(goals[_goals_forwardSpeed] > movingThreshold && !reachEoF){
      // Increment counter
      counter++;      
    }
    // If turning for too long and counter is above threshold
    if(counter >= counterThreshold){
      // Has reached end of field, set flag
      reachEoF = true;
    }
  }
};

#endif // PICKING_H
