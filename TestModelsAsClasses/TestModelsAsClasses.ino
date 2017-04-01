// Can test everything on http://cpp.sh/

// Get the common stuff
#include "Common.h"

// Include the MovementModel abstract class
#include "MovementModel.h"

// Include all of the used movement model types
#include "GoHome.h"
#include "Nav.h"

// Set the MovementModel to be filled later
MovementModel *m;

// Produce the types of MovementModels we want to use
GoHome g(data);
Nav n(data);

void setup(){
  Serial.begin( 115200 );
  
  data[0] = 4;
  data[1] = 5;
  data[2] = 6;

  char str[20];
  sprintf(str, "Before: %d, %d", (int)goals[0], (int)goals[1]);
  Serial.println(str);
  
  // Make the movement model the demo model
  m = &g;
  m->execute(goals);

}

void loop(){
  // Update the lidar data
//	updateLIDARData();

// decide which movement module to use
//  updateMovementLogic()

// Run the movement module
//  m->execute(goals);

// Interprets goals and sends commands to motors
//  controlMotors();
}
