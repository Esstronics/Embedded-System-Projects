/////////////////////////////////
// Making an Access point//connecting PC/Android  to ESP8266      //
/////////////////////////////////
#include <ESP8266WiFi.h>
WiFiServer server(80);


void setup()
{
  Serial.begin(9600);
  Serial.println("Start");
  WiFi.softAP("Liquid Monitoring System", "akobell");
  Serial.println((WiFi.softAPIP()));
  server.begin();

}


void loop()
{

    Serial.println("Connected station:");
    Serial.println((WiFi.softAPgetStationNum()));
    delay(5000);

}
