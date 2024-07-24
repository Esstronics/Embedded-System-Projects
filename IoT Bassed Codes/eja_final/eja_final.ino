//Eja Ice Fleet Management Device 
//GPS MOdule 
//Temperature Sensor
//BMS
#include <Wire.h>
#include <HTTPClient.h>
#include <WiFiClient.h>
#include <SPI.h>
#include <TinyGPS++.h>
#include <LiquidCrystal.h>
#include <SoftwareSerial.h>
//#include <ESP8266WiFi.h>
//#include <ESP8266HTTPClient.h>
//#include <WiFi.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
////Alarm///////////////
#include <TinyGPS++.h> // library for GPS module
#include <SoftwareSerial.h>
TinyGPSPlus gps;  // The TinyGPS++ object
#define SEALEVELPRESSURE_HPA (1013.25)
Adafruit_BME280 bme;  
LiquidCrystal lcd(19,23,18,17,16,15);
//GPS
static const int TXPin = 27, RXPin = 26;   
static const uint32_t GPSBaud = 9600;    
//TinyGPSPlus gps;
SoftwareSerial mySerial(TXPin, RXPin);


int id= 6;   //id of each device, to be changed for every device
String url= "http://ejaice.herokuapp.com/api/device/";   //url for all devices
String urlwithid= url + id + "/";    //url for a single device instance
String Data;   //sensor data to be sent to the server
float temperature;
float latitude;
float longitude;
float sensorValue;
///Restart if I2C Address for BME is wrong////////////
void checkBme (void)
{
  if (!bme.begin(0x76))
  {
    Serial.println("Could not find a valid BME280 sensor, check wiring!");
    while (1);
  }

}


void setup()
{
  
  Serial.begin(9600); //starting serial for debugging
  mySerial.begin(9600);
  Wire.begin();     bme.begin(0x76);  
  lcd.begin(16,2);
  lcd.clear (); 
  lcd.print ("Eja Ice FMS");
  lcd.setCursor (0,1);
  lcd.print ("Initializing"); 
  delay (2000);
  lcd.clear();
  checkBme();
WiFi.begin("EjaIceLtd", "ejaice123");
Data= "{\"id\":" + String(id) + "}";  
  //Check connection status to the wifi LAN
  while(WiFi.status() != WL_CONNECTED)
  {delay(500);}

  //Reconnect esp8266 automatically when connection is lost
  WiFi.setAutoReconnect(true);
  WiFi.persistent(true);

  //Check connection status to the wifi LAN
 if(WiFi.status() == WL_CONNECTED){
     WiFiClient clients;
     HTTPClient http;
     http.begin(clients, urlwithid);
     
     //Geting the instance of the device
     int ResponseCode= http.GET();
     http.end();
     Serial.println(ResponseCode);
     
     //Check if instance of the device is already available, incase the device has been switched off and turned on back or connection lost and reconnected 
     if(ResponseCode == 404){ 
          //instance of the device is not available
          http.begin(clients, url); 
          http.addHeader("Content-type","application/json");
          //Create a new instance of the device
          http.POST(Data);
          http.end();
        }
      //instance is already available continue to updating the instance
      }
    
}

void loop() {
  ///////////////////////Battery Monitoring//////////////////////////////
  temperature = bme.readTemperature();
 Serial.print("Temperature: ");
 Serial.println(temperature);
  float voltage = (float)analogRead(36) / 4096 * 55 * 6382 / 6570;
  int batteryPercentage = (voltage * 100)/ 55;
  Serial.print(voltage,1);
  Serial.println("v");
  Serial.print (batteryPercentage, 1);
  Serial.println ("%");
 

  Serial.println ("..........................");

  if (batteryPercentage >= 97){

    Serial.println ("battery full"); 
    delay (200);
  }
 else if ((batteryPercentage > 90) || (batteryPercentage < 80)){

    Serial.println ("battery at normal stage"); 
    delay (200);
  }

 
 //Serial.println();
 //delay(1000);
 lcd.clear();  lcd.setCursor(0,0);
 lcd.print("Temp: ");
 lcd.print(temperature); lcd.print("*C");
 lcd.setCursor(0,1);
 lcd.print("B: ");
 lcd.print(batteryPercentage);  lcd.print("%");
 delay(100); 
 Data= "{\"id\":" + String(id) + "," + "\"temperature\":" + String(temperature) + "," "\"battery\":" + String(batteryPercentage) + "," "\"long\":" + String(longitude) + "," "\"lat\":" + String(latitude) + "}";

     //Check connection status to the wifi LAN
    if(WiFi.status() == WL_CONNECTED){
       WiFiClient clients;
       HTTPClient http;
       http.begin(clients, urlwithid);
       http.addHeader("Content-type","application/json");

       //Updating the instance of the device every 10secs
       int response= http.PUT(Data);
       Serial.print(response);
       http.end();
      }

     delay(1000);
  
/////////////////////////////////////////////////////////////////////////
while (mySerial.available() > 0) //while data is available
if (gps.encode(mySerial.read())) //read gps data
{
if (gps.location.isValid()) //check whether gps location is valid
      {
     
     
     latitude= gps.location.lat();
     longitude=gps.location.lng();
     Serial.print(gps.location.lat(), 6);   Serial.print("  ");
     Serial.println(gps.location.lng(), 6);

  }
    }
}





 /*void displayInfo()
{
  Serial.print(F("Location: ")); 
 
  if (gps.location.isValid())
  {
    Serial.print(gps.location.lat(),5);
    Serial.print(F(","));
    Serial.print(gps.location.lng(),5);
    delay(1000);
  }
  else
  {
    Serial.print(F("INVALID"));
  }
  

  Serial.println();
}
///////////////////////GPS////////////////////////////////////////
Serial.print(F("Location: ")); 
 
  if (gps.location.isValid())
  {
    Serial.print(gps.location.lat(),5);
    Serial.print(F(","));
    Serial.print(gps.location.lng(),5);
    delay(1000);
  }
  else
  {
    Serial.print(F("INVALID"));
  }
  

  Serial.println();*/
  
