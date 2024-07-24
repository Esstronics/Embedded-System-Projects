
#include <TinyGPS++.h>
#define mySerial Serial2
TinyGPSPlus gps;
float latitude , longitude;
String lat_str , lng_str;

void setup() {
  Serial.begin(9600);
  mySerial.begin(9600);
  

}

void loop() {
 while (mySerial.available() > 0) //while data is available
    if (gps.encode(mySerial.read())) //read gps data
    {
      if (gps.location.isValid()) //check whether gps location is valid
      {
        latitude = gps.location.lat();
        lat_str = String(latitude , 6); // latitude location is stored in a string
        longitude = gps.location.lng();
        lng_str = String(longitude , 6); //longitude location is stored in a string
        Serial.print("Latitude: ");
        Serial.print (lat_str);
        Serial.print("    ");
        Serial.print("Longitude:");
        Serial.println (lng_str);
        delay(400);
      }
    
    }

}

void updateSerial()
{
  delay(500);
  while (Serial.available()) 
  {
    mySerial.write(Serial.read());//Forward what Serial received to Software Serial Port
  }
  while(mySerial.available()) 
  {
    Serial.write(mySerial.read());//Forward what Software Serial received to Serial Port
  }
}
