#include <TimerOne.h>
#include <ADC.h>

const int readPin = A9;
//const int readPin = 23;

ADC *adc = new ADC();


void setup(){
  delay(2000);
  
  Timer1.initialize(6);
  phil();
  Timer1.start();
  Timer1.pwm(3, 700);
  Serial.begin(115200);
  Serial.println("hello");
  
  delay(50);
  
  //pinMode(23,INPUT);
  pinMode(3,OUTPUT);
  pinMode(13,OUTPUT);
  digitalWrite(13,HIGH);
  pinMode(14, INPUT_PULLUP);  
    pinMode(23, INPUT);  
  pinMode(16,OUTPUT);
  
  delay(50);

  adc->setAveraging(1); // set number of averages
  adc->setResolution(8);
  adc->setConversionSpeed(ADC_HIGH_SPEED); // change the conversion speed
    // it can be ADC_VERY_LOW_SPEED, ADC_LOW_SPEED, ADC_MED_SPEED, ADC_HIGH_SPEED or ADC_VERY_HIGH_SPEED
  adc->setSamplingSpeed(ADC_HIGH_SPEED); // change the sampling speed

}
void loop(){
  contacted();
  
}
