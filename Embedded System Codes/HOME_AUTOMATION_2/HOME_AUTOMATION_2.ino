#include <LiquidCrystal.h>
LiquidCrystal lcd(13,12,11,6,5,4,3);int val;
int tempPin = A0;
int ldr = A1;
int val2;
#define bulbRelay 2
#define fanRelay 7
void setup(){
 pinMode(A1,INPUT);
 pinMode(2,OUTPUT);
 pinMode(7,OUTPUT);
 lcd.begin(16,2);
 lcd.setCursor(1,0);
 lcd.print("HOME AUTOMATION ");
 delay(1000);
 lcd.setCursor(3,1);
 lcd.print("SYSTEM");
 delay(4000);
 lcd.clear();
 delay(300);
 lcd.setCursor(2,0);
 lcd.print("DESIGNED BY");
 delay(1000);
 lcd.setCursor(0,1);
 lcd.print("ADESINA UTHMAN");
 delay(4000); 
 lcd.clear();
 lcd.setCursor(1,0);
 lcd.print("SUPERVISED BY");
 delay(1000);
 lcd.setCursor(3,1);
 lcd.print("AKOTRONICS");
 delay(3000);
 lcd.clear();
 lcd.setCursor(1,0);
 lcd.print("CALIBRATING");
 delay(1000);
 lcd.setCursor(0,1);
 lcd.print("system"); lcd.print("."); delay(400);  lcd.print("."); delay(400); lcd.print("."); delay(400);lcd.clear ();
 delay(4000);

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
  Serial.println(val);
  delay(1000);*/
  if (val2 <= 100)
  {
    lcd.clear();
   lcd.setCursor(3,1);
   lcd.print("AFTERNOON");
    delay(1000);
    digitalWrite(2,HIGH);
  }
    else if ((me >= 300) && (me <= 500))
  {
    lcd.clear();
    lcd.setCursor(3,1);
    lcd.print("MORNING");
    delay(1000);
    digitalWrite(2,HIGH);
  }
  else if (me >= 600)
  {
    lcd.clear();
    lcd.setCursor(5,1);
    lcd.print("NIGHT");
    delay(1000);
    digitalWrite(2,LOW);
  }
  //.......................................................
  if (cel >= 30)
  {
     lcd.clear();
     lcd.setCursor(3,1);
     lcd.print("It's too HOT");
     delay(1000);
    digitalWrite(7,LOW);
  }
  else
  {
    lcd.clear();
    lcd.setCursor(3,1);
    lcd.print("Not Too Hot");
    digitalWrite(7,HIGH);
  }
/* 
Serial.print("TEMPRATURE = ");
Serial.print(farh);
Serial.print("*F");
Serial.println();
*/
}
