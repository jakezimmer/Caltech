/**************************************************
 * In this version:
 * 
 * First go at cleaning up code from "PWM Tester" and
 * importing everything into the final form.
 * 
 * Ethernet is soon to be added in V1.1
 * 
 **************************************************/


#include <TimerOne.h>
#include <ADC.h>

/************
 * ADC Stuff
 ************/
const int readPin = A9;
const int readPin2 = A3;
ADC *adc = new ADC();

/************************
 * Magnet Reading Stuff
 ***********************/
int wholeSample[1000];
int wholeSample2[1000];
int section[100];
int section2[100];
int temp;
int wSPlace=0;
int cal;
int lastRead;


void setup(){
  delay(2000);
  
  Timer1.initialize(6);
  filler(wholeSample,130);
  Timer1.start();
  Timer1.pwm(3, 700);
  Serial.begin(115200);
  Serial.println("hello");
  
  delay(50);
  
  pinMode(3,OUTPUT);
  pinMode(13,OUTPUT);
  digitalWrite(13,HIGH);
  pinMode(14, INPUT_PULLUP);  
  pinMode(16,OUTPUT);
  
  delay(50);

  adc->setAveraging(1); // set number of averages
  adc->setResolution(10);
  adc->setConversionSpeed(ADC_HIGH_SPEED); // change the conversion speed
  adc->setSamplingSpeed(ADC_HIGH_SPEED); // change the sampling speed

   


}
void loop(){
  contacted(3);
  
}
