#include <i2c_t3.h>

#define WRITE    0x10
#define READ     0x20
#define SETRATE  0x30

String input;
int sensorsTotal[16];

void setup() {
  Serial.begin(115200);
  Wire.begin(I2C_MASTER, 0x00, I2C_PINS_18_19, I2C_PULLUP_EXT, I2C_RATE_400);

}

void loop() {
  
  while(Serial.available()){
    commandSelector();
  }
  
  
}
