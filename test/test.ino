#include <TinyGPS++.h>
#include <SoftwareSerial.h>
SoftwareSerial LORA_GPS(10,13);
TinyGPSPlus  gps_old;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  LORA_GPS.begin(9600);
  Serial2.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (Serial2.available()>0)
      {
       char c=Serial2.read();
       Serial.print(c);
      }
}
