#define pulse A0
int Threshold = 509;

void setup() {
pinMode(pulse,INPUT);
Serial.begin(9600);
delay(1000);

}

void loop() {
  
  int pulseReading = analogRead(pulse) ;
  int  b = pulseReading - Threshold; 
  int  a = b * 0.14922;   //constant value
  if (a <= -1)
  { 
     a = 0;
     Serial.print("BPM: ");     Serial.print(a); Serial.print("    "); 
     Serial.print("pulseReading: ");     Serial.println(pulseReading);  delay(500);
  }
  else
  {
  Serial.print("BPM: ");     Serial.print(a); Serial.print("    "); 
  Serial.print("pulseReading: ");     Serial.println(pulseReading);  delay(500);
  }
}
