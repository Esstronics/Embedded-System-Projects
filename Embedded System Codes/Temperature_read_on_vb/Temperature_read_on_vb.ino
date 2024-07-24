
#include "DHT.h"
 
#define DHTPIN 12     // what pin we're connected to
 
//Uncomment whatever the type of sensor we are using. 
#define DHTTYPE DHT11   // DHT 11  dht(DHTPIN, DHTTYPE);
 DHT dht(DHTPIN, DHTTYPE);
 
String TextForSms ;
String humidity = " Humidity: %";
String temperature = "   Temperature";
String sign = " *C";
 
char fromc; // character from computer
 
void setup() {
  Serial.begin(9600); 
 // Serial.println("DHT11 test!");
 
  dht.begin();
}
 
void loop() {

  delay(2000);
   int h = dht.readHumidity();
  // Read temperature as Celsius
  int t = dht.readTemperature();
  // Read temperature as Fahrenheit
  int f = dht.readTemperature(true);
  
  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
 
  int hi = dht.computeHeatIndex(f, h);
 
 
  
   TextForSms = TextForSms + t + "," + h + ","; // sorry comma
Serial.println(TextForSms); 
     TextForSms = ""; 
   delay(1000);   
 
 
 
}
