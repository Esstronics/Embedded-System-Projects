#include <SPI.h>
#include <Adafruit_PCD8544.h>

#include <Adafruit_GFX.h>
int volt =  A0;
double voltReading;
double voltage;
double Vthresold = 324;




Adafruit_PCD8544 lcd = Adafruit_PCD8544(12,11,10,9,8);


void welcome(void)
{

lcd.setTextSize(1);
lcd.setTextColor(BLACK);
lcd.setCursor(0,1);
lcd.println();
lcd.println("   WIRELESS");
lcd.println();
lcd.println("   CHARGER");
lcd.display();
delay(2000);
lcd.clearDisplay();

}


void setup() {
  
 pinMode(volt,INPUT);
lcd.begin();
lcd.setContrast(40);
delay(1000);
lcd.clearDisplay();
welcome();

}

void loop() {

VOLTAGE();

}

void VOLTAGE (void)
{
   
  voltReading = analogRead(volt);
  voltage = voltReading * 8 / Vthresold;
  Serial.println(voltReading);
  Serial.println(voltage);
  if ((voltage >= 4.85) && (voltage <= 5.16))
  {
lcd.setTextSize(1);
lcd.setTextColor(BLACK);
lcd.setCursor(0,0);
lcd.print("Voltage= ");
lcd.println(voltage);
lcd.println();
lcd.println("  Device Not");
lcd.print("   Charging");
lcd.display();
delay(200);
lcd.clearDisplay();
    
  }
  else if ((voltage >= 5.20) && (voltage <= 6.00))
  {
lcd.setTextSize(1);
lcd.setTextColor(BLACK);
lcd.setCursor(0,0);
lcd.print("Voltage= ");
lcd.println(voltage);
lcd.println();
lcd.print(" Charging."); 
lcd.display();
delay(200);
lcd.clearDisplay();
lcd.setCursor(0,0);
lcd.print("Voltage= ");
lcd.println(voltage);
lcd.println();
lcd.print(" Charging."); delay(100);
lcd.print(".");  delay(200); 
lcd.print(".");  delay(200);
lcd.display();
delay(200);
lcd.clearDisplay();
  }
  delay(500);
}
