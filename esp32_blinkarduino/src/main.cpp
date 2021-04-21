#include <Arduino.h>
#include <BluetoothSerial.h>
#include <CAN.h>

BluetoothSerial mybt;
int val_bt;
int val_old_time=0;
int val_new_time=0;
void led_blink();

void setup()
{

  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);
  mybt.begin("nalam_day");
  //can bus setup
  while (!Serial)
    ;
  Serial.println("CAN Sender");
  // start the CAN bus at 500 kbps
  if (!CAN.begin(125E3))
  {
    Serial.println("Starting CAN failed!");
    while (1)
      ;
  }
}

void loop()
{
  while (true)
  {
    val_new_time=millis();
    if ((val_new_time - val_old_time)==1000)
    {
      Serial.println("1000 ngat");
      led_blink();
      val_old_time=val_new_time;
      break;

    }
    
  }
  
 
  if (mybt.available())
  {
    val_bt = mybt.read();
    Serial.println(val_bt);
    if (val_bt == 100)
    {
      led_blink();
      CAN.beginPacket(0x12);
      CAN.write(0);
      CAN.write(100);

      Serial.println("send can_signal run");
    }
    if (val_bt == 101)
    {
      led_blink();
    }
    if (val_bt == 102)
    {
      led_blink();
    }
  }
}
void led_blink()
{
  digitalWrite(LED_BUILTIN, HIGH);
  delay(100);
  digitalWrite(LED_BUILTIN, LOW);
  delay(100);
}