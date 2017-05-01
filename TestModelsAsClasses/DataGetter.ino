/* 
 * Get the raw data from the USB connection 
 * Form it into packets, and then process those packets
 */
void updateLIDARData(){

  // If we can communicate
  if(Acm.isReady()) {
    // will hold data later on
    uint8_t rcode;
    
    // The rest of this function was adapted to suit our needs,
    // but was not originally written by the Rose-Hulman 2016-2017 ADEV Automation Navigation team
    /* reading the phone */
    /* buffer size must be greater or equal to max.packet size */
    /* it it set to 64 (largest possible max.packet size) here, can be tuned down
    for particular endpoint */
    uint8_t  buf[64];
    uint16_t rcvd = 64;
    // The buffer will contain about four packets worth of data
    // ['A' , ',' , '#' , ... , ',' , '#' , ... , ',' , 'Z' , ...]
    rcode = Acm.RcvData(&rcvd, buf);

    // If there has been an error
    if (rcode && rcode != hrNAK)
      ErrorMessage<uint8_t>(PSTR("Ret"), rcode);

    if( rcvd ) { //more than zero bytes received
      for(uint16_t i=0; i < rcvd; i++ ) {
        // If we are at the beginning of a packet, ensure we begin at index 0
        if (buf[i] == 'A')
          packet_writeIndex = 0;
        
        // Write to the packet
        packet[packet_writeIndex++] = buf[i];
  
        // If we have completed the packet, load it into the data
        if (buf[i] == 'Z' && packet_writeIndex == 12)
          loadPacketToData();
        
        // Wrap the write index back around to 0 when it hits the max size
        packet_writeIndex = packet_writeIndex % packet_maxSize;
  
      } // for
    }// if (rcvd)
  }// if ACM.ready()
  else {
    // Shouldn't ever be called because we wait in the setup
    Serial.println("Not ready");
  }

  // Force the readings to update based on the data
  dataToReadings();
}

/* 
 *  Load the angle and distance into the data based on packet
 *  Only called when a packet is formed properly
 */
void loadPacketToData(){
  // Transmit packet to computer; Used by Matlab
  // Debugging purposes only
  // Serial.println(packet);

  // guaranteed packet format: Header, Angle, Distance, Footer
  // Packet is guaranteed to be 12 characters: "A,###,####,Z"

  // Instatiating this as a string puts the 0 char at the end for us
  // This is necesarry in order to form a proper string
  // Thus the length of 5 not 4
  char packetBuf[5] = "    ";

  // Put the angle into the buffer. Final form: " ###"
  packetBuf[1] = packet[2];
  packetBuf[2] = packet[3];
  packetBuf[3] = packet[4];
  
  // Get the angle int
  int angle_int = atoi(packetBuf);

  
  // Put the distance into the buffer. Final form: "####"
  // This overwrites ALL bytes written for angle
  // No worry of artifacts
  packetBuf[0] = packet[6];
  packetBuf[1] = packet[7];
  packetBuf[2] = packet[8];
  packetBuf[3] = packet[9];
  
  // Get the distance int
  int dist_int = atoi(packetBuf); // mm

  
  // If the distance is a zero or too high, it is too far out of range or there was an error respectively
  // So, treat it as though it is the maximum reading
  dist_int = (dist_int == 0 || dist_int > _readings_max) ? _readings_max : dist_int;

  // Assign the distance at this angle
  data[angle_int] = dist_int;
  if (angle_int == 1){
    data[1] = data[0];
  }
}

/* 
 *  Turn the recorded data into readings
 */
void dataToReadings(){

  // The value to store the averages, one at a time
  float avg = 0;

  // For iterations. Should never reasonably exceed a value of 255, so are characters to save space
  char i = 0, j = 0;

  // For temporarily storing the angle information
  int a = 0;
  
  // for each reading
  for (i = 0; i < _readings_size; i++){
    // reset the average
    avg = 0;
    
    // sum the distances across the spread
    for (j = -_readings_spread; j <= _readings_spread; j++){
      // Get the angle and wrap around
      a = (angleArray[i] + j + 360) % 360;

      // get the distance at angleArray[i] + j
      avg += (float) data[a];
    } // for sum

    // average the distances
    avg = avg / (1.0 + 2.0*_readings_spread);

    // set the reading to be the average
    readings[i] = (int) avg;
  } // for reading
}

/* 
 * Loads the mock data into the distance data datastructure 
 * Should only be used when _readings_spread is set to zero
 */
void loadMockData(const int mock[_readings_size]){
  // for each reading
  for (int i = 0; i < _readings_size; i++){
    // set the data for the reading angle the same value as in the mock data
    data[angleArray[i]] = mock[i];
    
  } // for readings
}


/* 
 *  Looks at the environment and set the appropriate flags
 *  This is in DataGetter and not FlagProtocol because it is actively retrieving data
 */
void updateEnvironmentFlags(){
  //First, clear all flags
  FlagProtocol::clearAllFlags();

  // Get new flags
  // This is where you would check pins
  // Alternatively, interrupts could work for wireless communication
  
}

/*
 * Instantiates the USB object and the ACM and ensures they are ready for operation
 */
void USBSetup(){
  // If it fails to initialize
  if (Usb.Init() == -1)
      Serial.println("OSCOKIRQ failed to assert");

  // Wait for USB to be ready
  while(!Acm.isReady()){
    Usb.Task();
  }
  Serial.println("USB is ready");

  // Wait for the Acm and Usb to start collecting data well, experimentally takes at least 2 seconds
  delay( 2000 );

  // Every rotation will miss some angles, so we need to run for many rotations to
  // ensure that the data[] array will most accurately represent the environment before we start
  Serial.println("Preloading LIDAR data...");
  for (int i = 0; i < 5000; i++)
    updateLIDARData();

  Serial.println("Done loading");
}

