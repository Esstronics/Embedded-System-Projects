#include <dht.h>

dht DHT;

#define DHT11_PIN 5

void setup()
{
  Serial.begin(9600);
}

void loop()
{
  float h = DHT.humidity;
   float t = DHT.temperature;
  Serial.print(h, 2);
  Serial.print(",\t");
  Serial.println(t, 1);

  delay(500);
}
//
// END OF FILE
//
