#include <Wire.h>
#include <SPI.h>
#include <MFRC522.h>
#include <LiquidCrystal_I2C.h>
int led = 8;
int buzz = 7;
LiquidCrystal_I2C lcd(0x27,16,2);
 
#define SS_PIN 10
#define RST_PIN 9
MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance.
#define beep_pin 8
//LiquidCrystal lcd(13,12,11,6,5,4,3);

 #include <Servo.h>
Servo myservo;
 void welcome(void)
{
   lcd.begin();  lcd.backlight(); pinMode(led , OUTPUT); 
   lcd.setCursor(3, 1);    lcd.print("RFID Based");   lcd.setCursor(3, 0);   lcd.print("Door Lock");
  delay(1500);   lcd.clear();  
  lcd.print("Calibrating ");   lcd.setCursor(0,1);   lcd.print("Sensor.");   delay(2000);  lcd.print("."); delay(500);  lcd.print("."); delay(500);
  lcd.print("."); delay(500);
  lcd.clear();   lcd.print("System Ready"); delay(1000);    lcd.print("!"); delay(500);  lcd.print("!"); delay(500);    lcd.print("!"); delay(500);  
  lcd.clear();  delay(100);
}
void setup() 
{
 
  Serial.begin(9600);  
  pinMode(beep_pin,OUTPUT);
  pinMode(buzz ,OUTPUT);
  digitalWrite(beep_pin,LOW);
  
  
   
  SPI.begin();      // Initiate  SPI bus
  mfrc522.PCD_Init();   // Initiate MFRC522
  Serial.println("Put your card to the reader...");
  Serial.println();
  
  myservo.attach(6); 
   myservo.write(0);
   welcome();
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
  Serial.print("UID tag :");
  String content= "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
     Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
     Serial.print(mfrc522.uid.uidByte[i], HEX);
     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  Serial.println();
  Serial.print("Message : ");
  content.toUpperCase();
  

  
  if (content.substring(1) == "5C 7A 2C 17"|| content.substring(1) == "F9 54 73 B3"  ) //change here the UID of the card/cards that you want to give access
  {
    Serial.println("Authorized access");
    unlock();
     lock(); 
   // delay(1200);   
   digitalWrite(buzz,HIGH);
   delay(70);
   digitalWrite(buzz,LOW);
   delay(40);
   digitalWrite(buzz,HIGH);
   delay(70);
   digitalWrite(buzz,LOW);
   delay(40);
   digitalWrite(buzz,HIGH);
   delay(70);
   digitalWrite(buzz,LOW);
   delay(40);
    digitalWrite(led ,HIGH);
    delay(1000);
    digitalWrite(led,LOW);
  }
 
 else   {
   Serial.println(" Access Denied");
  // delay(1000);
   digitalWrite(led ,LOW);
   digitalWrite(buzz,HIGH);
   delay(2000);
   digitalWrite(buzz,LOW);
 }
}
void unlock()
{
 for (int pos = 0; pos <= 180; pos += 1) 
     { // goes from 0 degrees to 180 degrees in steps of 1 degree
     myservo.write(pos);              // tell servo to go to position in variable 'pos'
     delay(15);                       // waits 15ms for the servo to reach the position
     }
 delay(3000);  
}
void lock()
{
   for (int pos = 180; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  }}
