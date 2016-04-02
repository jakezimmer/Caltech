//#include <Dhcp.h>
//#include <Dns.h>
//#include <Ethernet.h>
//#include <EthernetClient.h>
//#include <EthernetServer.h>
//#include <EthernetUdp.h>

//#include<Ethernet.h>

//#include <DhcpV2_0.h>
//#include <DnsV2_0.h>
//#include <EthernetClientV2_0.h>
//#include <EthernetServerV2_0.h>
//#include <EthernetUdpV2_0.h>
//#include <EthernetV2_0.h>
//#include <utilV2_0.h>

/***************************************************
   In this version, ethernet as client is being added

   Ethernet client mode is probably the most useful
   mode as the controller no longer needs to be
   connected to the telescope. In addition, the data-
   base is stored somewhere else and not in the
   EEPROM or an SD card.

   The current encoding for the
 ****************************************************/

#include <Wire.h>
#include "Adafruit_Trellis.h"
#include <Ethernet.h>
#include <SPI.h>

/***************************************************

   LED Stuff

****************************************************/

#define MOMENTARY 0
#define LATCHING 1
// set the mode here
#define MODE LATCHING
#define NUMTRELLIS 5
#define numKeys (NUMTRELLIS * 16)
#define INTPIN 23

Adafruit_Trellis matrix0 = Adafruit_Trellis();
Adafruit_Trellis matrix1 = Adafruit_Trellis();
Adafruit_Trellis matrix2 = Adafruit_Trellis();
Adafruit_Trellis matrix3 = Adafruit_Trellis();
Adafruit_Trellis matrix4 = Adafruit_Trellis();

Adafruit_TrellisSet trellis =  Adafruit_TrellisSet(&matrix0, &matrix1, &matrix2, &matrix3, &matrix4);

const int mainVD = 8;//dimensions of mainV
const int focusD = 4;//dims of Focus
boolean mainV[mainVD][mainVD];
boolean focus[focusD][focusD];
int c = 0;
//char chars[mainVD];
int mainRef[mainVD][mainVD] =
{ {1, 2, 3, 4, 17, 18, 19, 20},
  {5, 6, 7, 8, 21, 22, 23, 24},
  {9, 10, 11, 12, 25, 26, 27, 28},
  {13, 14, 15, 16, 29, 30, 31, 32},
  {33, 34, 35, 36, 49, 50, 51, 52},
  {37, 38, 39, 40, 53, 54, 55, 56},
  {41, 42, 43, 44, 57, 58, 59, 60},
  {45, 46, 47, 48, 61, 62, 63, 64}
};

/***************************************************

   Ethernet Stuff

****************************************************/

//EthernetUDP Udp;
//EthernetServer server(80);
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
//IPAddress ip(71, 5, 228, 37);
IPAddress ip(169,254,24,252);
IPAddress badip(255,255,255,255);
IPAddress myDns(131, 215, 139, 100);
IPAddress gateway(131,215,193,254);
IPAddress subnet(255, 255, 255, 0);
unsigned int localPort = 12345;
IPAddress server(131,215,193,176);
// buffers for receiving and sending data
char packetBuffer[UDP_TX_PACKET_MAX_SIZE];  //buffer to hold incoming packet,
char  replyBuffer[mainVD] = "";       // a string to send back
EthernetClient client;
/***************************************************

    End of global variables

****************************************************/
void setup() {

  trellis.begin(0x70, 0x71, 0x72, 0x73, 0x74);
  trellis.setLED(26);
  trellis.writeDisplay();
  delay(200);
  trellis.setLED(25);
  trellis.writeDisplay();
  delay(200);
  // start the Ethernet:

//  pinMode(9, OUTPUT);
//  digitalWrite(9,HIGH);
//  digitalWrite(9, LOW);   // reset the WIZ820io
  pinMode(4, OUTPUT);
  digitalWrite(4, HIGH);   // de-select the SD Card
  Serial.println("5 seconds");
  trellis.setLED(24);
  trellis.writeDisplay();
  delay(200);
  trellis.setLED(11);
  trellis.writeDisplay();
  delay(200);
  trellis.setLED(10);
  trellis.writeDisplay();
  delay(200);
  trellis.setLED(9);
  trellis.writeDisplay();
  delay(200);
  trellis.blinkRate(1);
  trellis.writeDisplay();
  
  Ethernet.begin(mac);
  // print the Ethernet board/shield's IP address:
  Serial.print("My IP address: ");
  Serial.println(Ethernet.localIP());
  trellis.blinkRate(0);
  trellis.writeDisplay();
//  while (Ethernet.localIP()==badip){
//    Serial.println("no bueno");
//    pinMode(9, OUTPUT);
//    digitalWrite(9, LOW);
//    delay(500);
//    Ethernet.begin(mac, ip);
//    
//  }

  // give the Ethernet shield a second to initialize:
  delay(1000);
  Serial.println("connecting...");


  // if you get a connection, report back via serial:
  while (!client.connected()) {
    client.connect(server, 1201);
    Serial.println("connecting");
    // Make a HTTP request:nvb
    delay(1000);
  }
  Serial.println("connected");



  // Serial.println("Trellis Demo");

  trellis.begin(0x70, 0x71, 0x72, 0x73, 0x74);
  filler();
}

