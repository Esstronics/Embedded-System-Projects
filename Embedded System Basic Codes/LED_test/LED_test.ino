#include <LiquidCrystal.h>
LiquidCrystal lcd(12,11,10,9,8,7,6);
int led = 13;

void setup() {
  // put your setup code here, to run once:
pinMode(led,OUTPUT);
lcd.begin(16,2);
lcd.clear();   delay(200);
lcd.print("HEllo World!");
delay(1000);
}

void loop() {
  // put your main code here, to run repeatedly:
digitalWrite(led,HIGH);
delay(1000);
digitalWrite(led,LOW);
delay(600);

}
