#include <DHT.h>

#define DHTPIN 12 
#define DHTTYPE DHT11
// Setting Sensors pins
#define MQ135 2
#define MQ7 4
#define MQ3 15
#define MQ6 14

int gasValue1,gasValue2, gasValue3, gasValue4;
int AIR_ppm,CO_ppm,alcohol_ppm,LPG_ppm;

DHT dht(DHTPIN, DHTTYPE);
void setup() {
 Serial.begin(9600);
 dht.begin();
 pinMode(MQ135,INPUT);  pinMode(MQ7,INPUT);  pinMode(MQ3,INPUT);  pinMode(MQ6,INPUT);
}
 
   
void loop() {
  Serial.println();
  Serial.println();
  AirQuality();
  CO2();
  Alcohol();
  LPG();
  DHTRead();
  delay(1000);

}

void AirQuality(void)
{
  gasValue1 = analogRead(MQ135)/4;
  int AIR_ppm = (gasValue1 - 220)*500/803;
  if ((AIR_ppm >= 50) && (AIR_ppm <=50))
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
    gasValue2 = analogRead(MQ7)/4;
    CO_ppm = (gasValue2 - 210)*500/813;
   if ((CO_ppm >= 40) && (CO_ppm <= 49))
  {
    Serial.println("You have less than 10hours to stay here");
  }
  else if ((CO_ppm >= 50) && (CO_ppm <= 69))
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
    Serial.println("Healthy peercentage of air ");
  }
}

void Alcohol(void)
{
    gasValue3 = analogRead(MQ3)/4;
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
   gasValue4 = analogRead(MQ6)/4;
   LPG_ppm = (gasValue4 - 300)*3000/723;
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
   float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  float f = dht.readTemperature(true);

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
