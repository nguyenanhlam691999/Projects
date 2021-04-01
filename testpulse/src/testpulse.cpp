#include <Arduino.h>
unsigned int val_pulse = 0;
float val_speed = 0;
unsigned int val_old_pulse = 0;
extern volatile unsigned long timer0_millis;

void count_pulse();
void setup()
{
  Serial.begin(9600);
  pinMode(2, INPUT_PULLUP);
  pinMode(5, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(4, OUTPUT);
  digitalWrite(4, HIGH);
  attachInterrupt(0, count_pulse, FALLING);
}
void loop()
{

  analogWrite(5, 75);
  analogWrite(9, 0);
  while (millis() <= 500)
  {
    if (millis() >= 100)
    {
      noInterrupts();
      val_speed = (val_pulse ) / (96.0 * 0.5);
      timer0_millis = 0;
      Serial.println(val_speed);
      val_pulse = 0;
      interrupts();
      attachInterrupt(0, count_pulse, FALLING);
      break;
    }
  }
}
void count_pulse()
{
  if (digitalRead(2) == LOW)
  {
    val_pulse++;
  }
}