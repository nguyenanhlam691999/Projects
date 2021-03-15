#include <Arduino.h>
uint8_t a = 0;
void setup()
{
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop()
{
  if (Serial.available() > 0)
  {
    a = Serial.read();
    Serial.print(a);
    if (a == 5)
    {
      digitalWrite(LED_BUILTIN, HIGH);
      delay(1000);
      digitalWrite(LED_BUILTIN, LOW);
      delay(100);
    }
  }

  
}