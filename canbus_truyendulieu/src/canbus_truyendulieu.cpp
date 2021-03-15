#include <Arduino.h>

struct can_frame canMsg1;
MCP2515 mcp2515(10);

void setup()
{
    
    while (!Serial);
    Serial.begin(9600);
    SPI.begin();
    mcp2515.reset();
    mcp2515.setBitrate(CAN_125KBPS);
    mcp2515.setNormalMode();
    Serial.begin(9600);
    pinMode(LED_BUILTIN,OUTPUT);
}
void loop()
{
       
  canMsg1.can_id = 0x0F6;
  canMsg1.can_dlc = 8;
  canMsg1.data[0] = 0X01;
  canMsg1.data[1] = 1;
  canMsg1.data[2] = 0;
  canMsg1.data[3] = 0;
  canMsg1.data[4] = 0;
  canMsg1.data[5] = 0;
  canMsg1.data[6] = 0;
  canMsg1.data[7] = 0;
  mcp2515.sendMessage(&canMsg1);
  Serial.println("abc");
  delay(100)
  digitalWrite(LED_BUILTIN,HIGH);
  a=5;
   
}