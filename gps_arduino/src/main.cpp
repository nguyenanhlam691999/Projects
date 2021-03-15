#include <Arduino.h>
#include "avr8-stub.h"

void setup()
{
  // initialize GDB stub
  debug_init();
  pinMode(LED_BUILTIN, OUTPUT);
  int a=10;
}

void loop()
{
  
  digitalWrite(LED_BUILTIN, HIGH);
  //delay(1000);
  digitalWrite(LED_BUILTIN, LOW);
  //delay(1000);
  //breakpoint();
  int a=7 ;
  //breakpoint();
  a=9;
  breakpoint();
  a++;
  
}
// #include <TinyGPS++.h>
// #include <SoftwareSerial.h>

// static const int RXPin = 4, TXPin = 3;
// static const uint32_t GPSBaud = 9600;

// TinyGPSPlus gps;

// SoftwareSerial ss(RXPin, TXPin);

// void setup(){
//   Serial.begin(9600);
//   ss.begin(GPSBaud);
// }

// void loop(){
  
//   while (ss.available() > 0){
//     gps.encode(ss.read());
//     if (gps.location.isUpdated()){
//       Serial.print("Latitude= "); 
//       Serial.print(gps.location.lat(), 6);
//       Serial.print(" Longitude= "); 
//       Serial.println(gps.location.lng(), 6);
//     }
//   }
// }