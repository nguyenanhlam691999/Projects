#include <Arduino.h>
int counter = 0;
int vong = 0;
void ai0();

void setup()
{
  Serial.begin(9600);
  pinMode(2, INPUT_PULLUP); // pin 2
  pinMode(3, INPUT_PULLUP);
  attachInterrupt(0, ai0, FALLING);
}
void loop()
{
  Serial.println(counter);
}
void ai0()
{
  if (digitalRead(2) == LOW)
  {
    counter++;
    if (counter>=20)
    {
      counter=0;
      vong++;

    }
    
    
  }
  
  
}
