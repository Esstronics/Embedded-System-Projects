#include <TinyGPS++.h>
#include <SoftwareSerial.h>

TinyGPSPlus gps;
SoftwareSerial  mySerial(3,2);
#define B 5 
#define A 4

float latitude , longitude;
String date_str , time_str , lat_str , lng_str;

void setup() {
   Serial.begin(9600);
   mySerial.begin(9600);
   pinMode(A,OUTPUT);       pinMode(B,OUTPUT); 

}

void loop() {
  
//Location();
  digitalWrite(A,LOW);    digitalWrite(B,LOW);
  mySerial.println("AT"); //Once the handshake test is successful, it will back to OK
  updateSerial();

  mySerial.println("AT+CMGF=1"); // Configuring TEXT mode
  updateSerial();
  mySerial.println("AT+CMGS=\"+2347011473337\"");//You can change the phone number 
  updateSerial();
  mySerial.println("message"); //text content
  updateSerial();
  mySerial.write(26);
  delay(500);

}


void Location(void)
{
   digitalWrite(A,LOW);    digitalWrite(B,LOW);
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
