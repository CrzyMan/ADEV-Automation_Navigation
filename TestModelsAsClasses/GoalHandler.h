#ifndef GOALHANDLER_H
#define GOALHANDLER_H

namespace GoalHandler {
  // The direction the robot is attempting to move in
  int currDir = 0;

  // Names of directions
  const int left = -1;
  const int right = 1;
  const int straight = 0;

  // Pointer to goals
  float *goals;

  void updateGoals(){
    
  };

  void setDirection(int newDir){
    currDir = newDir;
  }
}
#endif
