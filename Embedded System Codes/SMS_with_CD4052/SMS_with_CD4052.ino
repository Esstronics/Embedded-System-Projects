
#include <SoftwareSerial.h>

SoftwareSerial  mySerial(3,2); //13,3 of CD4052   6 to gnd
#define B 5 //9
#define A 4 //10

#define b 13

int bRead;




void setup() {
   Serial.begin(9600);
   mySerial.begin(9600);
   pinMode(A,OUTPUT);       pinMode(B,OUTPUT);  
   // low,low to ON bit X0(12),Y0(1)
//  digitalWrite(A,HIGH);    digitalWrite(B,LOW);// To on bit X1(14),Y1(5)
//  Serial.println("Initializing...");
//  delay(500); 
//  mySerial.println("AT"); //Once the handshake test is successful, it will back to OK
//  updateSerial();  
//
//  mySerial.println("AT+CMGF=1"); // Configuring TEXT mode
//  updateSerial();
//  mySerial.println("AT+CMGS=\"+2347011473337\"");//You can change the phone number 
//  updateSerial();
//  mySerial.println("Hello world");//text content
//  updateSerial();
//  mySerial.write(26);
//  delay(500);

}

void loop() {
  Serial.println(digitalRead(b));
  if (digitalRead(b) == HIGH)
  {
  digitalWrite(A,HIGH);    digitalWrite(B,LOW);// To on bit X1(14),Y1(5)
  Serial.println("Initializing...");
  delay(1000); 
  mySerial.println("AT"); //Once the handshake test is successful, it will back to OK
  updateSerial();  

  mySerial.println("AT+CMGF=1"); // Configuring TEXT mode
  updateSerial();
  mySerial.println("AT+CMGS=\"+2347011473337\"");//You can change the phone number 
  updateSerial();
  mySerial.println("Hello world");//text content
  updateSerial();
  mySerial.write(26);
  delay(500);
  }
}





void updateSerial() 
{
  delay(500);
  while (Serial.available()) 
  {
    mySerial.write(Serial.read());//Forward what Serial received to Software Serial Port
  }
  while(mySerial.available()) 
  {
    Serial.write(mySerial.read());//Forward what Software Serial received to Serial Port
  }
 
}
