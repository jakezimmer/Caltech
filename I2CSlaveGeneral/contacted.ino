int wholeSample[1000];
int section[100];
int temp;
int wSPlace=0;


void phil(){
  filler(wholeSample,500); //needed to call filler because of scope
}

void filler(int y[], int x){
  for (int i=0; i<1000; i++){
    y[i]=x;
  }
}

int avg(int y[]){
  unsigned long int total=0;
  for (int j=0; j<1000; j++){
    total=total+y[j];
  }
  return (total/1000);
}

int greatest(int y[]){
  int big=0;
  for (int j=0; j<100; j++){
    if (y[j]>big){
      big=y[j];
    }
  }
  return big;
}

int contacted(short pin){
  int k=0;
  int last;
  analogWrite(pin, 127);
  for (int i=0; i<100000;i++){
    //Timer1.setPeriod(25);
    //Timer1.pwm(4, 100);
    //delay(1);
    //Timer1.restart();
    //delayMicroseconds(5);
    section[k]=analogRead(18);
    
    if ((i+1)%100==0){
      wholeSample[i/100]=greatest(section);
      wSPlace++;
      /*Serial.begin(115200);
      Serial.println(avg(wholeSample));
      //Serial.println(wholeSample[0]);
      //Serial.println(sizeof(wholeSample)/4);
      //Serial.println(i);
      //Serial.println(wSPlace);
      Serial.println();
      Serial.end();/*/
      k=0;
      
      
    }
    if (i%10000==0){
      last=avg(wholeSample);
      //Timer1.stop();
      //digitalWrite(13, LOW);
      //delay(100);
      //digitalWrite(13, HIGH);
      wSPlace=0;
      
      //Timer1.resume();
    }
    //delayMicroseconds(50);
    k++;
  }
  analogWrite(pin, 0);
  return last;
}
