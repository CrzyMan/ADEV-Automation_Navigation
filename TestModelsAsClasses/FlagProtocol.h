#ifndef FLAGPROTOCOL_H
#define FLAGPROTOCOL_H

namespace FlagProtocol {
  //Create flag names, up to 32 because of 32 bits in an Integer
  enum FlagNames { flagsActive, basketFull, batteryLow, armBusy, goHomeRequest, batteryDead, obstacleWhileTurning };
  int flags = 0;
  
  void setFlag(int flag){
    bitSet(flags, flag);
    bitSet(flags, FlagNames::flagsActive);
  };
  
  bool getFlag(int flag){
    return bitRead(flags, flag)?true:false;
  };
  
  void clearAllFlags(){
    flags = 0;
  };
};

#endif // FLAGPROTOCOL_H
