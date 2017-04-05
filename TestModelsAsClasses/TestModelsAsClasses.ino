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
MovementModule *m;

// Produce the types of MovementModels we want to use
GoHome g;
Picking p;
Idle i;
Demo d;
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
  m = &i;
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
