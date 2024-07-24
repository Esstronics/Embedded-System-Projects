#define touch 3
int valueT;
void setup() {
pinMode(touch,INPUT);
Serial.begin(9600);

}

void loop() {
valueT = analogRead(touch);
Serial.println(valueT);
delay(200);
}
