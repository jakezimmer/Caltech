/**************************************************
 * In this version:
 *
 *Ethernet integration has begun.
 *
 * TO DO:
 * Coil Deactivation Timer
 * General event timer and manager
 *
 **************************************************/


#include <TimerOne.h>
#include <ADC.h>
#include <Ethernet.h>
#include <SPI.h>

/************
 * ADC Stuff
 ************/
const int readPin = A9;
//const int readPin2 = A3;
ADC *adc = new ADC();

/***********************
 * Magnet Reading Stuff
 ***********************/
int wholeSample[1000];
int section[100];
int temp=0;
int wSPlace=0;
unsigned long lastMillis = 0;
uint8_t last300[300];
unsigned long callSecs = 0;
boolean coilOn = false;
int onPin=5;
int cal=0;
int lastRead=0;
uint8_t readings[2];

/***********************
 * Ethernet Config Stuff
 ***********************/
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
unsigned int localPort = 12345;
IPAddress server(131,215,193,176);
//Less used options (Use if DHCP doesnt start)
/*********************************************/
IPAddress ip(169,254,24,252); //static IP
IPAddress myDns(131, 215, 139, 100); //configureable DNS
IPAddress gateway(131,215,193,254); //DNS
IPAddress subnet(255, 255, 255, 0); //subnet

/*************************
 * Ethernet Backend Stuff
 *************************/
const int eArrSize=16;
char packetBuffer[eArrSize];  //buffer to hold incoming packet,
//[CommandType][Payload]
char replyBuffer[eArrSize] ={};       // a string to send back
EthernetClient client;
IPAddress badip(255,255,255,255); //hardware failure IP

/***************************************************

  * S         E          T          U          P

 ***************************************************/
void setup(){
  pinMode(4, OUTPUT);
  digitalWrite(4, HIGH);   // de-select the SD Card
  delay(2000);
  /***********************
   * Begin PWM and Timers
   ***********************/
  Timer1.initialize(6);
  filler(wholeSample,130);
  Timer1.start();
  Timer1.pwm(3, 700);
  Serial.begin(115200);
  Serial.println("hello");
  delay(50);
  /**************************
   * Begin Ethernet and DHCP
   **************************/
  Ethernet.begin(mac);
  Serial.print("My IP address: ");
  Serial.println(Ethernet.localIP());
  //ip(Ethernet.localIP);  //create a backup of the configured ip address
  while (!client.connected()) {
    client.connect(server, 1201);
    Serial.println("connecting");
    // Make a HTTP request:nvb
    delay(1000);
  }
  Serial.println("connected");
  /*****************
   * Configure Pins
   *****************/
  pinMode(3,OUTPUT);
  pinMode(13,OUTPUT);
  digitalWrite(13,HIGH);
  pinMode(14, INPUT_PULLUP);
  pinMode(16,OUTPUT);
  delay(50);
  /****************************
   * Analog->Digital Configure
   ****************************/
  adc->setAveraging(1); // set number of averages
  adc->setResolution(10);
  adc->setConversionSpeed(ADC_HIGH_SPEED); // change the conversion speed
  adc->setSamplingSpeed(ADC_HIGH_SPEED); // change the sampling speed
}

/***************************************************

  * L           O             O            P

 ***************************************************/
void loop(){
  contacted(3);
  if (client.available()){
    parseInput();
  }
}
