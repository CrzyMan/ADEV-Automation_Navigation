// Get the raw data from the USB connection
void updateLIDARData(){
  //Usb.Task();

  if(Acm.isReady()) {
    uint8_t rcode;

    //delay(50);

    /* reading the phone */
    /* buffer size must be greater or equal to max.packet size */
    /* it it set to 64 (largest possible max.packet size) here, can be tuned down
    for particular endpoint */
    uint8_t  buf[64];
    uint16_t rcvd = 64;
    // The buffer will contain about four packet
    // ['A',',','#',...,',','#',...,',','Z',...]
    rcode = Acm.RcvData(&rcvd, buf);
      if (rcode && rcode != hrNAK)
        ErrorMessage<uint8_t>(PSTR("Ret"), rcode);

        if( rcvd ) { //more than zero bytes received
          //Serial.println("New group");
          for(uint16_t i=0; i < rcvd; i++ ) {
            //Serial.print((char)buf[i]); //printing on the screen

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

  dataToReadings();
}

// Load the angle and distance into the data based on packet
// Only called when a packet is formed properly
void loadPacketToData(){
//  for (int i = 0; i < packet_maxSize; i++){
//    Serial.print(packet[i]);
//  }
//  Serial.print("\n");

  // guaranteed packet format: A,angle,dist,Z
  // Packet is guaranteed to be 12 characters: "A,###,####,Z"

  // Instatiating this as a string puts the 0 char at the end for us
  // Thus the length of 5 not 4
  char packetBuf[5] = "    ";

  // Put the angle into the buffer: 0###
  packetBuf[1] = packet[2];
  packetBuf[2] = packet[3];
  packetBuf[3] = packet[4];
  // Get the angle int
  int angle_int = atoi(packetBuf);
//  for (int i = 0; i < 5; i++){
//    Serial.print(packetBuf[i]);
//  }
//  Serial.print("\n");
  
  // Put the distance into the buffer: ####
  // This overwrites ALL bytes written for angle
  // No worry of artifacts
  packetBuf[0] = packet[6];
  packetBuf[1] = packet[7];
  packetBuf[2] = packet[8];
  packetBuf[3] = packet[9];
  // Get the distance int
  int dist_int = atoi(packetBuf); // mm
//  for (int i = 0; i < 5; i++){
//    Serial.print(packetBuf[i]);
//  }
//  Serial.print("\n\n");
  
  // If the distance is a zero, it is out of range, so treat it as though it is the maximum reading
  dist_int = dist_int == 0 ? _readings_max : dist_int;

  // Assign the distance at this angle
  data[angle_int] = dist_int;
  if (angle_int == 1){
    data[1] = data[0];
  }

//  Serial.print(angle_int);
//  Serial.print(", ");
//  Serial.print(dist_int);
//  Serial.print("\n\n");

}

// Turn the raw data into readings
void dataToReadings(){
  
  float avg;
  char i;
  char j;
  int val;
  // for each angle
  for (i = 0; i < _readings_size; i++){
    avg = 0;
    // across the spread
    for (j = -_readings_spread; j <= _readings_spread; j++){
      // Get the distance value at this angle
      val = data[angleArray[i] + j];

      // Adjust for when distance is beyond range (val = 0)
      // If val == 0, then set it to 4000, otherwise keep it the same
      // 4000 was chosen because it is just outside of the sensing range of the LIDAR
      val = (val == 0) ? 4000 : val;

      // get the distance at angleArray[i] + j
      avg += val;
    }

    // average the distances
    avg = avg / (1 + 2*_readings_spread);

    // set the reading to be the average
    readings[i] = avg;
  } 
}

// Loads the mock data into the distance data datastructure
// Should only be used when _readings_spread is set to zero
void loadMockData(const int mock[_readings_size]){
  for (int i = 0; i < _readings_size; i++){
    data[angleArray[i]] = mock[i];
  }
}


// Looks at the environment (basket, )
void updateEnvironmentFlags(){
  //First, clear all flags
  FlagProtocol::clearAllFlags();

  //Get new flags
  
}

void USBSetup(){
  if (Usb.Init() == -1)
      Serial.println("OSCOKIRQ failed to assert");

  // Wait for USB to be ready
  while(!Acm.isReady()){
    Usb.Task();
  }
  Serial.println("USB is ready");

  // Wait for the Acm and Usb to start collecting data well, experimentally takes at least 2 seconds
  delay( 2000 );
  
  Serial.println("Preloading LIDAR data...");
  for (int i = 0; i < 5000; i++) // added some more chunks to ensure full rotation
    updateLIDARData();
  
  for (int i = 0; i < 360; i++){
    Serial.print(i);
    Serial.print(", ");
    Serial.print(data[i]);
    Serial.print("\n");
  }
}

