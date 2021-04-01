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
// dem vong queo
int demvongqueo = 0;
int chieuvongqueo = 0;
void setup()
{
  // can bus
  Serial.begin(9600);
  SPI.begin();
  mcp2515.reset();
  mcp2515.setBitrate(CAN_125KBPS);
  mcp2515.setNormalMode();
  // control step motor
  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);
  pinMode(enPin, OUTPUT);
  digitalWrite(enPin, LOW);
  pinMode(9, OUTPUT);
  pinMode(LED_BUILTIN,OUTPUT);
}
void loop()
{
  mcp2515.readMessage(&canMsg);
  // queo phai

  while ((canMsg.can_id == 0x0F6) && canMsg.data[0] == 3)
  {
    mcp2515.readMessage(&canMsg);
    Serial.println(demvongqueo);
    chieuvongqueo = 1;
    if (demvongqueo == 5)
    {
      
      break;
    }
     if (canMsg.data[0] == 4)
    {
          break;
    }
 
    nalam.queo_phai(dirPin, stepPin);
    demvongqueo++;
    Serial.println(" queo phai");
    delay(10);
  }
  // queo trai
  while ((canMsg.can_id == 0x0F6) && canMsg.data[0] == 2)
  {
    mcp2515.readMessage(&canMsg);
    Serial.println(demvongqueo);
    chieuvongqueo = 2;
        if (demvongqueo == 5)
    {

      break;
    }
      if (canMsg.data[0] == 4)
    {
          break;
    }
    nalam.queo_trai(dirPin, stepPin);
    demvongqueo++;
    Serial.println("queo trai");
    delay(10);
  }
  // tra lai
  while ((canMsg.can_id == 0x0F6) && canMsg.data[0] == 4)
  {
    if (chieuvongqueo == 1)
    {
      nalam.tralai_phai(dirPin, stepPin);
      Serial.println("tra lai phai");
    }
    if (chieuvongqueo == 2)
    {
      nalam.tralai_trai(dirPin, stepPin);
      Serial.println("tra lai trai");
    }
    if (demvongqueo < 0)
    {
      chieuvongqueo = 0;
      break;
    }
    demvongqueo--;
    Serial.println(demvongqueo);
    delay(10);
  }
}
