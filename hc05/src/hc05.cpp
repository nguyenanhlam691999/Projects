#include <Arduino.h>
#include <SoftwareSerial.h>
#include "my_lib.h"
#include <SPI.h>
#include "mcp2515.h"
struct can_frame canMsg1;
MCP2515 mcp2515(10);
SoftwareSerial blue(2, 3);
void setup()
{
  // can bus
  while (!Serial)
    ;
  Serial.begin(9600);
  SPI.begin();
  mcp2515.reset();
  mcp2515.setBitrate(CAN_125KBPS);
  mcp2515.setNormalMode();
  canMsg1.can_id = 0x0F6;
  canMsg1.can_dlc = 8;
  canMsg1.data[0] = 0;
  canMsg1.data[1] = 0;
  canMsg1.data[2] = 0;
  canMsg1.data[3] = 0;
  canMsg1.data[4] = 0;
  canMsg1.data[5] = 0;
  canMsg1.data[6] = 0;
  canMsg1.data[7] = 0;
  // bluetooth
  blue.begin(9600);
  pinMode(9, OUTPUT);
}
void loop()
{
  /////////////////////////////send_speed_phone/////////////////////////////
  /////////////////////////////receive/////////////////////////////
  int tinhieudieukhien = 0;
  if (blue.available())
  {
    Serial.println("connect");
    tinhieudieukhien = blue.read();
    /////////////////////////////canMsg.data[1]/////////////////////////////
    if (tinhieudieukhien == 100)
    {
      // can bus
      // di thang
      canMsg1.data[1] = 10;
      mcp2515.sendMessage(&canMsg1);
    }
    if (tinhieudieukhien == 101)
    {
      // can bus
      // lui
      canMsg1.data[1] = 1;
      mcp2515.sendMessage(&canMsg1);
    }
    if (tinhieudieukhien == 105)
    {
      // can bus
      // phanh
      canMsg1.data[1] = 5;
      mcp2515.sendMessage(&canMsg1);
    }
    /////////////////////////////canMsg.data[0]/////////////////////////////
    if (tinhieudieukhien == 110)
    {
      // ngung danh lai
      canMsg1.data[0] = 10;
      mcp2515.sendMessage(&canMsg1);
    }
    if (tinhieudieukhien == 103)
    {
      // can bus
      // queo phai
      canMsg1.data[0] = 3;
      mcp2515.sendMessage(&canMsg1);
    }
    if (tinhieudieukhien == 102)
    {
      // can bus
      // queo trai
      canMsg1.data[0] = 2;
      mcp2515.sendMessage(&canMsg1);
    }
    if (tinhieudieukhien == 104)
    {
      // tra lai
      canMsg1.data[0] = 4;
      mcp2515.sendMessage(&canMsg1);
    }
    Serial.println(tinhieudieukhien);
    delay(10);
  }
}