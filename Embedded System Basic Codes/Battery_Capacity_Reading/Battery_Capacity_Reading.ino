int batteryCap = A0;
float batteryVoltage ,batteryReading;
void setup() {
  Serial.begin(9600);
}
void loop() {
  batteryReading = analogRead(A0);
  batteryVoltage = ( batteryReading * 5 / (1023) ) ;
  Serial.print("Battery Capacity: ");
  Serial.print(batteryVoltage);
  Serial.print("       ");
  Serial.print("Battery Capacity: ");
  Serial.println(batteryReading);
  delay(500);
}
