String getCommand(){
  String output;
  while(Serial.available())
  {
    delay(5);
    output += char(Serial.read());
  }
  return output;

}

