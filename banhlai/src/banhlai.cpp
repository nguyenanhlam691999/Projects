#include <Arduino.h>

const int stepPin = 3; //PUL
const int dirPin = 2; // DIR
const int enPin = 8; //ena
void setup() {
  
  pinMode(stepPin,OUTPUT); 
  pinMode(dirPin,OUTPUT);
  pinMode(enPin,OUTPUT);
  digitalWrite(enPin,LOW);
  pinMode(LED_BUILTIN,OUTPUT);
  
}
void loop() {
  digitalWrite(LED_BUILTIN,HIGH);
  delay(1000);
  digitalWrite(LED_BUILTIN,LOW);
  delay(1000);
  digitalWrite(dirPin,HIGH); // cho đông cơ quay theo chiều thuận
  
  for(int x = 0; x < 200; x++) { // CHẠY 1 VÒNG 200 STEP / 1.8 ĐỘ = 360, S1 S2 ON, S3 OFF
    digitalWrite(stepPin,HIGH); 
    delayMicroseconds(500); 
    digitalWrite(stepPin,LOW); 
    delayMicroseconds(500); 
  }
  delay(2000);
}
