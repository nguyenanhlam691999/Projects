#include <Arduino.h>
const int stepPin = 3; //PUL
const int dirPin = 2;  // DIR
const int enPin = 8;   //ena
void queo_phai(const int dirr, const int stepPinn);
void queo_trai(const int dirr, const int stepPinn);
void setup()
{
  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);
  pinMode(enPin, OUTPUT);
  digitalWrite(enPin, LOW);
  pinMode(LED_BUILTIN, OUTPUT);
}
void loop()
{

  queo_phai(dirPin, stepPin);
  queo_trai(dirPin, stepPin);
}

void queo_phai(const int dirPinn, const int stepPinn)
{
  digitalWrite(dirPinn, HIGH);
  for (char i = 0; i < 8; i++)
  {
    for (int x = 0; x < 200; x++)
    {
      digitalWrite(stepPinn, HIGH);
      delayMicroseconds(1000);
      digitalWrite(stepPinn, LOW);
      delayMicroseconds(1000);
    }
    delay(10);
  }

  digitalWrite(dirPinn, LOW);
  for (char i = 0; i < 8; i++)
  {
    for (int x = 0; x < 200; x++)
    {
      digitalWrite(stepPinn, HIGH);
      delayMicroseconds(1000);
      digitalWrite(stepPinn, LOW);
      delayMicroseconds(1000);
    }
    delay(10);
  }
}

void queo_trai(const int dirPinn, const int stepPinn)
{
  digitalWrite(dirPinn, LOW);
  for (char i = 0; i < 8; i++)
  {
    for (int x = 0; x < 200; x++)
    {
      digitalWrite(stepPinn, HIGH);
      delayMicroseconds(1000);
      digitalWrite(stepPinn, LOW);
      delayMicroseconds(1000);
    }
    delay(10);
  }
  digitalWrite(dirPinn, HIGH);
  for (char i = 0; i < 8; i++)
  {
    for (int x = 0; x < 200; x++)
    {
      digitalWrite(stepPinn, HIGH);
      delayMicroseconds(1000);
      digitalWrite(stepPinn, LOW);
      delayMicroseconds(1000);
    }
    delay(10);
  }
}