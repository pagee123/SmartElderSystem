#include <TinyGPS++.h>
#include <SoftwareSerial.h>
SoftwareSerial a(2,3);

TinyGPSPlus gps;

void setup() {
  // put your setup code here, to run once:
    Serial.begin(9600);
    a.begin(9600);
    Serial.println("ready");
}

void loop() {
  // put your main code here, to run repeatedly:
  while(a.available()){
    gps.encode(a.read());
    if(gps.location.isUpdated()){
      float longitude=(gps.location.lng()*1000000);
      float latitude=(gps.location.lat()*1000000);
      float distance=sqrt(sq(longitude-120000000)+sq(latitude-23000000));
      Serial.println(longitude);
      Serial.println(latitude);
      Serial.println(distance);
      Serial.println();
    }
  }
}
