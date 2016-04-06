

void filler(int y[], int x) {
  for (int i = 0; i < 1000; i++) {
    y[i] = x;
  }
}

void filler300(uint8_t y[]) {
  for (uint8_t i = 0; i < 300; i++) {
    y[i] = 0;
  }
}

int avg(int y[]) {
  unsigned long int total = 0;
  for (int j = 0; j < 1000; j++) {
    total = total + y[j];
  }
  return (total / 1000);
}

int avg300(uint8_t y[]) {
  unsigned long int total = 0;
  for (int j = 0; j < 300; j++) {
    total = total + y[j];
  }
  return (total / 300);
}


void contacted(int pin) {
  if (pin==3){
    Timer1.pwm(4, 0, 8);
  }
  else{
    Timer1.pwm(3, 0, 8);
  }
  int k = 0;

  Timer1.pwm(pin, 512, 8);
  Timer1.restart();

  for (int i = 0; i < 100000; i++) {
    Timer1.restart();
    delayMicroseconds(10);
    section[k] = adc->analogRead(23);
    if ((i + 1) % 100 == 0) {
      wholeSample[i / 100] = avg(section);
      wholeSample2[i / 100] = avg(section2);
      wSPlace++;
      k = 0;
    }
    if (i % 10000 == 0) {
      Serial.begin(115200);
      Serial.println("one");
      Serial.println((avg(wholeSample)));
      Serial.println("two");
      Serial.println((avg(wholeSample2)));
      Serial.end();
      wSPlace = 0;
    }
    k++;
  }
}


unsigned long lastMillis = 0;
uint8_t last300[300];
unsigned long callSecs = 0;
boolean coilOn = false;
int onPin=5;

boolean allowMagnet() {
  if ((unsigned long)(millis() - lastMillis) >= 300000) {
    filler300(last300);
    return true;
  }
  else if (avg300(last300) < 10) {
      return true;
  }
  return false;
}

boolean enableCoil(int time) {
  boolean allowed = allowMagnet();
  if (allowed){
    callSecs=millis();
    if (callSecs/1000%300<lastMillis/1000%300){
      for(int i = (lastMillis/100%300); i<300; i++){
        last300[i]=0;
      }
      for(int i = 0; i<(callSecs/100%300); i++){
        last300[i]=0;
      }
    }
    else{
      for(int i = (lastMillis/100%300); i<callSecs/100%300; i++){
        last300[i]=0;
      }
    }
    digitalWrite(onPin, HIGH);
    coilOn=true;
    lastMillis=callSecs;
  }
  return allowed;
}

void disableCoil() {
  digitalWrite(onPin, LOW);
  coilOn=false;
}

//int greatest(int y[]) {
//  int big = 0;
//  for (int j = 0; j < 100; j++) {
//    if (y[j] > big) {
//      big = y[j];
//    }
//  }
//  return big;
//}
