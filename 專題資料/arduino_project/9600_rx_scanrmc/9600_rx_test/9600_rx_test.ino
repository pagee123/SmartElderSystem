

#include <TinyGPS++.h>
#include <SoftwareSerial.h>

TinyGPSPlus gps;
TinyGPSCustom effect(gps, "GPRMC", 2);
float latitude;
float longitude;
int hours;
void setup()
  {
    Serial.begin(9600); //set the baud rate of serial port to 9600;
    
  }

void loop()
  {
    while (Serial.available() > 0)
      {
        gps.encode(Serial.read());//The encode() method encodes the string in the encoding format specified by encoding.
       if(effect.isUpdated())
        {
            Serial.println(effect.value());
        if(gps.location.isUpdated())
          {
            latitude = gps.location.lat(); //gps.location.lat() can export latitude
            longitude = gps.location.lng();//gps.location.lng() can export latitude
            Serial.print("Latitude=");
            Serial.print(latitude, 6);  //Stable after the fifth position
            Serial.print(" Longitude=");
            Serial.println(longitude, 6);
            delay(500);
          }
        }
      }
  }
      
