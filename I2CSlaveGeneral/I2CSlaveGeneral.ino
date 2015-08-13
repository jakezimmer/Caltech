#include <i2c_t3.h>
#include <TimerOne.h>

#define WRITE    0x10
#define READ     0x20
#define SETRATE  0x30

String input;
uint8_t sensorsTotal[4];
uint8_t cmd;
size_t addr;


void setup() {
  delay(2000);
  
  Timer1.initialize(6);
  phil();
  Timer1.start();
  Timer1.pwm(4, 700);
  // Setup for Slave mode, address 0x44, pins 18/19, external pullups, 400kHz
  // Each slave must have its own address, designate in hex.
  Wire.begin(I2C_SLAVE, 0x01, I2C_PINS_18_19, I2C_PULLUP_EXT, I2C_RATE_400);
  memset(sensorsTotal, 0, sizeof(sensorsTotal));
  cmd = 0;
  addr = 0;
}

void loop() {
  
  while (Wire.available()){
    
    
  }
  
  
}
