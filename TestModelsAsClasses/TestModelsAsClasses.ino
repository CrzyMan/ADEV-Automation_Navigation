// Can test everything on http://cpp.sh/

// Get everything included in Common.h
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

/*
 * Called once at the very beginning, used to set up everything (Serial, motors and USB).
 */
void setup(){
  // Setup Serial
  Serial.begin( 115200 );
  
  // Can wait at this point for GUI input

  // Setup motors
  motorSetup();

  // Set default movement module to idle
  m = &i;
  // Insure robot does not move on start up
  runModule();
  controlMotors();
  
  // Setup USB
  // This takes time to perform which is why we first insured the robot won't move
  USBSetup();
}

/*
 * Called by a infinite loop. Updates LIDAR data, picks the movement module
 * to use, runs that module, and controls the motors as appropriate.
 */
 void loop(){
  // Update the lidar data
  updateLIDARData();
  
  // decide which movement module to use
  pickModule();
    // Called inside updateMovementLogic();
  
  // Run the movement module
  runModule();

  // Interprets goals and sends commands to motors
  controlMotors();
}
