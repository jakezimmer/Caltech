int wholeSample[1000];
int wholeSample2[1000];
int section[100];
int section2[100];
int temp;
int wSPlace=0;
ADC::Sync_result result;

void phil(){
  filler(wholeSample,500);
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

void contacted(){
  int k=0;
  analogWriteFrequency(3, 30000);
  analogWrite(3, 127);
  //Timer1.pwm(3, 512, 33);
    //delay(1);
  //Timer1.restart();
  for (int i=0; i<100000;i++){
    //Timer1.setPeriod(50);
    //Timer1.restart();
    delayMicroseconds(2);
    result = adc->readSynchronizedContinuous();
    result.result_adc0 = (uint16_t)result.result_adc0;
    result.result_adc1 = (uint16_t)result.result_adc1;
    section[k]=result.result_adc0;
    section2[k]=result.result_adc1;
    
    //delayMicroseconds(15);
    if ((i+1)%100==0){
      wholeSample[i/100]=greatest(section);
      wholeSample2[i/100]=greatest(section2);
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
      //Timer1.restart();
      
    }
    if (i%10000==0){
      //Timer1.stop();
      
      Serial.begin(115200);
      //Serial.println(0+map(avg(wholeSample),6600,7000,0,100));
      Serial.println("one");
      Serial.println((avg(wholeSample)));
      Serial.println("two");
      Serial.println((avg(wholeSample2)));
      Serial.end();

      wSPlace=0;
      
      //Timer1.resume();
    }
    //delayMicroseconds(50);
    k++;
  }
  
}
