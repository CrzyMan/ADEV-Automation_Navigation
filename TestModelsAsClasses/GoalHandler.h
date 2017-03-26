#ifndef GOALHANDLER_H
#define GOALHANDLER_H

#include "_forReadings.h"

namespace GoalHandler {
  // The direction the robot is attempting to move in
  int currDir = 0;

  // Names of directions
  const int left = -1;
  const int right = 1;
  const int straight = 0;

  float goals[2] = {0, 0};

  // Indices for the biases array
  const char _biases_lateral = 0;
  const char _biases_rotational = 1;
  const char _biases_speed = 2;
  // biases = [_biases_lateral, _biases_rotational, _biases_speed]
  // lateral bias > 0 = turn to the left
  // rotational bias > 0 = turn to the right
  // speed bias -> sensitivityScaler for speed
  float biases[3];

  // For the logistic function
  // Respective sensitivities
  float latSensitivity = 4;
  float rotSensitivity = 4;
  float speedSensitivity=6;

  /*** Start defining constants and variables ***/
  // Indices for the fuzzy logic modifiers
  const char _fuzzy_sideBack = 0;
  const char _fuzzy_side = 1;
  const char _fuzzy_sideFront = 2;
  const char _fuzzy_frontSide = 3;
  const char _fuzzy_front = 4;
  const char _fuzzy_size = 5;
  // All goals are in mm
  // readingGoals = [_fuzzy_sideBack, _fuzzy_side, _fuzzy_sideFront, _fuzzy_frontSide, _fuzzy_front]
  int fuzzyGoals[_fuzzy_size] = {587, 450, 784, 0, 800};

  // Indices for the goals array
  const char _goals_turningSpeed = 0;
  const char _goals_forwardSpeed = 1;
  
  // Returns the balanced Logistic function of x, given a k value
  // Balanced, in this sense, means that the y-intercept is the origin 
  // and that it goes from -1 to 1 as x increases
  float balancedLogistic(float x, float k){
    return 2.0/(1.0 + exp(-k*x)) - 1.0;
  }

  // Takes in the readings and biases and Updates the biases based on the readings
  void updateBiases(){
    // Turn the readings into biases
  
    // Lateral bias from left and right readings
    biases[_biases_lateral] = readings[_readings_leftSide]*(currDir != right) // ignore when turning right
                            - readings[_readings_rightSide]*(currDir != left) // ignore when turning left
                            - fuzzyGoals[_fuzzy_side]*(-currDir);
  
    // Rotational bias from front left and front right readings
    biases[_biases_rotational] = 0
                               + readings[_readings_leftSideFront]*(currDir != right) // ignore when turning right
                               - readings[_readings_rightSideFront]*(currDir != left) // ignore when turning left
                               - fuzzyGoals[_fuzzy_sideFront]*(-currDir) // ignore when going straight

                               // Doesn't work how I had hoped, so I multiplied by 0 instead of completely forgetting about it
                               - readings[_readings_leftSideBack]*(currDir != right)*0 // ignore when turning right
                               + readings[_readings_rightSideBack]*(currDir != left)*0 // ignore when turning left
                               + fuzzyGoals[_fuzzy_sideBack]*(-currDir)*0; // ignore when going straight

  
    // Speed bias from the forward reading
    biases[_biases_speed] = readings[_readings_front] - fuzzyGoals[_fuzzy_front];

  };

  
  // Takes in the readings and the goals and Updates the goals according to the readings
  void updateGoals(){
    // get the new biases
    updateBiases();
  
    // This scaling is because it is easier to think of sensitivity when it isn't tiny
    float sensitivityScaler = 0.001;
    float latK = sensitivityScaler*latSensitivity;
    float rotK = sensitivityScaler*rotSensitivity;
    float speedK=sensitivityScaler*speedSensitivity;
  
    // turn the biases into goals
    goals[_goals_turningSpeed] = balancedLogistic(biases[_biases_lateral] + biases[_biases_rotational],latK);
    goals[_goals_forwardSpeed] = balancedLogistic(biases[_biases_speed], speedK);
    goals[_goals_forwardSpeed] = goals[_goals_forwardSpeed] < 0 ? 0 : goals[_goals_forwardSpeed];
  
  };

  void setDirection(int newDir){
    currDir = newDir;
  }
}
#endif
