#ifndef _FORTURNING_H
#define _FORTURNING_H

//ints for turning
const int _turning_initial;

//define turn at end of current row
int _turning_next;

void toggleTurn(){
  _turning_next *= -1;
}

#endif //_FORTURNING_H
