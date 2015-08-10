void updateReadings(){
  
  for (int ii=0; ii<4; ii++){
    transmitI2C(ii+1,3,READ);
    while(Wire.available()) {
      for (int jj=0; jj<4; jj++){
        sensorsTotal[ii*4+jj]=Wire.readByte();
      }
    }
  }
}
