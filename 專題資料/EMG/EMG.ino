
uint8_t data;
static uint8_t receive[3];
uint16_t finial;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial1.begin(115200);
  pinMode(13,OUTPUT);
  Serial.println("Ready");
}

void loop() {
  // put your main code here, to run repeatedly:

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
      if(finial>2000){
        digitalWrite(13,HIGH);
      }else{
        digitalWrite(13,LOW);
      }
    }
  }
  if(Serial1.available()){
    Serial1.write((byte)0x00);
    while(Serial1.available()){
      data=Serial1.read();
    }
  }
}
