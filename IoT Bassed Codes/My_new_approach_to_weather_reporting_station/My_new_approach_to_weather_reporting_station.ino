/////////////////////////////////
// Weather Reporting System By Akotronics   //
/////////////////////////////////
#include <ESP8266WiFi.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
#define lightSensor A0
#define Rain 14;
#define SEALEVELPRESSURE_HPA (1013.25)
Adafruit_BME280 bme;                    float temperature, humidity, pressure, altitudeValue , rainfall ;
//int lightPin = A0; 
  float lightValue; 
  float lightPercentage;
  float lightAverage; 
 ////////////////////thingspeak///////////////////////////
  #include <ESP8266HTTPClient.h>

WiFiClient client;

String thingSpeakAddress= "http://api.thingspeak.com/update?";
String writeAPIKey;
String tsfield1Name;
String request_string;

HTTPClient http;
 ////////////////////////////////////////////////////////
  
double dewPoint;
WiFiServer server(80);
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
Serial.begin(9600);            Wire.begin();     bme.begin(0x76);    pinMode (lightSensor, INPUT);   
pinMode(14, INPUT);
pinMode(13, OUTPUT);
WiFi.disconnect();
  delay(3000);
  Serial.println("START");
   WiFi.begin("Akotronics","akoredebello94");
  while ((!(WiFi.status() == WL_CONNECTED))){
    delay(300);
    Serial.print("..");

  }
  Serial.println("Connected!!!");
  Serial.println("Your IP is");
  Serial.println((WiFi.localIP().toString()));
  server.begin();
 checkBme();  
}


