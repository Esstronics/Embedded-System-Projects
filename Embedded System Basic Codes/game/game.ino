#include <Servo.h>
Servo servo;
int X = A0;
int ServoPin = 9;
int Xread;
void setup() {
Serial.begin(9600);
pinMode(X, INPUT);
servo.attach(9);
servo.write(0);}


void loop() {
 Xread = analogRead(A0)* 0.176;
 Serial.print("Value: ");
 Serial.println(Xread); 
servo.write(Xread);
}
