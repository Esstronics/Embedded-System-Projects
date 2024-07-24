#include <TinyGPS++.h>
#include <SoftwareSerial.h>
SoftwareSerial  ss(3,2);
//static const int RXPin = 2, TXPin = 3;
static const uint32_t GPSBaud = 9600;

// The TinyGPS++ object
TinyGPSPlus gps;

// The serial connection to the GPS device
 SoftwareSerial mySerial(3,2);
//SoftwareSerial mySerial(RXPin,TXPin);
#define B 5 //connect to Y of the IC 
#define A 4 //connect  to X of the IC

void setup()
{
  Serial.begin(9600);
  ss.begin(GPSBaud);
   pinMode(A,OUTPUT);     pinMode(B,OUTPUT);

  Serial.println(F("DeviceExample.ino"));
  Serial.println(F("A simple demonstration of TinyGPS++ with an attached GPS module"));
  Serial.print(F("Testing TinyGPS++ library v. ")); Serial.println(TinyGPSPlus::libraryVersion());
  Serial.println(F("by Mikal Hart"));
  Serial.println();

  
}

void loop()
{
     digitalWrite(A,LOW);     digitalWrite(B,LOW);
  while (ss.available() > 0)
  {
    if (gps.encode(ss.read()))
    {
      displayInfo();
     // Serial.println("sms Mode");
  }
  }
  
}

void displayInfo()
{
  Serial.print(F("Location: ")); 
  if (gps.location.isValid())
  {
    Serial.print(gps.location.lat(),5);
    Serial.print(F(","));
    Serial.print(gps.location.lng(),5);
    Serial.print(" ");
    Serial.print(F("Speed:"));
    Serial.print(gps.speed.kmph());
    delay(1000);
  }
  else
  {
    Serial.print(F("INVALID"));
  }
    
  Serial.print(F("  Date/Time: "));
  if (gps.date.isValid())
  {
    Serial.print(gps.date.month());
    Serial.print(F("/"));
    Serial.print(gps.date.day());
    Serial.print(F("/"));
    Serial.print(gps.date.year());
  }
  else
  {
    Serial.print(F("INVALID"));
  }

  Serial.print(F(" "));
  if (gps.time.isValid())
  {
    if (gps.time.hour() < 10) Serial.print(F("0"));
    Serial.print(gps.time.hour());
    Serial.print(F(":"));
    if (gps.time.minute() < 10) Serial.print(F("0"));
    Serial.print(gps.time.minute());
    Serial.print(F(":"));
    if (gps.time.second() < 10) Serial.print(F("0"));
    Serial.print(gps.time.second());
    Serial.print(F("."));
    if (gps.time.centisecond() < 10) Serial.print(F("0"));
    Serial.print(gps.time.centisecond());
  }
  else
  {
    Serial.print(F("INVALID"));
  }

  Serial.println();
}



void sms(void)
{
  mySerial.println("AT");
updateSerial();
mySerial.println("AT+CMGF=1"); // Configuring TEXT mode
updateSerial();
mySerial.println("AT+CMGS=\"+2349077994397\"");
updateSerial();
mySerial.println("I need Help!!!");
updateSerial();
mySerial.print("Am at a location of ");
updateSerial();
mySerial.print(gps.location.lat(),5);
updateSerial();
mySerial.print(F(","));
updateSerial();
mySerial.print(gps.location.lng(),5);
updateSerial();
mySerial.write(26);
 //Serial.print(gps.location.lat(),5);
  //  Serial.print(F(","));
  //  Serial.print(gps.location.lng(),5);
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


/*void alert(void)
{
  digitalWrite(sound,HIGH);
  delay(100);
  digitalWrite(sound,LOW);
  delay(60);
  digitalWrite(sound,HIGH);
  delay(100);
  digitalWrite(sound,LOW);
  delay(60);
  digitalWrite(sound,HIGH);
  delay(100);
  digitalWrite(sound,LOW);
  delay(60);
}*/
 void locate(void)
 {
  int state;
// state = digitalRead(key);
//  if (state ==HIGH)
  {
   // sms();
  // alert();
  }
  
 }// end of locate function


/*
Commands that we can try also
Serial.println(gps.location.lat()); // Latitude in degrees (double) 
Serial.println(gps.location.lng()); // Longitude in degrees (double) 
Serial.print(gps.location.rawLat().negative ? "-" : "+"); 
Serial.println(gps.location.rawLat().deg); // Raw latitude in whole degrees 
Serial.println(gps.location.rawLat().billionths);// ... and billionths (u16/u32) 
Serial.print(gps.location.rawLng().negative ? "-" : "+"); 
Serial.println(gps.location.rawLng().deg); // Raw longitude in whole degrees 
Serial.println(gps.location.rawLng().billionths);// ... and billionths (u16/u32) 
Serial.println(gps.date.value()); // Raw date in DDMMYY format (u32) S
erial.println(gps.date.year()); // Year (2000+) (u16) 
Serial.println(gps.date.month()); // Month (1-12) (u8) 
Serial.println(gps.date.day()); // Day (1-31) (u8) 
Serial.println(gps.time.value()); // Raw time in HHMMSSCC format (u32) 
Serial.println(gps.time.hour()); // Hour (0-23) (u8) 
Serial.println(gps.time.minute()); // Minute (0-59) (u8) 
Serial.println(gps.time.second()); // Second (0-59) (u8) 
Serial.println(gps.time.centisecond()); // 100ths of a second (0-99) (u8) 
Serial.println(gps.speed.value()); // Raw speed in 100ths of a knot (i32) 
Serial.println(gps.speed.knots()); // Speed in knots (double) 
Serial.println(gps.speed.mph()); // Speed in miles per hour (double) 
Serial.println(gps.speed.mps()); // Speed in meters per second (double) 
Serial.println(gps.speed.kmph()); // Speed in kilometers per hour (double) 
Serial.println(gps.course.value()); // Raw course in 100ths of a degree (i32) 
Serial.println(gps.course.deg()); // Course in degrees (double) 
Serial.println(gps.altitude.value()); // Raw altitude in centimeters (i32) 
Serial.println(gps.altitude.meters()); // Altitude in meters (double) 
Serial.println(gps.altitude.miles()); // Altitude in miles (double) 
Serial.println(gps.altitude.kilometers()); // Altitude in kilometers (double)
Serial.println(gps.altitude.feet()); // Altitude in feet (double) 
Serial.println(gps.satellites.value()); // Number of satellites in use (u32) 
Serial.println(gps.hdop.value()); // Horizontal Dim. of Precision (100ths-i32)
Chat Conversation End
*/
