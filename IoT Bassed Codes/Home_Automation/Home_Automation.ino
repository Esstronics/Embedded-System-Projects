/////////////////////////////////
// IoT Based Home Automation By: Bello  Abeeb Akorede
//Features: Display, PIR Motion sensing , Alarm, Android App 
/////////////////////////////////
#include <ESP8266WiFi.h>
String  i;
WiFiServer server(80);
////////Contactless Code//////////////////////////////////////
#include <Wire.h>
#include <Adafruit_MLX90614.h>
Adafruit_MLX90614 mlx = Adafruit_MLX90614();
#include <LiquidCrystal.h>
LiquidCrystal lcd(16,0,12,2,3,1);
/////////buzzer////////////////
//int buzzerPin = 9;
//////////////////////////////

void temperatureTracking(void){
  Serial.print("Ambient = "); Serial.print(mlx.readAmbientTempC()); 
  Serial.print("*C\tObject = "); Serial.print(mlx.readObjectTempC()); Serial.println("*C");
  Serial.print("Ambient = "); Serial.print(mlx.readAmbientTempF()); 
  Serial.print("*F\tObject = "); Serial.print(mlx.readObjectTempF()); Serial.println("*F");
          
}
/////////////////////////////////////////////////////////////////////////////////////////////
void welcome()
 {
  lcd.begin(16,2);        lcd.clear();        lcd.print("IoT Based");        lcd.setCursor(0,1);       lcd.print("Home Automation");        delay(2000);        lcd.clear();        delay(200);
  lcd.print("Constructed By: ");            delay(2000);                          lcd.clear();
  ////////////////////////////////////////////////////////////////Adewoyin Adeola 
  lcd.print("Mariam Sulleiman");             delay(1000);                          lcd.setCursor(0,1);       lcd.print("2015/1/54483EE"); delay(1000);         lcd.clear();
  //////////////////////////////////////////////////////////////////Adedokun Victor
  lcd.print("Supervised By:");             delay(1000);                           lcd.setCursor(0,1);      lcd.print("Prof.Engr Tsado");  delay(1000);         lcd.clear();     lcd.clear();
  ///////////////////////////////////////////////////////////////////////
  
 }
///////////////////////////////////////////////////////////////////////////////////////////////
void setup()
{
  i = "";
delay(10);
Serial.begin(9600);
welcome();
pinMode(13, OUTPUT);     //Configuring relay1
pinMode(14, OUTPUT);    //configuring relay2
//pinMode (15, INPUT);    //Configuring PIR Sensor 
//pinMode (buzzerPin, OUTPUT);  //configuring Buzzer Pin 
//digitalWrite (buzzerPin, LOW); 
digitalWrite(13,LOW);
digitalWrite(14,LOW);
//digitalWrite (buzzerPin , LOW);
  WiFi.disconnect();
  Serial.println("Start");
  WiFi.begin("Msulleiman","@Amiratu2");
  while ((!(WiFi.status() == WL_CONNECTED)))
  {
  delay(300);
  Serial.print("...");

  }
  Serial.println("Connected");
  Serial.println((WiFi.localIP().toString()));
  server.begin();
  mlx.begin();
  
}


void loop()
{
    temperatureTracking();
    /////////////////temperature data on digital display//////////////////
    delay(500);
    lcd.clear();
  //lcd.setCursor (0,1);
  lcd.print("Ambient="); //lcd.setCursor(11,0);
  lcd.print (mlx.readAmbientTempC());
  
   lcd.print("*C");     lcd.print(" "); 
   
   lcd.setCursor(0,1);
   lcd.print ("Object="); lcd.print (mlx.readObjectTempC()); lcd.print("*C");lcd.print (" ");     delay (500);
    if (mlx.readAmbientTempC()>=40)
   {
    lcd.clear();       lcd.setCursor(3,0);       lcd.print("Weather is");    lcd.setCursor(4,1);      lcd.print("too Hot");     delay(400);
    
   }
   else
   {
    lcd.clear();       lcd.print("Ambient=");          lcd.print (mlx.readAmbientTempC());       lcd.print("*C");      lcd.print(" ");       lcd.setCursor(0,1);
    lcd.print ("Object="); lcd.print (mlx.readObjectTempC()); lcd.print("*C");lcd.print (" ");       delay (500);
   }
   
 //Alarm Unit 
if (mlx.readObjectTempC() >= 37 )
{
  lcd.clear();
  delay(200);
  lcd.print("Go for Check up");
  lcd.setCursor(0,1);
  lcd.print("Sign of Covid-19");
  delay(2000);
  
  //digitalWrite(buzzerPin,HIGH);
// delay(1000);
 //digitalWrite(buzzerPin,LOW);
  //delay(1000);
 //digitalWrite(buzzerPin,HIGH);
 // delay(1000);
 // digitalWrite(buzzerPin,LOW);
 // delay(1000);
  // digitalWrite(buzzerPin,HIGH);
 //delay(1000);
 //digitalWrite(buzzerPin,LOW);
//delay(1000);
  
}
 else
   {
    lcd.clear();
    lcd.print("Ambient="); //lcd.setCursor(11,0);
  lcd.print (mlx.readAmbientTempC());
  lcd.print("*C");
   lcd.print(" ");
    lcd.setCursor(0,1);
   lcd.print ("Object="); lcd.print (mlx.readObjectTempC()); lcd.print("*C");lcd.print (" ");
   delay (500);
   }

 

    //////////////////////////////////////////////////////////////////////
     if ((digitalRead(15)==HIGH))
     {
    //digitalWrite (buzzerPin, HIGH);
    //delay(2000);
    Serial.println("Motion Detected");
    lcd.clear();          lcd.print ("Motion Detected");  delay(1500);
  }
  else {
    Serial.println("No Motion detected");
    //digitalWrite (buzzerPin, LOW); 
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
     if (i == "AmbientTemperature") {
      
      client.println("HTTP/1.1 200 OK");
      client.println("Content-Type: text/html");
      client.println("");
      client.println("<!DOCTYPE HTML>");
      client.println("<html>");
      client.println(mlx.readAmbientTempC());
      client.println("</html>");

      delay(1);

    }
     if (i == "ObjectTemperature") {
      
      client.println("HTTP/1.1 200 OK");
      client.println("Content-Type: text/html");
      client.println("");
      client.println("<!DOCTYPE HTML>");
      client.println("<html>");
      client.println(mlx.readObjectTempC());
      client.println("</html>");

      delay(1);

    }
    
    /////////////temperature Condition////////////////////////////
    
}
