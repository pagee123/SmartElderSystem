#include <TinyGPS++.h>
#include <SoftwareSerial.h>
SoftwareSerial LORA_GPS(10,13);


TinyGPSPlus  gps_old;
TinyGPSPlus  gps_home;

uint8_t data;
static uint8_t receive[3];
uint16_t finial;
int LORA_DATA;
int buzzerPin=9;
float distance=0;
float longitude_old,lattitude_old,longitude,lattitude;
float lattitude_home;
float longitude_home;

#include <LiquidCrystal.h>
// 建立 LiquidCrystal 的變數 lcd
//                 LCD 接腳:  rs, enable, d4, d5, d6, d7  
LiquidCrystal lcd(11, 12, 4, 5, 6, 7);

byte p5[8] = {
                0x1F,
                0x1F,
                0x1F,
                0x1F,
                0x1F,
                0x1F,
                0x1F,
                0x1F};


void setup() {
  Serial3.begin(9600);
  Serial2.begin(9600);
  Serial1.begin(115200);
  Serial.begin(9600);
  pinMode(2,INPUT);
  LORA_GPS.begin(9600);
  pinMode(buzzerPin, OUTPUT);
  
  // 設定 LCD 的行列數目 (2 x 16)
  lcd.begin(16, 2);
  lcd.createChar(1, p5);
}
  
void loop()
{
  //gps
  if(digitalRead(2)==LOW){
    //Serial.println(Serial2.available());
      if (Serial2.available()>0 && Serial3.available()>0)
      {
       LORA_DATA=Serial2.read();
       LORA_GPS.write(LORA_DATA);
       gps_old.encode(LORA_DATA);
       gps_home.encode(Serial3.read());
       if(gps_old.location.isUpdated() || gps_home.location.isUpdated()){
         longitude_old=(gps_old.location.lng())*0.022;
         lattitude_old=(gps_old.location.lat())*0.022;
         longitude_home=(gps_home.location.lng())*0.022;
         lattitude_home=(gps_home.location.lat())*0.022;
         longitude=(longitude_old-longitude_home);
         lattitude=(lattitude_old-lattitude_home);
         distance=2*asin(sqrt(sq(sin(lattitude/2))+cos(lattitude_old)*cos(lattitude_home)*sq(sin(longitude/2))))*6378.137;
       }
        lcd.setCursor(0, 0);
        lcd.print("Distance:");
        lcd.setCursor(9, 0);
        lcd.print(distance,3);
        lcd.setCursor(14, 0);
        lcd.print("km");
       if(distance>0.1){
        lcd.setCursor(4, 1);
        lcd.print("Warning!!");
        ambulenceSiren(buzzerPin);
         }else{
        lcd.setCursor(4, 1);
        lcd.print("            ");
         }
      }
  }
  //emg
  if(digitalRead(2)==HIGH){
    Serial1.write((byte)0x20);
    if(Serial1.available())
    {
      data=Serial1.read();
      if(data==0xf0){
        delay(5);
        data=Serial1.read();
        receive[1]=data & 0x0f;
        data=Serial1.read();
        receive[2]=data;
        finial=receive[1];
        finial<<=8;
        finial |=receive[2];
        Serial.println(finial);
        lcd.clear();
      if(finial>1800){
       lcd.setCursor(0, 0);
       lcd.write(1);
       lcd.write(1);
       if(finial>=1800){
         lcd.setCursor(2, 0);
         lcd.write(1);
         lcd.write(1);
         if(finial>=1850){
           lcd.setCursor(4,0);
           lcd.write(1);
           lcd.write(1);      
           if(finial>=1900){
             lcd.setCursor(6,0);
             lcd.write(1);
             lcd.write(1);      
             if(finial>=1950){
               lcd.setCursor(8,0);
               lcd.write(1);
               lcd.write(1);        
               if(finial>=2000){
                  lcd.setCursor(10,0);
                  lcd.write(1);
                  lcd.write(1);
                  if(finial>=2100){
                    lcd.setCursor(12,0);
                    lcd.write(1);                
                    if(finial>=2200){
                      lcd.setCursor(13,0);
                      lcd.write(1);                
                      if(finial>=2300){
                         lcd.setCursor(14,0);
                         lcd.write(1);
                         if(finial>3500){
                         lcd.setCursor(15,0);
                         lcd.write(1);
                         lcd.clear();
                      }}}}}}}}}}
                      lcd.setCursor(7,1);
                      lcd.print("Power!!!");
      }
    }
    if(Serial1.available()){
      Serial1.write((byte)0x00);
      while(Serial1.available()){
        data=Serial1.read();
      }
    }
  }
}
void ambulenceSiren(int pin) {
  tone(pin, 400);        
  delay(300);
  noTone(pin);
  delay(300);
  tone(pin, 400);        
  delay(300);
  noTone(pin);
  delay(300);
  }
   /*while (pp.available() > 0)
      {
        gps.encode(pp.read());//The encode() method encodes the string in the encoding format specified by encoding.
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
        }*/
  
  
