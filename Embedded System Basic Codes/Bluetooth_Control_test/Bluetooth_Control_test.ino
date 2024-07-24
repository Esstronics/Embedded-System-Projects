#define led 8
char i = 0;
void setup() {
Serial.begin(9600);
pinMode(led,OUTPUT);
digitalWrite(led,LOW);
}

void loop() {
 if(Serial.available() > 0)
 {
  i = Serial.read();
  Serial.print(i);
  Serial.print("\n");
  if (i == '1')
  {
    digitalWrite(led,HIGH);
  }
  else if (i == '2')
  {
    digitalWrite(led,LOW);
  }
 }
}
