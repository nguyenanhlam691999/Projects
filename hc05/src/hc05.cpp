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
  int tinhieudieukhien=0;
  if (blue.available())
  {
    tinhieudieukhien = blue.read();
    
    if (tinhieudieukhien == 100)
    {
      digitalWrite(9, HIGH);
      delay(100);
      // can bus
      canMsg1.data[0] = 1;
      mcp2515.sendMessage(&canMsg1);
      delay(500);
    
    }
    if (tinhieudieukhien == 200)
    {
      digitalWrite(9, LOW);
      // can bus
      canMsg1.data[0] = 0;
      mcp2515.sendMessage(&canMsg1);
      delay(500);
      
      
    }
  }
Serial.println(tinhieudieukhien);
  delay(100);
}