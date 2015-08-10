void transmitI2C(uint8_t spot, uint8_t cmd){
  Wire.beginTransmission(spot);
  Wire.write(0x00);
  Wire.write(cmd);
  Wire.endTransmission();
  
}
void commandSelector(){
  String x = getCommand();
  if (x=="COff"){
    transmitI2C(1,1);
  }
  else if (x=="CSense"){
    transmitI2C(1,2);
  }
  else if (x=="ROff"){
    transmitI2C(2,1);
  }
  else if (x=="RSense"){
    transmitI2C(2,2);
  }
  else if (x=="GOff"){
    transmitI2C(3,1);
  }
  else if (x=="GSense"){
    transmitI2C(3,2);
  }
  else if (x=="IOff"){
    transmitI2C(4,1);
  }
  else if (x=="ISense"){
    transmitI2C(4,2);
  }
  
  
}    
  
