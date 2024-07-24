#include <TinyGPS++.h> // library for GPS module
#include <SoftwareSerial.h>

TinyGPSPlus gps;  // The TinyGPS++ object
SoftwareSerial  mySerial(3,2);
float latitude , longitude;
int year , month , date, hour , minute , second;
String date_str , time_str , lat_str , lng_str;

void setup() {
  Serial.begin(9600);
  mySerial.begin(9600);
  Serial.println("Ready GPS");
  delay(1000);
}


void loop() {
//Latitude: 9.537832,    Longitude:6.473492

    while (mySerial.available() > 0) //while data is available
    {
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
        Serial.print(",");
        Serial.print("Longitude:");
        Serial.println (lng_str);  
       // Serial.println();
        //delay(1000);
      }
    }
}
  }
