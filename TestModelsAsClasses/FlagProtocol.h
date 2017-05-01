#ifndef FLAGPROTOCOL_H
#define FLAGPROTOCOL_H

// It's in its own namespace to isolate it from the rest of the code
namespace FlagProtocol {
  
  //Create flag names, up to 32 because of 32 bits in an Integer
  enum FlagNames { flagsActive, basketFull, batteryLow, armBusy, goHomeRequest, batteryDead, obstacleWhileTurning };

  // This integer will store every flag at once
  int flags = 0;

  /*
   * Takes a flag and sets it high
   * It also always sets the flagsActive high so we know a flag has been set
   */
  void setFlag(int flag){
    // Set the given flag by making the corresponding bit in the integer 1
    bitSet(flags, flag);

    // Set the flag for that a flag has been set
    bitSet(flags, FlagNames::flagsActive);
  };

  /*
   * Returns whether the flag has been set or not
   */
  bool getFlag(int flag){
    // bitRead() returns a 0 or a 1, which we have to convert to boolean
    return bitRead(flags, flag) ? true : false;
  };

  /*
   * Clears every single flag at once
   */
  void clearAllFlags(){
    // Because all flags are stored in one int, we can set the int to 0, and all bits are reset to 0
    flags = 0;
  };
};

#endif // FLAGPROTOCOL_H
