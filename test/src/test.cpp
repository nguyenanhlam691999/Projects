#include <Arduino.h>
extern volatile unsigned long timer0_millis;
void setup()
{
  Serial.begin(9600);
  
}

void loop()
{

  if (millis() >= 1000)
  {
    noInterrupts();
    timer0_millis = 0;
    interrupts();
  }
  Serial.print("time : ");
  Serial.println(millis());
  delay(100);
}
