 //IoT Based Home Automation by: Bello Abeeb Akorede (Akotronics)
#include <ESP8266WiFi.h>
String  i;
WiFiServer server(80);
////////Contactless Code//////////////////////////////////////
#include <Wire.h>
#include <LiquidCrystal.h>
LiquidCrystal lcd(16,0,12,2,5,4);
#include "DHT.h"
WiFiClient client;

#define DHTPIN 15  
DHT dht2(15,DHT11);
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);
float  t;              float h; 
/////////buzzer////////////////
//int buzzerPin = 1;
float gasLevel = A0;

void temperatureTracking(void){
  t = dht.readTemperature();
  h = dht.readHumidity();
  Serial.println(t);
  Serial.println(h);
}
void welcome()
 {
  lcd.begin(16,2);        lcd.clear();        lcd.print("IoT Based");        lcd.setCursor(0,1);       lcd.print("Home Automation");        delay(2000);        lcd.clear();        delay(200);
  lcd.print("Constructed By: ");            delay(2000);                          lcd.clear();
  ////////////////////////////////////////////////////////////////Adewoyin Adeola 
  lcd.print("Alabi Muhammed");             delay(1000);                          lcd.setCursor(0,1);       lcd.print("2015/1/54458EE"); delay(1000);         lcd.clear();
  //////////////////////////////////////////////////////////////////
  lcd.print("Supervised By:");             delay(1000);                           lcd.setCursor(0,1);      lcd.print("Dr. Henry O.");  delay(1000);         lcd.clear();     lcd.clear();
  ///////////////////////////////////////////////////////////////////////
  
 }


void setup() {
   i = "";                                  delay(10);                            Serial.begin(9600);      welcome();
   pinMode(13, OUTPUT);                     pinMode(14, OUTPUT);                  //pinMode (15, INPUT);   //Configuring PIR Sensor 
//pinMode (buzzerPin, OUTPUT);  //configuring Buzzer Pin 
//digitalWrite (buzzerPin, LOW); 
digitalWrite(13,LOW);                       digitalWrite(14,LOW);                 //digitalWrite (buzzerPin , LOW);
  t=0;                                      h=0;                                  pinMode(gasLevel, INPUT);
WiFi.disconnect();
  Serial.println("Start");
  WiFi.begin("mujaahid","mujaahid");
  while ((!(WiFi.status() == WL_CONNECTED))){
  delay(300);
  Serial.print("...");

  }
  Serial.println("Connected");
  Serial.println((WiFi.localIP().toString()));
  server.begin();
}

void loop() {
  temperatureTracking();          delay (500);                    lcd.clear();         lcd.print("Temp=");             lcd.print(t);                   lcd.print("*C");        lcd.print(" ");     delay (500);
   lcd.setCursor(0,1);
   lcd.print ("Humidity=");       lcd.print (h);                  lcd.print("%");       lcd.print (" ");    delay (500);
  float gasFlow = analogRead(gasLevel);                           
  float gasAverage = gasFlow/1024;
  float gasPercentage = gasAverage * 100; 
 Serial.print("Akotronics Formula");      
    Serial.print("Gas Flow : ");Serial.println(gasFlow);         
  Serial.print("Gas Average : ");Serial.println(gasAverage);         
  Serial.print("Gas Percentage: ");Serial.println(gasPercentage); 
    if (t>=40)
   {
    lcd.clear();       lcd.setCursor(3,0);       lcd.print("Weather is");    lcd.setCursor(4,1);      lcd.print("too Hot");     delay(400);
    
   }
   else
   {
    lcd.clear();              lcd.print("Temp=");          lcd.print (t);       lcd.print("*C");      lcd.print(" ");       lcd.setCursor(0,1);
    lcd.print ("Humidity=");  lcd.print (h);              lcd.print("%");      lcd.print (" ");       delay (500);
   }
   delay(500);
    WiFiClient client = server.available();
    if (!client) { return; }
    while(!client.available()){  delay(1); }
    i = (client.readStringUntil('\r'));
    i.remove(0, 5);
    i.remove(i.length()-9,9);
    if (i == "Relay1On") {
      digitalWrite(13,LOW);
      client.println("HTTP/1.1 200 OK");
      client.println("Content-Type: text/html");
      client.println("");
      client.println("<!DOCTYPE HTML>");
      client.println("<html>");
      client.println("Relay1 is On");
      client.println("</html>");

      delay(1);

    }
    if (i == "Relay1Off") {
      digitalWrite(13,HIGH);
      client.println("HTTP/1.1 200 OK");
      client.println("Content-Type: text/html");
      client.println("");
      client.println("<!DOCTYPE HTML>");
      client.println("<html>");
      client.println("Relay1 is Off");
      client.println("</html>");
      

      delay(1);

    }
    if (i == "Relay2On") {
      digitalWrite(14,LOW);
      client.println("HTTP/1.1 200 OK");
      client.println("Content-Type: text/html");
      client.println("");
      client.println("<!DOCTYPE HTML>");
      client.println("<html>");
      client.println("Relay2 is On");
      client.println("</html>");

      delay(1);

    }
    if (i == "Relay2Off") {
      digitalWrite(14,HIGH);
      client.println("HTTP/1.1 200 OK");
      client.println("Content-Type: text/html");
      client.println("");
      client.println("<!DOCTYPE HTML>");
      client.println("<html>");
      client.println("Relay2 is Off");
      client.println("</html>");

      delay(1);

    }
     if (i == "Temperature") {
      
      client.println("HTTP/1.1 200 OK");
      client.println("Content-Type: text/html");
      client.println("");
      client.println("<!DOCTYPE HTML>");
      client.println("<html>");
      client.println(t);
      client.println("</html>");

      delay(1);

    }
     if (i == "Humidity") {
      
      client.println("HTTP/1.1 200 OK");
      client.println("Content-Type: text/html");
      client.println("");
      client.println("<!DOCTYPE HTML>");
      client.println("<html>");
      client.println(h);
      client.println("</html>");

      delay(1);

    }
    if (i == "GasLevel") {
      
      client.println("HTTP/1.1 200 OK");
      client.println("Content-Type: text/html");
      client.println("");
      client.println("<!DOCTYPE HTML>");
      client.println("<html>");
      client.println(gasPercentage);
      client.println("</html>");

      delay(1);

    }
    if (gasPercentage>=50)
   {
    lcd.clear();        lcd.print("Gas Detected");     delay(400);            
    //digitalWrite (buzzer, HIGH);
    
   }
   else
   {
    lcd.clear();              lcd.print("Temp=");          lcd.print (t);       lcd.print("*C");      lcd.print(" ");       lcd.setCursor(0,1);
    lcd.print ("Humidity=");  lcd.print (h);              lcd.print("%");      lcd.print (" ");       delay (500);
   } 
  


}
