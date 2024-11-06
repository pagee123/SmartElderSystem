void setup() {
  // put your setup code here, to run once:
  pinMode(2,INPUT);
  pinMode(5,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  int pin=digitalRead(2);
  if(pin==HIGH){
    digitalWrite(5,LOW);
  }
  if(pin==LOW)
  {
    digitalWrite(5,HIGH);
  }
}