void filler() {
  for (uint8_t i = 0; i < numKeys; i++) {
    trellis.setLED(i);
    trellis.writeDisplay();
    delay(5);
  }
  delay(500);
  // then turn them off
  for (uint8_t i = 0; i < numKeys; i++) {
    trellis.clrLED(i);

    delay(0);
    if (i % 4 == 0)
      trellis.writeDisplay();
  }
  trellis.writeDisplay();
  for (int i = 0; i < mainVD; i++) {
    for (int j = 0; j < mainVD; j++) {
      mainV[i][j] = false;
    }
  }
  for (int i = 0; i < focusD; i++) {
    for (int j = 0; j < focusD; j++) {
      focus[i][j] = false;
    }
  }
}

//converts led matrix state change into boolean in virtual array
void arrayManager(int l) {
  if (l < 16) {
    mainV[l / 4][l % 4] = !mainV[l / 4][l % 4];
  }
  else if (l < 32) {
    mainV[(l - 16) / 4][(l % 4) + 4] = !mainV[(l - 16) / 4][(l % 4) + 4];
  }
  else if (l < 48) {
    mainV[(l - 32) / 4 + 4][l % 4] = !mainV[(l - 32) / 4 + 4][l % 4];
  }
  else if (l < 64) {
    mainV[(l - 48) / 4 + 4][(l % 4) + 4] = !mainV[(l - 48) / 4 + 4][(l % 4) + 4];
  }
  else if (l < 80) {
    focus[(l - 64) / 4][(l % 4)] = !focus[(l - 64) / 4][(l % 4)];
  }

}


//converts backwards from the array to LED Matrix //needs refinement (USE mainRef[][]);
void arrayToMatrix(int i, int j, boolean state) {
  if (state) {
    if (i < 4 && j < 4) {
      trellis.setLED(i * 4 + j );
    }
    else if (i < 4) {
      trellis.setLED(i * 4 + j - 4 + 16);
    }
    else if (j < 4) {
      trellis.setLED(i * 4 + j + 16);
    }
    else {
      trellis.setLED(i * 4 + j - 4 + 32);
    }
  }
  else {
    if (i < 4 && j < 4) {
      trellis.clrLED(i * 4 + j );
    }
    else if (i < 4) {
      trellis.clrLED(i * 4 + j - 4 + 16);
    }
    else if (j < 4) {
      trellis.clrLED(i * 4 + j + 16);
    }
    else {
      trellis.clrLED(i * 4 + j - 4 + 32);
    }
  }
}


//this funtion checks to see if there are other leds in the column that are on //effectively, it checks for column power
boolean vert(int h) {
  boolean was = false;
  for (int i = 0; i < mainVD; i++) {
    if (mainV[i][h]) {
      was = true;
    }
  }
  return was;
}


//this one does the dame thing but horizontally for row power
boolean hori(int h) {
  boolean was = false;
  for (int i = 0; i < mainVD; i++) {
    if (mainV[h][i]) {
      was = true;
    }
  }
  return was;
}


//this one figures out which leds to light on the display
void lighter() {
  for (int i = 0; i < mainVD; i++) {
    for (int j = 0; j < mainVD; j++) {
      if (vert(j) && hori(i)) {
        arrayToMatrix(i, j, true);
      }
      else {
        arrayToMatrix(i, j, false);
      }
    }
  }
  trellis.writeDisplay();
}


//for testing purposes, prints the array to the console.
void arrayPrint() {
  Serial.println(" ");
  Serial.println("CurrentBoard");
  for (int i = 0; i < mainVD; i++) {
    Serial.print("[ ");
    for (int j = 0; j < mainVD; j++) {
      if (mainV[i][j]) {
        Serial.print("x ");
      }
      else {
        Serial.print("_ ");
      }
    }
    Serial.println("]");
  }
}


//this function blinks leds that are inherently on but werent turned on
void blinker() {
  for (int i = 0; i < mainVD; i++) {
    for (int j = 0; j < mainVD; j++) {
      if (trellis.isLED(mainRef[i][j] - 1) && !mainV[i][j])
        trellis.clrLED(mainRef[i][j] - 1);
    }
  }
}


void loop() {
  delay(30); // 30ms delay is required, dont remove me!

  if (MODE == LATCHING) {
    // If a button was just pressed or released...
    if (trellis.readSwitches()) {
      // go through every button
      for (uint8_t i = 0; i < numKeys; i++) {
        // if it was pressed...
        if (trellis.justPressed(i)) {
          Serial.print("v"); Serial.println(i);
          networkHandler(i);
          // Alternate the LED
          arrayManager(i);
          lighter();
        }
      }
      trellis.writeDisplay();
      // arrayPrint();
      // tell the trellis to set the LEDs we requested
    }
  }

  if (c == 0) {
    lighter();
    trellis.writeDisplay();
  }
  if (c == 2) {
    blinker();
    trellis.writeDisplay();
  }
  c++;
  if (c > 8)
    c = 0;



}

