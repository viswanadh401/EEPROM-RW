#include <EEPROM.h>

String inputString = "";
int data, value = 0;

void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
EEPROM.begin(512);
}

void loop() {
  // put your main code here, to run repeatedly:
if(Serial.available()>0)
{
  char inChar = (char)Serial.read();
  inputString += inChar;
  if(inChar == '\n')
  {
    //Serial.print(inputString);
    eepromwrite(inputString);
    inputString = "";
  }
}
}

void eepromwrite(String x)
{
  int factor = 1,temp,data;
  int i = 1;
  temp = x.toInt();
  //Serial.println(temp);
  data = x.toInt();
  //Serial.println(data);
   while(temp){
      temp=temp/10;
      factor = factor*10;
  }
  while(factor>1){
      factor = factor/10;
      int a = data/factor;
      //Serial.println(a);
      EEPROM.write(i,a);
      EEPROM.commit();
      i++;
      data = data % factor;
  }
    eepromread(1);
}

void eepromread(int x)
{
  for (int i = x;i<9;i++)
{
  value = EEPROM.read(i);
  Serial.print(value, DEC);
  data = data+value;
  data = data*10;
  delay(100);
}
Serial.println();
data = data/10;
Serial.println(data);
}

