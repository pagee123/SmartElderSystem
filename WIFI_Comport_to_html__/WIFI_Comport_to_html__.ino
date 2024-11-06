#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <SoftwareSerial.h>
#include <TinyGPS++.h>


TinyGPSPlus  gps;
TinyGPSCustom   effect(gps, "GPRMC", 2);

float latitude  = 0.0;
float longitude  = 0.0;

WiFiServer server(80); // HTTP伺服器物件

#define STASSID "111"
#define STAPSK  "00000000"
const char* ssid = STASSID;
const char* password = STAPSK;


SoftwareSerial mySerial(0,4);


void setup() {
  Serial.begin(115200);
  mySerial.begin(9600);
  WiFi.begin(ssid, password);
  Serial.setTimeout(100);


 while (WiFi.status() != WL_CONNECTED) {
    delay(500);   // 等待WiFi連線
    Serial.print(".");
  }
  
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.print("IP:");
  Serial.println(WiFi.localIP()); 

  // Start the server
  server.begin();
  Serial.println(F("Server started"));
  Serial.println("");
  

}

void loop() {
  
  if(mySerial.available()>0) {//如暫存器有訊號則不斷讀取直到沒有
        gps.encode(mySerial.read());
        if(effect.isUpdated())
        {
            mySerial.println(effect.value());
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
 
    WiFiClient client = server.available();
    client.println("HTTP/1.1 200 OK");
    client.println("Content-Type: text/html");
    client.println("Connection: close");  
    client.println("Refresh: 5");  
    client.println();
  
    client.println("<!DOCTYPE html>");
    client.println("<head>\n<meta charset='UTF-8'>");
    client.println("<title>The smart system of senior citizens</title>");
    client.println("</head>\n<body>");
    client.println("<H2>The smart system of senior citizens</H2>");
    client.println("<H3>Location</H3>");
    client.println("<pre>");
    client.print("the Latitude is: ");
    client.println(latitude,6);
    client.print("the Longitude is: ");
    client.println(longitude,6);
    client.println("</pre>");
    client.print("</body>\n</html>");
      
        
  }
}
