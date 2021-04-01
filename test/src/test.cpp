#include <Arduino.h>
#include <PID_v1.h>
double val_tin_hieu_dieu_khien=0;
double val_so_sanh=0;

//val couter
unsigned int val_pulse = 0;
int val_speed = 0;
unsigned int val_old_pulse = 0;
extern volatile unsigned long timer0_millis;

// void count
void count_pulse();
// pid
double Setpoint, Input, Output;
double Kp = 0.7, Ki = 0.0006, Kd = 20;
PID myPID(&Input, &Output, &Setpoint, Kp, Ki, Kd, DIRECT);
void setup()
{
  Serial.begin(9600);
  pinMode(5, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(4, OUTPUT);
  digitalWrite(4, HIGH);
  // encoder
  pinMode(2, INPUT_PULLUP); // pin 2
  pinMode(3, INPUT_PULLUP);
  attachInterrupt(0, count_pulse, FALLING);
  // pid
  Setpoint = 100;
  Input = val_speed;
  myPID.SetMode(AUTOMATIC);
}
void loop()
{
  while (millis() <= 500)
  {
    if (millis() >= 100)
    {
      noInterrupts();
      val_speed = (val_pulse * 60) / (96 * 0.1);
      timer0_millis = 0;
      val_pulse = 0;
      interrupts();
      attachInterrupt(0, count_pulse, FALLING);
      break;
    }
  }
  Input = val_speed;
  myPID.Compute();
  
  if (Output > 0)
  {
    val_so_sanh=Output;
    analogWrite(5, Output);
    analogWrite(9, 0);
  }
  // analogWrite(5, 100);
  // analogWrite(9, 0);
  Serial.print("speed  ");
  Serial.println(val_speed);
  
  if (Output==0)
  {
    analogWrite(5, val_so_sanh);
    analogWrite(9, 0);
  }
  
  
}
// program interrupt
void count_pulse()
{
  if (digitalRead(2) == LOW)
  {
    val_pulse++;
  }
}
