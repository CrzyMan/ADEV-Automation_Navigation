/*
#include <iostream>
#include <string>

int direction = 0;

int pos = 0;

void (*f)();

void move(){
    pos += direction;
}

void setDirection(int dir){
    direction = dir;
}

void forwards(){
    setDirection(1);
}

void backwards(){
    setDirection(-1);
}

void runModule(){
    (*f)();
}

int main()
{
    f = forwards;
    
    std::cout << "Pos = " << pos << "\n";
    
    runModule();
    move();
    
    std::cout << "Pos = " << pos << "\n";
    
    f = backwards;
    runModule();
    move();
    
    std::cout << "Pos = " << pos << "\n";
    
}

 */

// Can test everything on http://cpp.sh/

// Get the common stuff
#include "Common.h"


/** Includes for Movement Logic **/
// Include the MovementModel abstract class
#include "MovementModule.h"

// Include all of the used movement model types
#include "GoHome.h"
#include "Picking.h"
#include "Idle.h"
#include "Demo.h"

// Set the MovementModel to be filled later
//MovementModule *m;
void (*m)();

// Produce the types of MovementModels we want to use
//GoHome g;
//Picking p;
//Idle i;
//Demo d;
/** End Movement Logic **/


void setup(){
  // Setup Serial
  Serial.begin( 115200 );
  //While not ready, do nothing

  // Setup motors
  motorSetup();

  // Setup USB
  USBSetup();

  // Wait to start for some reason
  //while (Pin low or something){}
  
  //Set default movement module to idle
  m = Idle::execute;
  runModule();
  controlMotors();
}

void loop(){
  // Update the lidar data
  updateLIDARData();
  
  // decide which movement module to use
  pickModule();
    // Called inside updateMovementLogic();
    // Update flags caused by environment
    // updateEnvironmentFlags();
  
  // Run the movement module
  runModule();

  // Interprets goals and sends commands to motors
  controlMotors();
}
