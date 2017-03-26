// Can test everything on http://cpp.sh/

// Get the common stuff
#include "Common.h"

// Include the MovementModel abstract class
#include "MovementModel.h"

// Include all of the used movement model types
#include "Demo.h"
#include "Nav.h"

// Set the MovementModel to be filled later
MovementModel *m;

// Produce the types of MovementModels we want to use
Demo d(data);
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
  m = &d;
  m->execute(goals);
  sprintf(str, "Demo 1: %d, %d", (int)goals[0], (int)goals[1]);
  Serial.println(str);
  

  // change the data in this scope to prove everything is connected
  data[2] = 8;
  
  // Make the movement model the nav model
  m = &n;
  m->execute(goals); // this makes data[0]=1
  sprintf(str, "Nav  1: %d, %d", (int)goals[0], (int)goals[1]);
  Serial.println(str);

  // Switch it back to the demo model
  m = &d;
  m->execute(goals);
  sprintf(str, "Demo 2: %d, %d", (int)goals[0], (int)goals[1]);
  Serial.println(str);

}

void loop(){
//	updateLIDARData();
//  m->execute(goals);
//  controlMotors();
}
