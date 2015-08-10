String getCommand(){
  String output;
  while(Serial.available())
  {
    delay(5);
    output += char(Serial.read());
  }
  return output;

}
int* I2CRead(uint8_t spot){
  int x[4]={0,0,0,0};
  while(Wire.available()) {
    for (int i=0; i<4; i++){
      x[i]=Wire.readByte();
    }
  }
  return x;
  
  
}
