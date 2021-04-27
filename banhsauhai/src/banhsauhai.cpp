// Program controlls dc motor by using can bus and interrupt
// hardware : arduino nano, mcp2515, h bridge 43a
#include <Arduino.h>
#include <SPI.h>
#include "mcp2515.h"
#include <my_lib.h>
#include "PID_v1.h"

// resert time
void reset_time();
// val pid
double val_so_sanh = 0;
// val pid count
unsigned int val_pulse = 0;
int val_speed = 0;
unsigned int val_old_pulse = 0;
extern volatile unsigned long timer0_millis;
// val resert millis
extern volatile unsigned long timer0_millis;
// can bus
struct can_frame canMsg;
MCP2515 mcp2515(10);
// void count
void count_pulse();
//pid set up
double Setpoint, Input, Output;
double Kp = 1, Ki = 0, Kd = 0;
PID myPID(&Input, &Output, &Setpoint, Kp, Ki, Kd, DIRECT);
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

  // dc motor
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(4, OUTPUT);
  digitalWrite(4, HIGH);
  // pid
  Setpoint = 100;
  Input = val_speed;
  myPID.SetMode(AUTOMATIC);
}
void loop()
{
  analogWrite(6, 100);
    analogWrite(5, 0);
  // can bus and control dc motor
  mcp2515.readMessage(&canMsg);
  //Serial.println(canMsg.data[0]);
  while ((canMsg.can_id == 0x0F6) && canMsg.data[1] == 10)
  {
    attachInterrupt(0, count_pulse, FALLING);
    mcp2515.readMessage(&canMsg);
    if (canMsg.data[1] != 10)
    {
      break;
    }
    //Serial.println("GO AHEAD");
    while (true)
    {
      if (millis() >= 100)
      {
        //Serial.print("itme  ");
        //Serial.println(millis());
        noInterrupts();
        val_speed = (val_pulse * 60) / (96 * 0.1);
        timer0_millis = 0;
        val_pulse = 0;
        Serial.print("speed  ");
        Serial.println(val_speed);
        interrupts();
        attachInterrupt(0, count_pulse, FALLING);
        break;
      }
    }
    Input = val_speed;
    myPID.Compute();
    if (Output > 0)
    {
      val_so_sanh = Output;
      analogWrite(5, Output);
      analogWrite(6, 0);
    }
    if (Output == 0)
    {
      analogWrite(5, val_so_sanh);
      analogWrite(6, 0);
    }
  }
  while ((canMsg.can_id == 0x0F6) && canMsg.data[1] == 1)
  {
    mcp2515.readMessage(&canMsg);
    analogWrite(6, 100);
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
    analogWrite(6, 0);
    Serial.println("BREAK");
    if (canMsg.data[1] != 5)
    {
      break;
    }
  }
 reset_time();
}
void count_pulse()
{
  if (digitalRead(2) == LOW)
  {
    val_pulse++;
  }
}
void reset_time()
{
  noInterrupts();
  timer0_millis = 0;
  interrupts();
}