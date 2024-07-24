float a = A0;
float aRead;
void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
pinMode(a,INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
aRead = analogRead(a) ;
float volt = aRead * 5.0 / 1024;
Serial.print("pH:");
Serial.println(volt);
delay(500);
}
