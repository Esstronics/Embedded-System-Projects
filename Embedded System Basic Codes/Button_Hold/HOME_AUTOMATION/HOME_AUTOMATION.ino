int val;
int tempPin = A0;
int ldr = A1;
int val2;
#define bulbRelay 2
#define fanRelay 7
void setup()
{
  Serial.begin(9600);
  pinMode(A1,INPUT);
  pinMode(2,OUTPUT);
  pinMode(7,OUTPUT);
}
void loop()
{
  val2=analogRead(A1);
  int me = val2;
  val = analogRead(A0);
  float mv = ( val/1024.0)*5000;
  float cel = mv/10;
  float farh = (cel*9)/5 + 32;
  Serial.print("TEMPRATURE = ");
  Serial.print(cel);
  Serial.print("*C");
  Serial.println();
  delay(1000);
  /*Serial.print("LDR= ");
  Serial.println(val2);
  delay(1000);*/
  if (val2 <= 100)
  {
   Serial.print("AFTERNOON");
    delay(1000);
    digitalWrite(2,HIGH);
  }
    else if ((me >= 300) && (me <= 500))
  {
    Serial.println("MORNING");
    delay(1000);
    digitalWrite(2,HIGH);
  }
  else if (me >= 600)
  {
    Serial.println("NIGHT");
    delay(1000);
    digitalWrite(2,LOW);
  }
  //.......................................................
  if (cel <= 30)
  {
    digitalWrite(7,HIGH);
  }
  else
  {
    digitalWrite(7,LOW);
  }
/* 
Serial.print("TEMPRATURE = ");
Serial.print(farh);
Serial.print("*F");
Serial.println();
*/
}
