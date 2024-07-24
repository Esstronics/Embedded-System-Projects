#include <WebServer.h>
#include <WiFi.h>
#include <Wire.h>
#include <DHT.h>

#define DHTPIN 12 
#define DHTTYPE DHT11
// Setting Sensors pins
#define MQ135 26
#define MQ7 25
#define MQ3 33
#define MQ6 32

//const char* ssid     = "Uthman1";
//const char* password = "uthman7890";

// Set web server port number to 80
WiFiServer server(80);

// Variable to store the HTTP request
String header;

// Current time
unsigned long currentTime = millis();
// Previous time
unsigned long previousTime = 0; 
// Define timeout time in milliseconds (example: 2000ms = 2s)
const long timeoutTime = 2000;




int gasValue1,gasValue2, gasValue3, gasValue4;
int AIR_ppm,CO_ppm,alcohol_ppm,LPG_ppm;
float t,h,f;

DHT dht(DHTPIN, DHTTYPE);

// void setup////////////////////

void setup() {
   pinMode(MQ135,INPUT);  pinMode(MQ7,INPUT);  pinMode(MQ3,INPUT);  pinMode(MQ6,INPUT);
   bool status;

  
 Serial.begin(9600);
 dht.begin();


 WiFi.disconnect();
  delay(3000);
  Serial.print("Connecting to ");
 // Serial.println(ssid);
  WiFi.begin("TF","Funso012");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  // Print local IP address and start web server
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  server.begin();
  
}
 
   
void loop() {
  Serial.println();
  Serial.println();
  gasValue4 = analogRead(MQ6)/4;
  gasValue1 = analogRead(MQ135)/4;
  gasValue2 = analogRead(MQ7)/4;
  gasValue3 = analogRead(MQ3)/4;
  AirQuality();
  CO2();
  Alcohol();
  LPG();
  DHTRead();
  webPage();

}

void AirQuality(void)
{
  
   AIR_ppm = (gasValue1 - 220)*500/803;
  Serial.println(gasValue1);
  if (AIR_ppm <=50)
  {
   Serial.println("The Air is Good for your Health");
  }
  else if((AIR_ppm >= 51) && (AIR_ppm <= 100)){
    Serial.println("The Air is Slightly good/Moderate for your Health");
  }
  else if ((AIR_ppm >=  101) &&( AIR_ppm <= 150))
  {
    Serial.println("The Air is Unhealthy/Not Good for Sensitive Groups"); 
  }
  else if ((AIR_ppm >=  151) && (AIR_ppm <= 200))
  {
   Serial.println("The Air is Unhealthy for you");  
  }
  else if ((AIR_ppm >=  201) && (AIR_ppm <= 300))
  {
    Serial.println("The Air is Very Unhealthy for you");
  }
   else if ((AIR_ppm >=  301) && (AIR_ppm <= 500))
  {
    Serial.println("The Air is Harzadous to your Health");
  }
}



void CO2(void)
{
 
    CO_ppm = (gasValue2 - 210)*500/813;
    
   if ((CO_ppm >= 40) && (CO_ppm < 50))
  {
    Serial.println("You have less than 10hours to stay here");
  }
  else if ((CO_ppm >= 50) && (CO_ppm < 70))
  {
    Serial.println("You have less than 8hours to stay here");
  }
  else if ((CO_ppm >= 70) && (CO_ppm < 150))
  {
    Serial.println("You have 1 to 4hours to stay here");
  }
  else if ((CO_ppm >= 150) && (CO_ppm < 400))
  {
     Serial.println("You have 10 to 50 minutes to stay here");
  }
  else if ((CO_ppm >= 400) && (CO_ppm <= 500))
  {
    Serial.println("You have less than 4 to 15 minutes to stay here");
  }
  else if (CO_ppm < 40)
  {
    Serial.println("Healthy percentage of air ");
  }
}

void Alcohol(void)
{
  
    alcohol_ppm = (gasValue3 - 500)*4000/523;
   if ((alcohol_ppm >=1000) && (alcohol_ppm < 3300))
  {
    Serial.println("You can stay here for 8hours");
  }
   else if(alcohol_ppm >= 3300)
   {
    Serial.println("The Air is Harzadrous to your Health");
   }
   else
   {
    Serial.println("Good Environment");
   }
}


