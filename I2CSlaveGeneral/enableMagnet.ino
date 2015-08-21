boolean wasCalled=false;
int times;
void enableMagnet(int time){
  wasCalled=true;
  times=millis();
  eMagnet(times);
}
void eMagnet(int time){
  //if (analogRead(22) > 533 || wasCalled==true){
    wasCalled=false;
    analogWrite(3, 255);
    analogWrite(4, 255);
    analogWrite(5, 255);
    analogWrite(6, 255);
    digitalWrite(16, HIGH);
    //for(int i=0; i<time*10; i++){
      //Serial.println(analogRead(22));
      Serial.println(analogRead(22));
      Serial.print(map(analogRead(22), 550, 535, 30, 0));
      Serial.println(" seconds remaining before shutdown.");
      Serial.println("");
      //delay(100);
    //}
  //}
  //else{disableMagnet();}
}
void disableMagnet(){
  digitalWrite(16, LOW);
  analogWrite(3, 0);
  analogWrite(4, 0);
  analogWrite(4, 0);
  analogWrite(4, 0);
  if (analogRead(22) > 530 && wasCalled==true){
    eMagnet(times);
  }
}
