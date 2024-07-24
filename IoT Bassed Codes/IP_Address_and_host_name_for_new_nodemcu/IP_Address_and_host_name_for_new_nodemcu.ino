/////////////////////////////////
// choosing your IP Address     //
/////////////////////////////////
#include <ESP8266WiFi.h>

IPAddress staticIP265_100(192,168,43,185);
IPAddress gateway265_100(192,168,43,1);
IPAddress subnet265_100(255,255,255,0);


void setup()
{
  Serial.begin(9600);
  delay(3000);
  WiFi.disconnect();
  Serial.println("Start");
   WiFi.begin("Abdullateef");
  while ((!(WiFi.status() == WL_CONNECTED))){
    delay(300);
    Serial.print("...");

  }
  Serial.println("Connected");
  WiFi.config(staticIP265_100, gateway265_100, subnet265_100);
  WiFi.hostname("Abdullateef") ;
  delay(3000);
  Serial.println("Your IP Address is:");
  Serial.println((WiFi.localIP().toString()));
  Serial.println("Your GatewayIP is:");
  Serial.println((WiFi.gatewayIP().toString().c_str()));
  Serial.println("Your Host name is:");
  Serial.println((WiFi.hostname()));

}


void loop()
{


}
