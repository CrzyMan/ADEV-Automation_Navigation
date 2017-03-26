#ifndef NAV_H
#define NAV_H

#include "MovementModel.h"
#include "_forReadings.h"
#include "Protocol.h"

class Nav : public MovementModel{
    public:
        Nav(int *d):MovementModel(d){};
        void execute(float goals[2]);
        void updateGoals(float goals[2]);
};
void Nav::execute(float goals[2]){
    int dir = Protocol::left;
    this->updateGoals(goals);
};
void Nav::updateGoals(float goals[2]){
  goals[0] = data[1];
  goals[1] = data[2];
  data[0] = 1; 
};

#endif // NAV_H
