#ifndef DEMO_H
#define DEMO_H

#include "MovementModel.h"

class Demo : public MovementModel{
  public:
    Demo(int *d):MovementModel(d){};
    void execute(float goals[2]);
    void updateGoals(float goals[2]);
};

void Demo::execute(float goals[2]){
  this->updateGoals(goals);
};

void Demo::updateGoals(float goals[2]){
  goals[0] = data[0];
  goals[1] = data[1];
};

#endif // DEMO_H
