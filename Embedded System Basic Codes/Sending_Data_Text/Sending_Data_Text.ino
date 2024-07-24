#include <Wire.h>
#include <HTTPClient.h>
#include <WiFiClient.h>
#include <SPI.h>
#include <WiFi.h>

int id= 2;   //id of each device, to be changed for every device
String url= "http://marvelous-acadia-34986.herokuapp.com/api/distance/";   //url for all devices
String urlwithid= url + id + "/";    //url for a single device instance
String Data;   //sensor data to be sent to the server


void setup()
{
  Serial.begin(9600); //starting serial for debugging
  Wire.begin();      
  //Connect esp8266 to wifi LAN
 WiFi.begin("esstronics", "immanuel");
 while ((!(WiFi.status() == WL_CONNECTED))){
    delay(300);
    Serial.print("...");

  }
  Serial.println("Connected");
  Serial.println("Your IP Address is:");
  Serial.println((WiFi.localIP().toString()));
 Data= "{\"id\":" + String(id) + "}"; 
  
  //Check connection status to the wifi LAN
  while(WiFi.status() != WL_CONNECTED){delay(500);}

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

     //Sensor data to be sent to the server in JSON format
     Data= "{\"id\":" + String(id) + "6.83563,9.555735" + "}";

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
