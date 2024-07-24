#include <SPI.h>
#include <Adafruit_PCD8544.h>

#include <Adafruit_GFX.h>
Adafruit_PCD8544 lcd = Adafruit_PCD8544(12,11,10,9,8);


void setup() {
  lcd.begin();
  lcd.setContrast(40);
  delay(1000);
  lcd.clearDisplay();

}

void loop() {
  
lcd.setTextSize(2);
lcd.setTextColor(BLACK);
lcd.setCursor(0,1);
lcd.println(" HELLO");
lcd.println();
lcd.println(" WORLD!");
lcd.display();
delay(2000);
lcd.clearDisplay();
}
