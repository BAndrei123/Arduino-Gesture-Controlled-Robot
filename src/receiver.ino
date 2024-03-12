#include <SPI.h>
#include "RF24.h"

RF24 myRadio (8,9);
struct package{
  
  int dir=0;
};
int in1=2;
int in2=4;
int enA=3;

int in3=5;
int in4=7;
int enB=6;
byte adresses[][6]={"0"};

typedef struct package Package;
Package data;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  delay(500);

  myRadio.begin();
  myRadio.setChannel(115);
  myRadio.setPALevel(RF24_PA_MAX);
  myRadio.setDataRate(RF24_250KBPS);
  myRadio.openReadingPipe(1,adresses[0]);
  myRadio.startListening();
  pinMode(enA, OUTPUT);
   pinMode(in1,OUTPUT);
   pinMode(in2,OUTPUT);
   pinMode(enB,OUTPUT);
   pinMode(in3,OUTPUT);  
   pinMode(in4,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(myRadio.available()){
    while(myRadio.available()){
      myRadio.read(&data,sizeof(data));
    }
  }
  Serial.println(data.dir);
 if(data.dir==1) {
  Serial.println("Forward");
   digitalWrite(in1,HIGH);
  digitalWrite(in2,LOW);
    digitalWrite(in3,HIGH);
    digitalWrite(in4,LOW);
    digitalWrite(enA,100);
    digitalWrite(enB,100);
    delay(500);
}else if(data.dir==2) {
     
     digitalWrite(in1,LOW);
  digitalWrite(in2,HIGH);
    digitalWrite(in3,LOW);
    digitalWrite(in4,HIGH);
    digitalWrite(enA,100);
    digitalWrite(enB,100);
      Serial.println("Bakward");
      
} else if(data.dir==3){
   digitalWrite(in1,HIGH);
  digitalWrite(in2,LOW);
    digitalWrite(in3,LOW);
    digitalWrite(in4,HIGH);
    digitalWrite(enA,100);
    digitalWrite(enB,100);
    Serial.println("Right");
   
}else if(data.dir==4){
    digitalWrite(in1,LOW);
  digitalWrite(in2,HIGH);
    digitalWrite(in3,HIGH);
    digitalWrite(in4,LOW);
    digitalWrite(enA,100);
    digitalWrite(enB,100);
    Serial.println("Left");
   
}else if(data.dir==0){
     digitalWrite(in1,LOW);
  digitalWrite(in2,LOW);
  digitalWrite(in3,LOW);
  digitalWrite(in4,LOW);
  digitalWrite(enA,100);
  digitalWrite(enB,100);

    Serial.println("stay");
    
  }
}
