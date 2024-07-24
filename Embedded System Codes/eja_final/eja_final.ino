//Eja Ice Fleet Management Device 
//GPS MOdule 
//Temperature Sensor
//BMS
#include <Wire.h>
#include <HTTPClient.h>
#include <WiFiClient.h>
#include <SPI.h>
#include <TinyGPS++.h>
//#include <TinyGPSPlus.h>
#include <LiquidCrystal.h>
#include <SoftwareSerial.h>
//#include <ESP8266WiFi.h>
//#include <ESP8266HTTPClient.h>
#include <WiFi.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
////Alarm///////////////
//#define buzzer D7
#define SEALEVELPRESSURE_HPA (1013.25)
Adafruit_BME280 bme;  
LiquidCrystal lcd(19,23,18,17,16,15);
//GPS
static const int RXPin = 27, TXPin = 26;   
static const uint32_t GPSBaud = 9600;    
TinyGPSPlus gps;
SoftwareSerial ss(RXPin, TXPin);


int id= 2;   //id of each device, to be changed for every device
String url= "http://ejaice.herokuapp.com/api/device/";   //url for all devices
String urlwithid= url + id + "/";    //url for a single device instance
String Data;   //sensor data to be sent to the server
float temperature;
float battery;
float latitude;
float longitude;
float voltage;

///Restart if I2C Address for BME is wrong////////////
void checkBme (void)
{
  if (!bme.begin(0x76))
  {
    Serial.println("Could not find a valid BME280 sensor, check wiring!");
    while (1);
  }

}

void Battery(void)
{
  int sensorValue = analogRead(4);
// Convert the analog reading (which goes from 0 - 1023) to a voltage (0 - 50V):
 voltage = sensorValue * (1.0 / 4095.0) * 100;
Serial.print(sensorValue);  Serial.print("  ");
// print out the value you read:
Serial.print("Voltage: ");
Serial.print(voltage);
Serial.println(" %");
delay(100);
}

void setup()
{
  Serial.begin(9600); //starting serial for debugging
  Wire.begin();     bme.begin(0x76);  pinMode (4, OUTPUT); // pinMode(buzzer, OUTPUT);
  lcd.begin(16,2);
   checkBme();
   
  //Connect esp8266 to wifi LAN
 WiFi.begin("Akotronics", "akobell4AI");
 Data= "{\"id\":" + String(id) + "}"; 
  
  //Check connection status to the wifi LAN
  while(WiFi.status() != WL_CONNECTED){delay(500);}

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
     //Get sensors reading into the variables
     //Tracker();
     Battery();
     temperature = bme.readTemperature();
    //longitude= (gps.location.lng(),5);
    Serial.print(gps.location.lat(), 6);
    Serial.print(gps.location.lat(), 6);
    latitude= gps.location.lat();
    longitude=gps.location.lng();
    //longitude= 6;
    //latitude= 8;
     Serial.print("Temperature: ");
     Serial.println(temperature);
     Serial.println (longitude);
     Serial.println(latitude);
     lcd.clear();
     lcd.print("Temp: ");
     lcd.print(temperature); lcd.print("*C");
     delay(1000); 
     lcd.setCursor(0,1);
     lcd.print("BMS: ");
     lcd.print(voltage);  lcd.print("%");
     delay(1000); 
     //Sensor data to be sent to the server in JSON format
     Data= "{\"id\":" + String(id) + "," + "\"temperature\":" + String(temperature) + "," "\"battery\":" + String(battery) + "," "\"long\":" + String(longitude) + "," "\"lat\":" + String(latitude) + "}";

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
  
  }

 void displayInfo()
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

////GPS FUNCTIONS
 void Tracker(void)
 {
   while (ss.available() > 0)
    if (gps.encode(ss.read()))
      displayInfo();

  if (millis() > 5000 && gps.charsProcessed() < 10)
  {
    Serial.println(F("No GPS detected: check wiring."));
    while(true);
  }
 }
