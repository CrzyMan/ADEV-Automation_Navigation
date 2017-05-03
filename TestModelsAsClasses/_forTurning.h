#ifndef _FORTURNING_H
#define _FORTURNING_H

// Provides access to turn directions
#include "GoalHandler.h"

namespace Turning{
  // The first turn will be to the right, by default
  // This is not a constant so it can be changed during setup

  int initial = GoalHandler::right;

  // The turn that will be made the next time the robot reaches the end of a row
  int next = Turning::initial;

  // Variable to track number of rows picked
  int rows_picked = 0;

  /* 
   *  Toggles the next turn between left (-1) and right (1)
   *  If the next turn is set to straight (0), then it will stay straight
  */
  void toggleNext(){
    // Because left is -1 and right is 1, we can negate the turn to toggle between the two.
    Turning::next *= -1;
  }
};

#endif //_FORTURNING_H
