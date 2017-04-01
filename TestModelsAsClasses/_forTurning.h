#ifndef _FORTURNING_H
#define _FORTURNING_H

#include "GoalHandler.h"

namespace Turning{
  // int for turning
  int initial = GoalHandler::left;;

  // define turn at end of current row
  int next = Turning::initial;;

  /** Toggles the next turn between left (-1) and right (1)
      If the next turn is set to straight (0), then it will stay straight
  */
  void toggleNext(){
    // Because left is -1 and right is 1, we can negate the turn to toggle between the two.
    Turning::next *= -1;
  }
};

#endif //_FORTURNING_H
