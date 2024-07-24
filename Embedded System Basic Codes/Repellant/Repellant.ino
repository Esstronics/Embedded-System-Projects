int trig = 7;
void setup() {
 pinMode(trig,OUTPUT);
Serial.begin(9600);
}

void loop() {
  digitalWrite(trig,HIGH);
  delayMicroseconds(25);
  digitalWrite(trig,LOW);
  delayMicroseconds(25);
  
}
