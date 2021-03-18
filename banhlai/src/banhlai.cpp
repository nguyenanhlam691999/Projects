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
}
void loop()
{
  mcp2515.readMessage(&canMsg);
// queo phai
  while ((canMsg.can_id == 0x0F6) && canMsg.data[0] == 1)
  {
    
    Serial.println(demvongqueo);
    chieuvongqueo = 1;
    nalam.queo_phai(dirPin, stepPin);
    Serial.println(" queo phai");
    if (demvongqueo==5)
    {
      Serial.println("ngung tang toc queo phai");
      break;
    }
    demvongqueo++;
    delay(100);
  }
  // queo trai
  while ((canMsg.can_id == 0x0F6) && canMsg.data[0] == 2)
  {
   
    Serial.println(demvongqueo);
    chieuvongqueo = 2;
    nalam.queo_trai(dirPin, stepPin);
    Serial.println("queo trai");
    if (demvongqueo == 5)
    {
      Serial.println("ngung tang goc queo trai");
      break;
    }
    demvongqueo++;
    delay(100);
  }
  // tra lai
  while ((canMsg.can_id == 0x0F6) && canMsg.data[0] == 0)
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
    if (demvongqueo == 0 )
    {
      chieuvongqueo = 0;
      break;
    }
    demvongqueo--;
    
    delay(100);
  }
}
