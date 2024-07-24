#include <Wire.h>
#include <SPI.h>
#include <MFRC522.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2);
 void welcome(void)
{
   lcd.begin();  lcd.backlight();
   lcd.setCursor(3, 1);    lcd.print("RFID Based");   lcd.setCursor(3, 0);   lcd.print("Door Lock");
  delay(1500);   lcd.clear();  
  lcd.print("Calibrating ");   lcd.setCursor(0,1);   lcd.print("Sensor.");   delay(2000);  lcd.print("."); delay(500);  lcd.print("."); delay(500);
  lcd.print("."); delay(500);
  lcd.clear();   lcd.print("System Ready"); delay(1000);    lcd.print("!"); delay(500);  lcd.print("!"); delay(500);    lcd.print("!"); delay(500);  
  lcd.clear();  delay(100);
}
void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:
welcome();
}
