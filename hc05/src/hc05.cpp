#include <Arduino.h>
#include <SoftwareSerial.h>
#include"my_lib.h"
SoftwareSerial blue(2, 3);
custom_led ledblink;
void setup()
{
  Serial.begin(9600);
  blue.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop()
{
  int tinhieudieukhien;
  if (blue.available())
  {
    tinhieudieukhien=blue.read();
    ledblink.custom_led_run_condition(tinhieudieukhien,LED_BUILTIN);
  }
  
}