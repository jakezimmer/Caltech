void setup() {
  Serial1.begin(57600);
  Serial2.begin(57600);
  Serial3.begin(57600);

}

void loop() {
  if(Serial1.available()){
    Serial3.write(Serial1.read());
  }
  if(Serial2.available()){
    Serial3.write(Serial2.read());
  }

}
