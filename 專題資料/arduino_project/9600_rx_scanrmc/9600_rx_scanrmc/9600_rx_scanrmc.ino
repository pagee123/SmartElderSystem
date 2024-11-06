
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("Reading GPS");
}
char temp[100];
int incomingByte=0;
int count=0;

void loop() {
  char i;
  // put your main code here, to run repeatedly:
  while(Serial.available())
{
    incomingByte=Serial.read();
    char te=incomingByte;
    temp[count++]=te;
    if(te=='\n')
    {
      String data(temp);
      if(data.indexOf("$GPRMC")!=-1)
      {
        Serial.print(data);
      }
      for(int i=0;i<sizeof(temp);++i)
        temp[i]=(char)0;
      count=0;
    }
  }
}
