/////////////////////////////////
// Running a web server over an access point       //
/////////////////////////////////
#include <ESP8266WiFi.h>

String  Request;
WiFiServer server(80);

void setup()
{
  Request = "";

Serial.begin(9600);
pinMode(2, OUTPUT);
  delay(3000);
  Serial.println("Start");
  WiFi.softAP("Akobell");
  Serial.println((WiFi.softAPIP()));
  server.begin();

}


void loop()
{

    WiFiClient client = server.available();
    if (!client) { return; }
    while(!client.available()){  delay(1); }
    Request = (client.readStringUntil('\r'));
    client.println("HTTP/1.1 200 OK");
    client.println("Content-Type: text/html");
    client.println("");
    client.println("<!DOCTYPE HTML>");
    client.println("<html>");
    client.println((millis()/1000));
    client.println("</html>");

    delay(1);
    Request.remove(0, 5);
    Request.remove(Request.length()-9,9);
    if (Request == "ON") {
      Serial.println("ON");
      digitalWrite(2,HIGH);
      client.println("LED IS ON!");

    }
    if (Request == "OFF") {
      Serial.println("OFF");
      digitalWrite(2,LOW);
      client.println("LED IS OFF");
    }
    client.flush();

}
