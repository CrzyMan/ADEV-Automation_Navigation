#ifndef _FORREADINGSH
#define _FORREADINGSH

// Indices for readings array
const char _readings_leftSideBack = 0;
const char _readings_leftSide = 1;
const char _readings_leftSideFront = 2;
const char _readings_frontLeft = 3;
const char _readings_front = 4;
const char _readings_frontRight = 5;
const char _readings_rightSideFront = 6;
const char _readings_rightSide = 7;
const char _readings_rightSideBack = 8;
const char _readings_size = 9;

// All data is in mm
int readings[_readings_size];

const int angleArray[_readings_size] = {
  130,  // left side back
  90,   // left side
  35,   // left side front
  12,   // front left
  0,    // front
  348,  // front right
  325,  // right side front
  270,  // right side
  230,  // right side back
};

// The number of degrees on each side of the viewing angle
// that are averaged with the angle
// 0 - Only the angle is used
// 1 - One degree on each side is averaged with the angle
const char _readings_spread = 0;
const int  _readings_max = 3000;

// Contains distance data for each angle (0-359, which is 360 elements)
int data[360];

// The max size of a packet is 12 characters
// A,###,####,Z
// 012345678901
const int packet_maxSize = 12;
char packet[packet_maxSize];
uint8_t packet_writeIndex = 0;

/** Mock Data **/
//                       angles = {130 , 90  , 35  , 12  , 0   , 348 , 325 , 270 , 230 }
const int mock_middleLeft[]     = {   0, 1506, 1677, 2403,    0,    0,    0, 1578, 1561};
const int mock_middleStraight[] = {1815, 1411, 2326,    0,    0,    0, 2409, 1478, 1882};
const int mock_middleRight[]    = {1455, 1545,    0,    0,    0, 2347, 1669, 1634, 1031};
const int mock_leftLeft[]       = {   0,  698,  716,  995, 1340,    0,    0, 2397, 2212};
const int mock_leftStraight[]   = { 809,  629, 1084,    0,    0,    0,    0, 2157, 2709};
const int mock_leftRight[]      = { 635,  722,    0,    0,    0,    0, 2381, 2439,    0};
const int mock_rightLeft[]      = {   0, 2208, 2487,    0,    0,    0,    0,  673,  683};
const int mock_rightStraight[]  = {   0, 2120,    0,    0,    0,    0,  998,  606,  794};
const int mock_rightRight[]     = {2162, 2311,    0,    0, 1340,  979,  705,  704, 1497};
const int mock_blind[]          = {   0,    0,    0,    0,    0,    0,    0,    0,    0};
const int mock_blindToTheRight[]= {   0,    0,    0,    0,    0,    0,  784,  450,    0};
/** End Mock Data **/

// The goals
float goals[2] = {0, 0};
// Indices for the goals array
const char _goals_turningSpeed = 0;
const char _goals_forwardSpeed = 1;

const int inRowThreshold = 2000;
// Returns whether or not the robot is in a row
bool robotInRow(){
  return (readings[_readings_rightSideFront] <= inRowThreshold &&
          readings[_readings_leftSideFront ] <= inRowThreshold);
}

#endif // _FORREADINGSH
