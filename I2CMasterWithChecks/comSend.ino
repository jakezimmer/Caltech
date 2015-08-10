void transmitI2C(uint8_t spot, uint8_t cmd, uint8_t type){
  Wire.beginTransmission(spot);
  Wire.write(type);
  Wire.write(0x00);
  Wire.write(cmd);
  Wire.endTransmission();
  
}
void commandSelector(){
  String x = getCommand();
  if (x=="COff"){
    transmitI2C(1,1,WRITE);
  }
  else if (x=="ROff"){
    transmitI2C(2,1,WRITE);
  }
  else if (x=="GOff"){
    transmitI2C(3,1,WRITE);
  }
  else if (x=="IOff"){
    transmitI2C(4,1,WRITE);
  }
  else if (x=="CheckDead"){
    comboBreaker();
  }
  
}    
  
