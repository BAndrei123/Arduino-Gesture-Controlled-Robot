#include <SPI.h>
#include "RF24.h"
#include "I2Cdev.h"
#include "MPU6050.h"

MPU6050 accelgyro;

int16_t ax, ay, az;
int16_t gx, gy, gz;

RF24 myRadio (7,8);
byte addresses[][6] = {"0"};

struct package
{
  int dir=0;
};

typedef struct package Package;
Package data;

void setup() {
  Wire.begin();
  Serial.begin(115200);
  delay(1000);
  myRadio.begin();
  myRadio.setChannel(115);
  myRadio.setPALevel(RF24_PA_MAX);
  myRadio.setDataRate(RF24_250KBPS);
  myRadio.openWritingPipe(addresses[0]);
  accelgyro.initialize();
}

void loop() {
  accelgyro.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
  
  myRadio.write(&data, sizeof(data));

  Serial.print("\nPackage:");
  Serial.print("\n");

  if(ax < -6000) {
    data.dir = 1; //forward
  }else if(ax > 6000) {
    data.dir = 2; //backward
    
  } else if(ay > 6000){
    data.dir = 3; //right
  }else if(ay < -6000){
    data.dir = 4; //left
  }else {
    data.dir = 0; //stay
  }
  Serial.println(data.dir);
}
