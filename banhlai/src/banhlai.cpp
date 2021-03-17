#include <Arduino.h>
#include <my_lib.h>
#include <SPI.h>
#include "mcp2515.h"
// can bus
struct can_frame canMsg;
MCP2515 mcp2515(10);
// step motor
const int stepPin = 3; //PUL
const int dirPin = 2;  // DIR
const int enPin = 8;   //ena
// my_lib
car nalam;
void setup()
{
  Serial.begin(9600);
  SPI.begin();
  mcp2515.reset();
  mcp2515.setBitrate(CAN_125KBPS);
  mcp2515.setNormalMode();
  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);
  pinMode(enPin, OUTPUT);
  digitalWrite(enPin, LOW);

  pinMode(9, OUTPUT);
}
void loop()
{
  // nalam.queo_phai(dirPin, stepPin);
  // nalam.queo_trai(dirPin, stepPin);
  mcp2515.readMessage(&canMsg);
  Serial.println(canMsg.can_id);
  // neu id nhan = id gui mong muon
  if ((canMsg.can_id == 0x0F6) && canMsg.data[0] == 1)
  {
    Serial.println(canMsg.can_id);
    Serial.println(canMsg.data[0], HEX);
    nalam.queo_phai(dirPin,stepPin,canMsg.data[0]);
  }
  delay(1000);
}
