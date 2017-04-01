
// Looks at the flags and sets active module to most appropriate module to run
void pickModule(){
  // Update flags caused by environment
  updateEnvironmentFlags();

  // Set module to default, Picking, will change if needed
  m = &p;
  
  // If a flag has been set, then make decisions
  if(FlagProtocol::getFlag(FlagProtocol::FlagNames::flagsActive)){
      // Make decisions
      // Idle: arm busy, object in-front while turning, battery dead
      if (FlagProtocol::getFlag(FlagProtocol::FlagNames::armBusy) ||
          FlagProtocol::getFlag(FlagProtocol::FlagNames::batteryDead) ||
          FlagProtocol::getFlag(FlagProtocol::FlagNames::obstacleWhileTurning)){
          m = &i;
      }
      // GoHome: Battery low, basket full, goHome request
      else if (FlagProtocol::getFlag(FlagProtocol::FlagNames::basketFull) ||
          FlagProtocol::getFlag(FlagProtocol::FlagNames::batteryLow) ||
          FlagProtocol::getFlag(FlagProtocol::FlagNames::goHomeRequest)){
          m = &g;
       }
  }
  
  // Make the movement model the demo model
  // m = &p;
}

void runModule(){
  m->execute();
}

