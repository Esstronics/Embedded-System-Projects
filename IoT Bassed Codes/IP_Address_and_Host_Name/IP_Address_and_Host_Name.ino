
/////////////////////////////////
//IP and HOST NAME      //
/////////////////////////////////
#include <ESP8266WiFi.h>

void setup()
{
  Serial.begin(9600);
  delay(3000);
  WiFi.disconnect();
  Serial.println("Start");
   WiFi.begin("Esstronics","immanuel");
  while ((!(WiFi.status() == WL_CONNECTED))){
    delay(300);
    Serial.print("...");

  }
  Serial.println("Connected");
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
