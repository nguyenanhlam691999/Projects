#include <Arduino.h>
#include<my_lib.h>
#include<SPI.h>
#include<SoftwareSerial.h>
#include"mcp2515.h"
SoftwareSerial blue(2, 3);
const int stepPin = 3; //PUL
const int dirPin = 2;  // DIR
const int enPin = 8;   //ena

car nalam;
void setup()
{
  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);
  pinMode(enPin, OUTPUT);
  digitalWrite(enPin, LOW);

  Serial.begin(9600);
  blue.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);
  
}
void loop()
{
  nalam.queo_phai(dirPin, stepPin);
  nalam.queo_trai(dirPin, stepPin);

  int tinhieudieukhien;
  if (blue.available())
  {
    tinhieudieukhien=blue.read();
    
  }
}

