/***************************************************
   In this version, EVERYTHING WORKS!
   Turns out you cant name variables main....
   Blinking lights were addded.
   
 ****************************************************/

#include <Wire.h>
#include "Adafruit_Trellis.h"
#include <Ethernet.h>


/***************************************************
  This example shows reading buttons and setting/clearing buttons in a loop
  "momentary" mode has the LED light up only when a button is pressed
  "latching" mode lets you turn the LED on/off when pressed

  Up to 8 matrices can be used but this example will show 4 or 1
 ****************************************************/

#define MOMENTARY 0
#define LATCHING 1
// set the mode here
#define MODE LATCHING


Adafruit_Trellis matrix0 = Adafruit_Trellis();

// uncomment the below to add 3 more matrices

Adafruit_Trellis matrix1 = Adafruit_Trellis();
Adafruit_Trellis matrix2 = Adafruit_Trellis();
Adafruit_Trellis matrix3 = Adafruit_Trellis();
Adafruit_Trellis matrix4 = Adafruit_Trellis();
// you can add another 4, up to 8


// Just one
//Adafruit_TrellisSet trellis =  Adafruit_TrellisSet(&matrix0);
// or use the below to select 4, up to 8 can be passed in
Adafruit_TrellisSet trellis =  Adafruit_TrellisSet(&matrix0, &matrix1, &matrix2, &matrix3, &matrix4);

// set to however many you're working with here, up to 8
#define NUMTRELLIS 5

#define numKeys (NUMTRELLIS * 16)

// Connect Trellis Vin to 5V and Ground to ground.
// Connect the INT wire to pin #A2 (can change later!)
#define INTPIN A2
// Connect I2C SDA pin to your Arduino SDA line
// Connect I2C SCL pin to your Arduino SCL line
// All Trellises share the SDA, SCL and INT pin!
// Even 8 tiles use only 3 wires max

const int mainVD = 8;//dimensions of mainV
const int focusD = 4;//dims of Focus
boolean mainV[mainVD][mainVD];
boolean focus[focusD][focusD];
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

int c = 0;

EthernetUDP Udp;
byte mac[] = {
  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED
};
IPAddress ip(192, 168, 1, 177);

unsigned int localPort = 8888; 
// buffers for receiving and sending data
char packetBuffer[UDP_TX_PACKET_MAX_SIZE];  //buffer to hold incoming packet,
char  ReplyBuffer[] = "acknowledged";       // a string to send back

void setup() {
  // start the Ethernet and UDP:
  Ethernet.begin(mac, ip);
  Udp.begin(localPort);

  Serial.begin(9600);
  Serial.println("Trellis Demo");

  // INT pin requires a pullup
  pinMode(INTPIN, INPUT);
  digitalWrite(INTPIN, HIGH);

  // begin() with the addresses of each panel in order
  // I find it easiest if the addresses are in order
  //trellis.begin(0x70);  // only one
  trellis.begin(0x70, 0x71, 0x72, 0x73, 0x74);  // or four!

  // light up all the LEDs in order
  for (uint8_t i = 0; i < numKeys; i++) {
    trellis.setLED(i);
    trellis.writeDisplay();
    delay(5);
  }
  // then turn them off
  for (uint8_t i = 0; i < numKeys; i++) {
    trellis.clrLED(i);
    trellis.writeDisplay();
    delay(5);
  }
}

void filler() {
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

//converts backwards from the array to LED Matrix
//needs refinement (USE mainRef[][]);
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

//this funtion checks to see if there are other leds in the column that are on
//effectively, it checks for column power
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

  if (MODE == MOMENTARY) {
    // If a button was just pressed or released...
    if (trellis.readSwitches()) {
      // go through every button
      for (uint8_t i = 0; i < numKeys; i++) {
        // if it was pressed, turn it on
        if (trellis.justPressed(i)) {
          Serial.print("v"); Serial.println(i);
          trellis.setLED(i);
        }
        // if it was released, turn it off
        if (trellis.justReleased(i)) {
          Serial.print("^"); Serial.println(i);
          trellis.clrLED(i);
        }
      }
      // tell the trellis to set the LEDs we requested
      trellis.writeDisplay();
    }
  }

  if (MODE == LATCHING) {
    // If a button was just pressed or released...
    if (trellis.readSwitches()) {
      // go through every button
      for (uint8_t i = 0; i < numKeys; i++) {
        // if it was pressed...
        if (trellis.justPressed(i)) {
          Serial.print("v"); Serial.println(i);
          // Alternate the LED
          arrayManager(i);
          lighter();
        }
        
        
      }
      trellis.writeDisplay();
      arrayPrint();
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

