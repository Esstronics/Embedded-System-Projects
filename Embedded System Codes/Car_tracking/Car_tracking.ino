#include <LiquidCrystal.h>
#include <SoftwareSerial.h>
// Configure software serial port
LiquidCrystal lcd(12,11,10,9,8,7,6);
SoftwareSerial sim(3, 2);
// Variable to store text message
String textMessage;
void welcome(void)
{
  lcd.begin(16,2);  lcd.clear();  lcd.setCursor(2,0);
  lcd.print("Car Tracking"); lcd.setCursor(5,1);  lcd.print("Device");  delay(2000);
  lcd.clear();
 lcd.setCursor(4,0);  lcd.print("Designed ");  lcd.setCursor(7,1);   lcd.print("By");  delay(3000);  lcd.clear(); lcd.setCursor(5,0); lcd.print("OLAOYE"); 
  lcd.setCursor(5,1);  lcd.print("SUNDAY");   delay(1500);  lcd.clear();      lcd.setCursor(3,0);   lcd.print("Matric No:");    delay(100);    lcd.setCursor(2,1); 
  lcd.print("19010631018");  delay(1500); lcd.clear(); lcd.print(" Supervised by");   delay(1500);   lcd.clear();  lcd.print("   ENGR");   lcd.setCursor(4,1); 
  lcd.print("ADEGBESAN");  delay(2000);  lcd.clear(); 
  lcd.setCursor(1,0);   lcd.print("Searching for"); lcd.setCursor(3,1);  lcd.print("Network"); delay(2000); lcd.print("."); delay(700); lcd.print("."); delay(700);
  lcd.print("."); delay(700); lcd.clear(); delay(100);  lcd.clear(); lcd.setCursor(1,0); lcd.print("Calibrating"); lcd.setCursor(3,1);  lcd.print("Sensor"); delay(2000);
  lcd.print("."); delay(700); lcd.print("."); delay(700); lcd.print("."); delay(700);  lcd.clear();delay(100);
  lcd.print("System Ready");  delay(1000); lcd.print("!"); delay(500); lcd.print("!"); delay(1000); lcd.print("!"); delay(1000);  lcd.clear();  delay(300);
   
}
void setup() {
  
  // Initializing serial commmunication
  Serial.begin(9600); 
  sim.begin(9600);
  sim.print("AT+CMGF=1\r"); 
  delay(100);
  sim.print("AT+CNMI=2,2,0,0,0\r");
  delay(100);
  welcome();
}

void loop(){
  lcd.clear();
  lcd.print("Device is Ready"); lcd.setCursor(0,1); lcd.print("to send location");
  delay(200);
  if(sim.available()>0){
    textMessage = sim.readString();
    Serial.print(textMessage);    
    delay(10);
  } 
  
  if(textMessage.indexOf("LOCATION")>=0){
    String message = "Longitude: 3.6705 E and Latitude:6.9883 N";
    lcd.clear();
    lcd.print(" Location is ");  lcd.setCursor(4,1);  lcd.print("requested");
    delay(500);
    sendSMS(message);
    lcd.clear();  lcd.print("Locaton Sent");  delay(1000);
    textMessage = "";
    Serial.println("Locaton Sent");
    delay(1000);
  }
}  

// Function that sends SMS
void sendSMS(String message){
  // AT command to set SIM900 to SMS mode
  sim.print("AT+CMGF=1\r"); 
   updateSerial();
  delay(100);

  sim.println("AT+CMGS=\"+2348033604882\""); 
   updateSerial();
  delay(100);
  // Send the SMS
  sim.println(message); 
  updateSerial();
  delay(100);
  sim.println((char)26); 
  updateSerial();
  delay(100);
  sim.println();
  delay(2000);  
}
void updateSerial()
{
  delay(500);
  while (Serial.available()) 
  {
    sim.write(Serial.read());//Forward what Serial received to Software Serial Port
  }
  while(sim.available()) 
  {
    Serial.write(sim.read());//Forward what Software Serial received to Serial Port
  }
}
