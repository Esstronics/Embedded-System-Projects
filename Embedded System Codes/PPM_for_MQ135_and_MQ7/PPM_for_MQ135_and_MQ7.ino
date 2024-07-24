#include <DHT.h>

#define DHTPIN 12 

#define DHTTYPE DHT11
int airQuality_sensor = 2; //Sensor pin 
int  CO = 4;
int alcohol = 15;
int LPG = 14;
int buzzer = 27;
float m = -0.3376; //Slope 
float b = 0.7165; //Y-Intercept 
float R0 = 3.12; //Sensor Resistance in fresh air from previous code
float AIR_volt; //Define variable for sensor voltage 
float RS_gas1;
float CO_volt;
float alcohol_volt;
  float LPG_volt; 
  float RS_gas2;
  float RS_gas3;
  float RS_gas4;
  float ratio1; //Define variable for ratio
  float ratio2;
  float ratio3;
  float ratio4;
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600); //Baud rate 
  pinMode(buzzer,OUTPUT);
  pinMode(CO,INPUT); pinMode(alcohol,INPUT);
  pinMode(airQuality_sensor, INPUT); pinMode(LPG,INPUT);
  Serial.println("Ready!");
  delay(1000);
  digitalWrite(buzzer,LOW);
  dht.begin();
}
 
void loop() {  
 
  Serial.println();
  Serial.println();
   airQuality();
   Carbon();
   Alcohol();
   Butane();
  //.............................Read Data from DHT11
  DHTRead();
  delay(2000);
}

void airQuality(void)
{
  int sensorValue =(analogRead(airQuality_sensor)/4 - 430);
  Serial.print("Air Quality = ");
  Serial.println(sensorValue);
  AIR_volt = sensorValue*(5.0/1024.0); //Convert analog values to voltage 
  Serial.print("Sensor value in volts = ");
  Serial.println(AIR_volt);
  RS_gas1 = ((5.0*10.0)/AIR_volt)-10.0; //Get value of RS in a gas
  Serial.print("Rs value = ");
  Serial.println(RS_gas1);
  ratio1 = RS_gas1/R0;  // Get ratio RS_gas/RS_air
  Serial.print("Ratio1 = ");
  Serial.println(ratio1);
  float ppm_log1 = (log10(ratio1)-b)/m; //Get ppm value in linear scale according to the the ratio value  
  float AIR_ppm = pow(10, ppm_log1); //Convert ppm value to log scale 
  Serial.print("Our desired PPM = ");
  Serial.println(AIR_ppm);
  double airPercentage = AIR_ppm/5; //Convert to percentage 
  Serial.print("Value in Percentage = "); //Load screen buffer with percentage value
  Serial.println(airPercentage); 
  Serial.println();
  delay(100);
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
 

void Carbon(void)
{
   int CORead = (analogRead (CO)/4 - 250);
   
  //............ For CO gas
  Serial.print("Carbonmonoxide:");
  Serial.println(CORead);
  CO_volt = CORead *(5.0/1024.0); //Convert analog values to voltage 
  Serial.print("CO value in volts = ");
  Serial.println(CO_volt);
  RS_gas2 = ((5.0*10.0)/CO_volt)-10.0; //Get value of RS in a gas
  Serial.print("Rs_gas2 value = ");
  Serial.println(RS_gas2);
  ratio2 = RS_gas2/R0;  // Get ratio RS_gas/RS_air
  Serial.print("Ratio2 = ");
  Serial.println(ratio2);
  float ppm_log2 = (log10(ratio2)-b)/m; //Get ppm value in linear scale according to the the ratio value  
  float CO_ppm = pow(10, ppm_log2); //Convert ppm value to log scale 
  Serial.print("Our desired PPM = ");
  Serial.println(CO_ppm);
  double coPercentage = CO_ppm/4; //Convert to percentage 
  Serial.print("Value in Percentage = "); //Load screen buffer with percentage value
  Serial.println(coPercentage); 
  if ((CO_ppm >= 40) && (CO_ppm <50))
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
    Serial.println("Healthy peercentage of air ");
  }
  delay(100);
  Serial.println();
}


void Alcohol(void)
{
  int alcoholRead = (analogRead(alcohol)/4);
   // .............................Read data from alcohol
  Serial.print("Alcohol:");
  Serial.println(alcoholRead);
   alcohol_volt = alcoholRead *(5.0/1024.0); //Convert analog values to voltage 
  Serial.print("alcohol value in volts = ");
  Serial.println(alcohol_volt);
  RS_gas3 = ((5.0*10.0)/alcohol_volt)-10.0; //Get value of RS in a gas
  Serial.print("Rs_gas3 value = ");
  Serial.println(RS_gas3);
  ratio3 = RS_gas3/R0;  // Get ratio RS_gas/RS_air
  Serial.print("Ratio3 = ");
  Serial.println(ratio3);
  float ppm_log3 = (log10(ratio3)-b)/m; //Get ppm value in linear scale according to the the ratio value  
  float alcohol_ppm = pow(10, ppm_log3); //Convert ppm value to log scale 
  Serial.print("Our desired PPM = ");
  Serial.println(alcohol_ppm);
  double alcoholPercentage = alcohol_ppm/5; //Convert to percentage 
  Serial.print("Value in Percentage = "); //Load screen buffer with percentage value
  Serial.println(alcoholPercentage); 
  if ((alcohol_ppm >=1000) && (alcohol_ppm < 3300))
  {
    Serial.println("You can stay here for 8hours");
  }
   else if(alcohol_ppm >= 3300)
   {
    Serial.println("The Air is Harzadrous to your Health");
   }
  Serial.println();
  delay(100);

}

void Butane(void)
{
  int LPGRead = (analogRead(LPG)/4 - 430);
  //.........................Read data from LPG
    Serial.print("LPG:");
  Serial.println(LPGRead);
  LPG_volt = LPGRead *(5.0/1024.0); //Convert analog values to voltage 
  Serial.print("LPG value in volts = ");
  Serial.println(LPG_volt);
  RS_gas4 = ((5.0*10.0)/LPG_volt)-10.0; //Get value of RS in a gas
  Serial.print("Rs_gas4 value = ");
  Serial.println(RS_gas4);
  ratio4 = RS_gas4/R0;  // Get ratio RS_gas/RS_air
  Serial.print("Ratio4 = ");
  Serial.println(ratio4);
  float ppm_log4 = (log10(ratio4)-b)/m; //Get ppm value in linear scale according to the the ratio value  
  float LPG_ppm = pow(10, ppm_log4); //Convert ppm value to log scale 
  Serial.print("Our desired PPM = ");
  Serial.println(LPG_ppm);
  double LPGPercentage = LPG_ppm/5; //Convert to percentage 
  Serial.print("Value in Percentage = "); //Load screen buffer with percentage value
  Serial.println(LPGPercentage); 
  if ((LPG_ppm >= 1000)&& (LPG_ppm < 2000))
  {
    Serial.println("You have less than 8hours to stay here");
  }
  else if (LPG_ppm >= 2000)
  {
    Serial.println("The Air is Harzadrous to your Health");
  }
  
  Serial.println();
  delay(100);
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
