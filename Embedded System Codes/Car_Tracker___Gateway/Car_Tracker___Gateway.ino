//#include <TinyGPS++.h>
//#include <SoftwareSerial.h>
//SoftwareSerial  sim(3,2);




//SoftwareSerial mySerial(RXPin,TXPin);

void setup() {

  
  Serial.begin(9600);
 
}

void loop() {
  // put your main code here, to run repeatedly:
 Serial.println("AT+CPIN");
  while(Serial.available() >0)
  {
    if (Serial.find("+CPIN:READY"))
    {
  Serial.println("AT"); //Once the handshake test is successful, it will back to OK
 // updateSerial();

  Serial.println("AT+CMGF=1"); // Configuring TEXT mode
  //updateSerial();
  Serial.println("AT+CMGS=\"+2349010864064\"");//You can change the phone number 
  //updateSerial();
  Serial.print("Hello Akotronics"); //text content
  //updateSerial();
  Serial.write(26);
  }

  }
}
