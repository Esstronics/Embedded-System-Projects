
#include <Servo.h>
#define vr A0
int vrScale;
Servo myservo;  


void setup() {
  myservo.attach(9); 
  pinMode(vr,OUTPUT);
  Serial.begin();
 
}

void loop() {
 vrScale = analogRead(vr)/1023 * 180;
 Servo.write(vrScale);
  
}
