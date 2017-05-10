#ifndef IDLE_H
#define IDLE_H

#include "MovementModule.h" // Extends MovementModule
#include "_forReadings.h"   // Defines goals and goal constants

// The class to be instantiated later
// Extends Movement Module
//class Idle : public MovementModule {
//  public:
//    void execute();
//};
//
/*
 * Robot stays still
 */
namespace Idle {
    void execute(){
      // Don't turn
      goals[_goals_turningSpeed] = 0.0;
    
      // Don't move forward
      goals[_goals_forwardSpeed] = 0.0;
    
      //Send out a message for dire circumstances (dead battery, can't move,...)
    }; // execute
};

#endif // IDLE_H
