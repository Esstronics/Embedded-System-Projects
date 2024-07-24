#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

Adafruit_SSD1306 oled(128,64, &Wire, -1);

int ldrPin = A0;
int vrbPin = A1;
int flamePin = 5;
int vrb;
int flame;
int ldr;
void setup() {
 if (!oled.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    while (true);
    
  }
  
  pinMode (flamePin, INPUT);
  pinMode(ldrPin,INPUT);
  Serial.begin(9600);
}

void loop() {
  ldr = analogRead(ldrPin);
  flame = digitalRead(flamePin);
  vrb = analogRead(vrbPin);
  Serial.println("VOLTAGE; ");       Serial.println(ldr);     Serial.println("    ");
//  Serial.println("FLAME: ");     Serial.println(flame);         Serial.println("     ");
//  Serial.println("RESISTOR: ");   Serial.println(vrb);  Serial.println("    ");

   oled.clearDisplay();
    oled.setCursor(0,0);
    oled.setTextSize(2);
    oled.setTextColor(WHITE); 
   oled.println("  Voltage");  oled.print("   ");
    oled.print(ldr);  oled.println("v");
    oled.println("Device not");
    oled.println(" Charging");
    oled.display();
    
}
