#include <Arduino.h>
#include <SPI.h> //Library for using SPI Communication
#include <mcp2515.h> //Library for using CAN Communication
//khai bao kieu du lieu can_frame
struct can_frame canMsg;
// type def
MCP2515 mcp2515(10);
void setup()
{
 // khai bao su dung serial o toc do 9600
 Serial.begin(9600); 
 SPI.begin();
 // set bo mcp2515
 mcp2515.reset();
 mcp2515.setBitrate(CAN_125KBPS);
 mcp2515.setNormalMode();
 //khai bao LED
 
 pinMode(9, OUTPUT);
}
void loop()
{ //doc du lieu tu mang can
 mcp2515.readMessage(&canMsg);
 Serial.println(canMsg.can_id);
 // neu id nhan = id gui mong muon
 if ((canMsg.can_id == 0x0F6)&& canMsg.data[0]==1)
 {
 
 digitalWrite(9, HIGH);
 delay(100);
 digitalWrite(9, LOW);
 Serial.println(canMsg.can_id); Serial.println(canMsg.data[0], HEX);
 }
 delay(1000);
}