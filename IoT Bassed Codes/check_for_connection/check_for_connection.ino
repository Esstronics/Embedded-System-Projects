#include <ESP8266WiFi.h>

void setup()
{
  Serial.begin(9600);
  
  WiFi.disconnect();
  delay(3000);
   WiFi.begin("Uthman","uthman1234");
  while ((!(WiFi.status() == WL_CONNECTED))){
    delay(300);
    Serial.print("...");
  }
  Serial.print("i am connected");

}


void loop()
{


}
