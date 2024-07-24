

int a = A0;
void setup() {
pinMode(a,INPUT);
Serial.print(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
int reading = analogRead(a);
Serial.print(" Read : ");
Serial.println(reading);
delay(1000);
}
