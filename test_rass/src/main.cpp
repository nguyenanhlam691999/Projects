#include <Arduino.h>
#include <Arduino.h>
#include <SPI.h>
#include "mcp2515.h"
struct can_frame canMsg1;
struct can_frame canMsg2;
MCP2515 mcp2515(10);

void setup()
{
  // can bus
  while (!Serial)
    ;
  Serial.begin(9600);
  SPI.begin();
  mcp2515.reset();
  mcp2515.setBitrate(CAN_500KBPS);
  mcp2515.setNormalMode();
  canMsg1.can_id = 0x114;
  canMsg1.can_dlc = 8;
  canMsg1.data[0] = 0;
  canMsg1.data[1] = 0;
  canMsg1.data[2] = 0;
  canMsg1.data[3] = 0;
  canMsg1.data[4] = 0;
  canMsg1.data[5] = 0;
  canMsg1.data[6] = 0;
  canMsg1.data[7] = 0;
  canMsg2.can_id = 0x118;
  canMsg2.can_dlc = 8;
  canMsg2.data[0] = 0;
  canMsg2.data[1] = 0;
  canMsg2.data[2] =100;
  canMsg2.data[3] = 0;
  canMsg2.data[4] = 0;
  canMsg2.data[5] = 0;
  canMsg2.data[6] = 0;
  canMsg2.data[7] = 0;
 
}
void loop()
{
canMsg1.data[2]=96;
mcp2515.sendMessage(&canMsg1);
mcp2515.sendMessage(&canMsg2);
}