#define vibration1 A1
#define vibration2 7
int vibrationValue1;
int vibrationValue2;
void setup() {
  pinMode (vibration1,INPUT);
  pinMode (vibration2,INPUT);
  Serial.begin(9600);
}

void loop() {
 vibrationValue1 = analogRead(vibration1);
 vibrationValue2 = digitalRead(vibration2);
 Serial.print("sensorvalue:");
 Serial.println(vibrationValue2);
 delay(500);

}
