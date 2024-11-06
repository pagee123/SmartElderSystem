void setup() {

  Serial.begin(115200);  //設定通訊速率

}

 

void loop() {
  int i;
  
  if(Serial.available()>0) {   //如果暫存器有訊號則不斷讀取直到沒有
    i=Serial.read();
    Serial.write(i);
  } 

}
