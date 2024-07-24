byte flowPin =  3;
byte sensorInterrupt = 0;
float calibrationFactor = 4.5;
volatile byte pulseCount;

float flowRate;
unsigned int flowMilliLitres;
unsigned long totalMilliLitres;

unsigned long oldTime;

void setup() {
  pinMode(flowPin,INPUT);
  Serial.begin(9600);
  digitalWrite(flowPin,HIGH);
  pulseCount = 0;
  flowRate   = 0;
  totalMilliLitres = 0;
  oldTime = 0;

  attachInterrupt(sensorInterrupt, pulseCount ,FALLING);
  

}

void loop() {
  if((millis() - oldTime) > 1000)
  {
     detachInterrupt(sensorInterrupt);
    flowRate = ((1000 / (millis() - oldTime)) * pulseCount);
    oldTime = millis();
    flowMilliLitres += (flowRate /60) * 1000;
    totalMilliLitres += flowMilliLitres;

    unsigned int frac;

    Serial.print("FlowRate: ");
    Serial.print(int(flowRate));
    Serial.print("L/min");
    Serial.println("\t");
    delay(500);

    pulseCount = 0;

    attachInterrupt(sensorInterrupt,pulseCount ,FALLING);
  }
  }
