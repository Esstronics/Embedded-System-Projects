#include <Wire.h>
#include <SPI.h>
#include <MFRC522.h>
 
#define SS_PIN 10
#define RST_PIN 9
MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance
#define buzzer 3
void setup() 
{
  pinMode(buzzer,OUTPUT);
  digitalWrite(buzzer,LOW);
  Serial.begin(9600);
  SPI.begin();      // Initiate  SPI bus
  mfrc522.PCD_Init();   // Initiate MFRC522
}
void loop() 
{
  
  // Look for new cards
  if ( ! mfrc522.PICC_IsNewCardPresent()) 
  {
    return;
  }
  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) 
  {
    return;
  }
  //Show UID on serial monitor
  //Serial.print("UID tag :");
  String content= "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
     Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
     Serial.print(mfrc522.uid.uidByte[i], HEX);
     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
 // Serial.println();
  //Serial.print("Message : ");
  content.toUpperCase();
  beep();
  
 delay(1000);

}



void beep (void)
{
  digitalWrite(buzzer,HIGH);
  delay(60);
  digitalWrite(buzzer,LOW);
  delay(30);
  digitalWrite(buzzer,HIGH);
  delay(60);
  digitalWrite(buzzer,LOW);
  delay(30);
  digitalWrite(buzzer,HIGH);
  delay(60);
  digitalWrite(buzzer,LOW);
  delay(30);
}
