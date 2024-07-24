#include <Wire.h> 
#include <SoftwareSerial.h>
SoftwareSerial mySerial(3,2);
#include <Stepper.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,16,2);
#define trig 5
#define echo 4
#define alarm 7
//stepper motor declaration
const int stepsPerRevolution = 2048;
Stepper myStepper(stepsPerRevolution,8,9,10,11);
void setup() {
  pinMode(alarm,OUTPUT);
 lcd.begin();  lcd.backlight();  pinMode(trig,OUTPUT);   pinMode(echo,INPUT); 
 //Stepper motor initializtion
 myStepper.setSpeed(15);
  Serial.begin(9600);     mySerial.begin(9600);     Serial.println("Initializing...");
 Serial.begin(9600);
 welcome();

}
void welcome(void)
{
   lcd.clear();
  lcd.print("Human Detection");
  lcd.setCursor(5,1);
  lcd.print("Robot");  delay(3000);  lcd.clear(); delay(100);
  lcd.print(" Supervised by");   lcd.setCursor(3,1);  lcd.print("Eng Adeyeye"); delay(2000);  lcd.clear();  delay(100); lcd.setCursor(1,0);
  lcd.print("Searching for"); lcd.setCursor(3,1);  lcd.print("Network"); delay(2000); lcd.print("."); delay(700); lcd.print("."); delay(700); lcd.print("."); delay(700);
  lcd.clear(); delay(100);  lcd.clear(); lcd.setCursor(3,0);
  lcd.print("Calibrating"); lcd.setCursor(3,1);  lcd.print("Sensor"); delay(3000); lcd.print("."); delay(700); lcd.print("."); delay(700); lcd.print("."); delay(700);
  lcd.clear();
  delay(100);
  lcd.print("System Ready"); delay(1000); lcd.print("!"); delay(500); lcd.print("!"); delay(1000); lcd.print("!"); delay(1000);  lcd.clear();  delay(300);
}
void loop() {
  
 //Stepper function.
for ( int i = 0; i < 5 ; i ++)
{
  myStepper.step(400);
  search();
}
for (int i = 0; i < 5 ; i++)
{
  myStepper.step(-400);
  search();
}

}

//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
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
//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
void sendMessage (){
mySerial.println("AT");
updateSerial();
mySerial.println("AT+CMGF=1"); // Configuring TEXT mode
updateSerial();
mySerial.println("AT+CMGS=\"+2349077994397\"");
updateSerial();
mySerial.print("Be ware!!!, Human is Detected"); 
updateSerial();
mySerial.write(26);

}


void search(void)
{
 digitalWrite(trig,HIGH);
 delayMicroseconds(20);
 digitalWrite(trig,LOW);
 delayMicroseconds(20);
 int duration = pulseIn(echo , HIGH);
 int distance = duration * 0.034 / 2;
 Serial.println(distance);
 delay(50);
 if (distance <= 40)
 {
  sendMessage();
  lcd.clear(); lcd.print("Human Detected"); lcd.setCursor(3,1); lcd.print("Beware"); delay(700); lcd.print("!"); delay(100);  lcd.print("!"); delay(100); lcd.print("!"); delay(100);
  digitalWrite(alarm,HIGH); delay(900); digitalWrite(alarm,LOW);
 } 
 else
 {
  digitalWrite(alarm,LOW);
  lcd.clear();   lcd.setCursor(4,0);   lcd.print("No Human");  lcd.setCursor(4,1);  lcd.print("Detected");  delay(100);
 }
}
