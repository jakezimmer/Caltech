void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:

}

#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>

// GUItool: begin automatically generated code
AudioInputAnalog         adc1;           //xy=152,307
AudioAnalyzePeak         peak1;          //xy=429,280
AudioConnection          patchCord1(adc1, peak1);
// GUItool: end automatically generated code