void LPG(void)
{
   
   LPG_ppm = (gasValue4 - 300)*2500/723;
   if ((LPG_ppm >= 1000)&& (LPG_ppm < 2000))
  {
    Serial.println("You have less than 8hours to stay here");
  }
  else if (LPG_ppm >= 2000)
  {
    Serial.println("The Air is Harzadrous to your Health");
  }
  else
  {
    Serial.println("Good Evironment");
  }
}



void DHTRead (void)
{
   h = dht.readHumidity();
  // Read temperature as Celsius (the default)
   t = dht.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
   f = dht.readTemperature(true);

  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }

  // Compute heat index in Fahrenheit (the default)
  float hif = dht.computeHeatIndex(f, h);
  // Compute heat index in Celsius (isFahreheit = false)
  float hic = dht.computeHeatIndex(t, h, false);

  Serial.print(F("Humidity: "));
  Serial.print(h);
  Serial.print(F("%  Temperature: "));
  Serial.print(t);
  Serial.print(F("°C "));
}




void webPage(){
  WiFiClient client = server.available();   // Listen for incoming clients
  
  if (client) {                             // If a new client connects,
    currentTime = millis();
    previousTime = currentTime;
    Serial.println("New Client.");          // print a message out in the serial port
    String currentLine = "";                // make a String to hold incoming data from the client
    while (client.connected() && currentTime - previousTime <= timeoutTime) {  // loop while the client's connected
      currentTime = millis();
      if (client.available()) {             // if there's bytes to read from the client,
        char c = client.read();             // read a byte, then
        Serial.write(c);                    // print it out the serial monitor
        header += c;
        if (c == '\n') {                    // if the byte is a newline character
          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0) {
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Connection: close");
            client.println();
            
            // Display the HTML web page
            client.println("<!DOCTYPE html><html>");
            client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
            client.println("<link rel=\"icon\" href=\"data:,\">");
            // CSS to style the table 
            client.println("<style>body { background-image: repeating-circle-gradient(#e66465, #9198e5 20%) ; text-align: center; font-family: \"Trebuchet MS\", Arial;}");
            client.println("table {background-color:#f0ebe1 ;border-collapse: collapse; width:35%; margin-left:auto; margin-right:auto; }");
            client.println("th { padding: 12px; background-color: #0043af; color: white; }");
            client.println("tr { border: 1px solid #ddd; padding: 15px; }");
            client.println("tr:hover { background-color: #f0ebe1; }");
            client.println("td { border: none; padding: 12px; }");
            client.println(".sensor { color:black; font-weight: bold; background-color: #f0ebe1; padding: 1px; }");
 
            // Web Page Heading
            client.println("</style></head><body><h1>IoT Based Air Quality Monitoring System</h1>");
            client.println("</style></head><body><h2>Supervised By Dr. Michael David</h2>");
            client.println("<table><tr><th>MEASUREMENT</th><th>VALUE</th></tr>");
            client.println("<tr><td>Air Quality PPM</td><td><span class=\"sensor\">");
            client.println(AIR_ppm); 
            client.println("<tr><td>LPG PPM</td><td><span class=\"sensor\">");
            client.println(LPG_ppm);      
            client.println("<tr><td>Alcohol PPM</td><td><span class=\"sensor\">");
            client.println(alcohol_ppm);
            client.println("<tr><td>CO PPM</td><td><span class=\"sensor\">");
            client.println(CO_ppm);
            client.println("<tr><td>Temperature</td><td><span class=\"sensor\">");
            client.println(t);
            client.println(" *C</span></td></tr>");
            client.println("<tr><td>Humidity</td><td><span class=\"sensor\">");
            client.println(h);
            client.println(" %</span></td></tr>"); 
            client.println("</body></html>");
            
            // The HTTP response ends with another blank line
            client.println();
            // Break out of the while loop
            break;
          } else { // if you got a newline, then clear currentLine
            currentLine = "";
          }
        } else if (c != '\r') {  // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }
      }
    }
    // Clear the header variable
    header = "";
    // Close the connection
   // client.stop();
    Serial.println("Client disconnected.");
    Serial.println("");
  }
}
