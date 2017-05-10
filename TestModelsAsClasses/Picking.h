#ifndef PICKING_H
#define PICKING_H

#include "MovementModule.h"
#include "_forReadings.h"
#include "_forTurning.h"
#include "GoalHandler.h"
//
//class Picking : public MovementModule {
//  private:
//    
//  public:
//    void execute();
//    void goingStraight(void);
//    void turning(void);
//};

namespace Picking {

  enum State {TURNING, STRAIGHT}; // Instantiate the different states within picking
  State currState = State::STRAIGHT;  // Set default state to straight


  void goingStraight(){
    //Go straight
    GoalHandler::setDirection(GoalHandler::straight);
  
    //If not in a row, switch state to turning
    if (!robotInRow()) currState = State::TURNING;
  }; // goingStraight()


  void turning(){
    //Turn in the next direction
    GoalHandler::setDirection(Turning::next);
    //If in a row, toggle next turning, switch state to going straight
    if (robotInRow()){
      Turning::toggleNext();
      Turning::rows_picked += 1;
      currState = State::STRAIGHT;
    }
  }; // turning()

    void execute(){
    switch (currState) {
      case State::STRAIGHT:
        Picking::goingStraight();  // Enact the goStraight behavior
        break;
  
     case State::TURNING:
        Picking::turning();  // Enact the turning behavior
        break;
      default:
        // Do nothing
          break;
    }
  }; // execute()
};

#endif // PICKING_H
