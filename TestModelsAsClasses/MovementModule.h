#ifndef MOVEMENTMODULE_H
#define MOVEMENTMODULE_H

/*
 * This class serves as a framework for the different movement modules
 * present in the overall behavior of the robot. At the current implementation
 * GoHome.h, Picking.h and Idle.h are the instances of MovementModule used.
 * Within each module, an execute() function should be defined to describe the
 * behaviors required of that module.
 */
class MovementModule {
    public:
    /* 
     *  This function, execute(), will contain the module specific
     *  behavior, to be defined within each instance of MovementModule.
    */
      virtual void execute(){};
};

#endif //MOVEMENTMODULE_H
