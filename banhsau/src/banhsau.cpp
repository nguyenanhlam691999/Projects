// Program controlls dc motor by using can bus and interrupt
// hardware : arduino nano, mcp2515, h bridge 43a
#include <Arduino.h>
#include <SPI.h>
#include "mcp2515.h"
// val resert millis
extern volatile unsigned long timer0_millis;
// can bus
struct can_frame canMsg;
MCP2515 mcp2515(10);
int val_pulse = 0;
int val_circle = 0;
// int vong = 0;
void count_pulse();
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
  attachInterrupt(0, count_pulse, FALLING);
  // dc motor
  pinMode(5, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(4, OUTPUT);
  digitalWrite(4, HIGH);
}
void loop()
{
  // resert millis()
   if (millis() >= 1000)
  {
    noInterrupts();
    timer0_millis = 0;
    interrupts();
  }
  Serial.print("time : ");
  Serial.println(millis());
  delay(100);
  // can bus and control dc motor
  mcp2515.readMessage(&canMsg);
  Serial.println(canMsg.data[0]);
  while ((canMsg.can_id == 0x0F6) && canMsg.data[1] == 10)
  {
    mcp2515.readMessage(&canMsg);
    analogWrite(5, 100);
    analogWrite(9, 0);
    Serial.println("GO AHEAD");
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
    Serial.println("REVERSE");
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
    Serial.println("BREAK");
    if (canMsg.data[1] != 5)
    {
      break;
    }
  }
}
void count_pulse()
{
  if (digitalRead(2) == LOW)
  {
    val_pulse++;
    if (val_pulse >= 96)
    {
      val_pulse = 0;
      val_circle++;
    }
  }
}