void loop()
{   
  temperature = bme.readTemperature();
  pressure = bme.readPressure() / 100.0F;
  altitudeValue = bme.readAltitude(SEALEVELPRESSURE_HPA);
  humidity = bme.readHumidity();
  lightValue= analogRead(lightSensor);
  lightAverage = lightValue / 1024; 
  //percentValue= ((lightValue-110)/(1023-110))*100;
  lightPercentage = lightAverage * 100 ; 
  dewPoint = dewPointFast(temperature, humidity);
  Serial.println(temperature);
  Serial.println (pressure);
  Serial.println(altitudeValue);
  Serial.println (dewPoint);
  Serial.println(humidity);
  Serial.println (lightPercentage);
    WiFiClient client = server.available();
    if (!client) { return; }
    while(!client.available()){  delay(1); }
    client.println("HTTP/1.1 200 OK");
    client.println("Content-Type: text/html");
    client.println("");
    client.println("<!DOCTYPE HTML>");
    client.println("<html>");
    client.println("<head>");
      client.println("<h3 style=""color:#ff0000"">");
      client.println("IoT Based Weather Reporting Station");
      client.println("</h3>");
    client.println("</head>");
    client.println("<body>");
    client.println("<!DOCTYPE HTML>");
      client.println("<html>");
      client.println("Light Percentage:");
      client.println("</html>");

      delay(1);
      client.println("<span style=""color:#ff6600;font-size:24px"">");
      client.println(lightPercentage);
      client.println("</span>");
      client.println("<br>");
      client.println("<html>");
      client.println("Temperature in Degree Celsius:");
      client.println("</html>");

      delay(1);
      client.println("<span style=""color:#ff6600;font-size:24px"">");
      client.println((bme.readTemperature()));
      client.println("</span>");
      client.println("<br>");
      client.println("<html>");
      client.println("Humidity:");
      client.println("</html>");

      delay(1);
      client.println("<span style=""color:#ff6600;font-size:24px"">");
      client.println((bme.readHumidity()));
      client.println("</span>");
      client.println("<br>");
      client.println("<html>");
      client.println("Pressure in Pascal:");
      client.println("</html>");

      delay(1);
      client.println("<span style=""color:#ff0000;font-size:24px"">");
      client.println(((bme.readPressure() / 100.0F)));
      client.println("</span>");
      client.println("<br>");
      client.println("<html>");
      client.println("Altitude in meter:");
      client.println("</html>");

      delay(1);
      client.println("<span style=""color:#ff0000;font-size:24px"">");
      client.println((bme.readAltitude(SEALEVELPRESSURE_HPA)));
      client.println("</span>");
      client.println("<br>");
      client.println("<html>");
      client.println("Rain:");
      client.println("</html>");

      delay(1);
      client.println("<span style=""color:#ff0000;font-size:24px"">");
      client.println(digitalRead(14));
      client.println("</span>");
      client.println("<br>");
      client.println("Dew Point:");
      client.println("</html>");

     delay(1);
     client.println("<span style=""color:#ff0000;font-size:24px"">");
     client.println(dewPoint);
     client.println("</span>");
     client.println("<br>");
     client.println("</html>");
      delay(1);
    if (digitalRead(14) == 0) {
      digitalWrite(13,HIGH);
      delay(1);
     client.println("<span style=""color:#ff0000;font-size:24px"">");
     client.println("Oops, It is raining");
     client.println("</span>");
     client.println("<br>");
     client.println("</html>");
      
    }
    else {
       delay(1);
       digitalWrite (13,LOW);
     client.println("<span style=""color:#ff0000;font-size:24px"">");
     client.println("No Rain");
     client.println("</span>");
     client.println("<br>");
     client.println("</html>");
      
    }
  thingspeakStuff();
  //delay(5000);

}
double dewPointFast(double celsius, double humidity)
{
  double a = 17.271;
  double b = 237.7;
  double temp = (a * celsius) / (b + celsius) + log(humidity * 0.01);
  double Td = (b * temp) / (a - temp);
  return Td;
}
void thingspeakStuff (void){
   if (client.connect("api.thingspeak.com",80)) {
      request_string = thingSpeakAddress;
      request_string += "key=";
      request_string += "W2NG4PWO51VZMDHN";
      request_string += "&";
      request_string += "field1";
      request_string += "=";
      request_string += (bme.readTemperature());
      http.begin(request_string);
      http.GET();
      http.end();

    }
    delay(1500);
    if (client.connect("api.thingspeak.com",80)) {
      request_string = thingSpeakAddress;
      request_string += "key=";
      request_string += "W2NG4PWO51VZMDHN";
      request_string += "&";
      request_string += "field2";
      request_string += "=";
      request_string += (bme.readHumidity());
      http.begin(request_string);
      http.GET();
      http.end();

    }
    delay(1500);
    if (client.connect("api.thingspeak.com",80)) {
      request_string = thingSpeakAddress;
      request_string += "key=";
      request_string += "W2NG4PWO51VZMDHN";
      request_string += "&";
      request_string += "field3";
      request_string += "=";
      request_string += ((bme.readPressure() / 100.0F));
      http.begin(request_string);
      http.GET();
      http.end();

    }
    delay(1500);
    if (client.connect("api.thingspeak.com",80)) {
      request_string = thingSpeakAddress;
      request_string += "key=";
      request_string += "W2NG4PWO51VZMDHN";
      request_string += "&";
      request_string += "field4";
      request_string += "=";
      request_string += (bme.readAltitude(SEALEVELPRESSURE_HPA));
      http.begin(request_string);
      http.GET();
      http.end();

    }
    delay(3000);
    if (client.connect("api.thingspeak.com",80)) {
      request_string = thingSpeakAddress;
      request_string += "key=";
      request_string += "W2NG4PWO51VZMDHN";
      request_string += "&";
      request_string += "field5";
      request_string += "=";
      request_string += (lightPercentage);
      http.begin(request_string);
      http.GET();
      http.end();

    }
    delay(1500);
    if (client.connect("api.thingspeak.com",80)) {
      request_string = thingSpeakAddress;
      request_string += "key=";
      request_string += "W2NG4PWO51VZMDHN";
      request_string += "&";
      request_string += "field6";
      request_string += "=";
      request_string += (dewPoint);
      http.begin(request_string);
      http.GET();
      http.end();

    }
    //delay(3000);
    if (client.connect("api.thingspeak.com",80)) {
      request_string = thingSpeakAddress;
      request_string += "key=";
      request_string += "W2NG4PWO51VZMDHN";
      request_string += "&";
      request_string += "field7";
      request_string += "=";
      request_string += (lightValue);
      http.begin(request_string);
      http.GET();
      http.end();

    }
    delay(1500);
    if (client.connect("api.thingspeak.com",80)) {
      request_string = thingSpeakAddress;
      request_string += "key=";
      request_string += "W2NG4PWO51VZMDHN";
      request_string += "&";
      request_string += "field8";
      request_string += "=";
      request_string += "";
      http.begin(request_string);
      http.GET();
      http.end();

    }
    delay(3000);

}
