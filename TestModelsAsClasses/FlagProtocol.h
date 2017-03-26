#ifndef FLAGPROTOCOL_H
#define FLAGPROTOCOL_H

namespace FlagProtocol {
  const char flag_flagsActive = 0;
  const char flag_basketFull = 1;
  const char flag_startPicking = 2;

  int flags = 0;
  
  void setFlag(int flag){
    bitSet(flags, flag);
    bitSet(flags, flag_activeFlag);
  };
  
  bool getFlag(int flag){
    return bitRead(flags, flag)?true:false;
  };
  
  void clearAllFlags(){
    flags = 0;
  };
};

#endif FLAGPROTOCOL_H
