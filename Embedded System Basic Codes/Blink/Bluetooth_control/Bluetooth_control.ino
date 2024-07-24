#define led 5
int i ;

void setup() {
Serial.begin(9600);
pinMode(led,OUTPUT);

}

void loop() {
 while(Serial.available() > 0 )
 i = Serial.read();
 Serial.print("\n");
 if (i = 1)
 {
  digitalWrite(led,HIGH);
 }
 else if (i = 0)
 {
  digitalWrite(led,LOW);  
 }

}
