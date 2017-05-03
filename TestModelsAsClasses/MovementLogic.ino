
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
       // Add additional else if statements if other states arise.
  }
}

/*
 * Updates goals and calls the current movement module's execute() function
 */
void runModule(){
  // Runs for the most recently selected direction
  GoalHandler::updateGoals();

  // Gives the module the opportunity to directly edit the goals (idle/demo)
  // Otherwise, timescale is so small, the output will seem to happen at the same time as the decision, even though it is an iteration behind
  m->execute();
}

