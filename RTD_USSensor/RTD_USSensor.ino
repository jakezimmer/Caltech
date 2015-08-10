void setup() {
  pinMode(10, OUTPUT);
  pinMode(13, OUTPUT);
  
  Serial.begin(9600);
  
  digitalWrite(13, HIGH);
  digitalWrite(10, HIGH);
  
  

}

void loop() {
  Serial.println(((40.21722138*pow(2.71828, 0.0039705*analogRead(14)))-273)*(9/5)+32);
  Serial.println(" ");
  delay(100);

}
