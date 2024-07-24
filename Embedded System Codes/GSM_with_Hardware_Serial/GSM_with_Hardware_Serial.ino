#include <TinyGPS++.h>
#include <SoftwareSerial.h>
SoftwareSerial ss(3,2);

TinyGPSPlus gps;

void setup() {
 Serial.begin(9600);
 ss.begin(9600);
 
 Serial.println("GPS Start");
// mm.begin(4800);
}

void loop() {
  while(ss.available())
  {
    gps.encode(ss.read());
  }
  if (gps.location.isUpdated());
  {
    Serial.begin(9600);
    Serial.println("\r");
   delay(100);
   Serial.println("AT+CMGF=1\r");
   delay(100);
   Serial.println("AT+CMGS=\"+2349077994397\"\r");
   delay(100);
   Serial.println("Now,it is working with Hardware Serial");
   Serial.print("lat:");  Serial.print(gps.location.lat(),6);
   Serial.print("      lng:"); Serial.println(gps.location.lng(),6);
   delay(1);
   Serial.println((char)26);
   delay(100);
   Serial.write(0x1A);
   Serial.write(0x0D);
   Serial.write(0x0A);
   delay(100);

  }
 
}
