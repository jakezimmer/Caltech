#include <TimerZero.h>
#include <ADC.h>
//#include "Arduino.h"
const int readPin = A9;
const int readPin2 = A3;

ADC *adc = new ADC();

int cal;

void setup(){
  delay(2000);
  
  Timer0.initialize(5);
  phil();
  Timer0.start();
  Timer0.pwm(5, 512, 30);
  Serial.begin(115200);
  Serial.println("hello");
  
  delay(50);
  
  //pinMode(23,INPUT);
  pinMode(5,OUTPUT);
  pinMode(13,OUTPUT);
  digitalWrite(13,HIGH);
  pinMode(14, INPUT_PULLUP);  
  pinMode(16,OUTPUT);
  
  delay(50);

  adc->setAveraging(1); // set number of averages
  adc->setResolution(10);
  adc->setConversionSpeed(ADC_HIGH_SPEED); // change the conversion speed
    // it can be ADC_VERY_LOW_SPEED, ADC_LOW_SPEED, ADC_MED_SPEED, ADC_HIGH_SPEED or ADC_VERY_HIGH_SPEED
  adc->setSamplingSpeed(ADC_HIGH_SPEED); // change the sampling speed

//  adc->setAveraging(1, ADC_1); // set number of averages
//  adc->setResolution(8, ADC_1); // set bits of resolution
//  adc->setConversionSpeed(ADC_HIGH_SPEED, ADC_1); // change the conversion speed
//  adc->setSamplingSpeed(ADC_HIGH_SPEED, ADC_1); // change the sampling speed

  //adc->startContinuous(23);
   


}
void loop(){
  contacted();
  Serial.println("break");
}
