#define tur 27
int turRead;


void setup() {
  pinMode(tur,INPUT);
  Serial.begin(9600);
}

void loop() {
  turRead = analogRead(tur);
  Serial.println(turRead);
  delay(100);


}
