#include <Arduino.h>
#include <SPI.h>
#include "mcp2515.h"
// can bus
struct can_frame canMsg;
MCP2515 mcp2515(10);
int counter = 0;
// int vong = 0;
void ai0();
void setup()
{
  // can bus
  Serial.begin(9600);
  SPI.begin();
  mcp2515.reset();
  mcp2515.setBitrate(CAN_125KBPS);
  mcp2515.setNormalMode();
  //encoder
  pinMode(2, INPUT_PULLUP); // pin 2
  pinMode(3, INPUT_PULLUP);
  attachInterrupt(0, ai0, FALLING);
  pinMode(5, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(4, OUTPUT);
  digitalWrite(4, HIGH);
}
void loop()
{
  

    
  mcp2515.readMessage(&canMsg);
  Serial.println(canMsg.data[0]);
  while ((canMsg.can_id == 0x0F6) && canMsg.data[1] == 10)
  {
    mcp2515.readMessage(&canMsg);
    analogWrite(5, 100);
    analogWrite(9, 0);
    Serial.println("chay thang");
    if (canMsg.data[1] != 10)
    {
      break;
    }
  }
  while ((canMsg.can_id == 0x0F6) && canMsg.data[1] == 1)
  {
    mcp2515.readMessage(&canMsg);
    analogWrite(9, 100);
    analogWrite(5, 0);
    Serial.println("lui");
    if (canMsg.data[1] != 1)
    {
      break;
    }
  }
  while ((canMsg.can_id == 0x0F6) && canMsg.data[1] == 5)
  {
    mcp2515.readMessage(&canMsg);
    analogWrite(5, 0);
    analogWrite(9, 0);
    Serial.println("phanh");
    if (canMsg.data[1] != 5)
    {
      break;
    }
  }
}
void ai0()
{
  if (digitalRead(2) == LOW)
  {
    counter++;
    //Serial.println(counter);
    if (counter >= 100)
    {
      counter = 0;
    }
  }
}
