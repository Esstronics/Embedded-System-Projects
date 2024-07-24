int alcohol = A0;
int buzzer = 5;
int sensorValue;

void setup() {
  // put your setup code here, to run once:
 pinMode(alcohol, INPUT);
 pinMode(buzzer, OUTPUT);
 Serial.begin(9600);
 
}

void loop() {
  // put your main code here, to run repeatedly:
  sensorValue = analogRead(A0);
  Serial.println(sensorValue);
  delay(1000);
 /* if (sensorValue >= 10.24){
    Serial.println ("Alcohol Detected");
    digitalWrite (buzzer, HIGH);
    delay(1000);
  }
  else
  {
    Serial.println("No Alcohol Detected");
    digitalWrite (buzzer, LOW);
  }
  */

}
