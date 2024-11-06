int f;
void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
Serial.println("ready");
}

void loop() {
  // put your main code here, to run repeatedly:
  if(Serial.available()){
      char a=Serial.read();
      int b=(a-48)*1000;
      a=Serial.read();
      int c=(a-48)*100;
      a=Serial.read();
      int d=(a-48)*10;
      a=Serial.read();
      int e=(a-48);
      f=b+c+d+e;
      Serial.println(f);
    }
  }
