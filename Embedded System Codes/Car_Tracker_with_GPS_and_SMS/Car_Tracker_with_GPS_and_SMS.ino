#include <LiquidCrystal.h>
#include <TinyGPS++.h> // library for GPS module
#include <SoftwareSerial.h>
LiquidCrystal lcd(12,11,10,9,8,7,6);
TinyGPSPlus gps;  // The TinyGPS++ object
SoftwareSerial  mySerial(3,2);  //connect to A and B of the CD4052
#define B 5 //connect to Y of the IC 
#define A 4 //connect  to X of the IC
float latitude , longitude;
int year , month , date, hour , minute , second;
String date_str , time_str , lat_str , lng_str;
int pm;
String textMessage;

void welcome(void)
{
  
  lcd.clear();
}

void setup() {
   Serial.begin(9600);
   mySerial.begin(9600);
   lcd.begin(16,2);
   pinMode(A,OUTPUT);     pinMode(B,OUTPUT);
   delay(100);
   digitalWrite(A,LOW);     digitalWrite(B,LOW);
   delay(100);
    //set sim Module to sms mode
  // 
  
}




//............................SEND MESSAGE FUNCTION
void recieveSend(void)
{
  digitalWrite(A,HIGH);     digitalWrite(B,LOW);
  delay(3000);
  Serial.println("SIM800 ready...");
  mySerial.print("AT+CMGF=1\r"); 
  delay(100);
  mySerial.print("AT+CNMI=2,2,0,0,0\r");
  delay(100);
   if(mySerial.available()>0)
   {  
    textMessage = mySerial.readString();
    delay(500);
    Serial.print(textMessage);    
    delay(10);
  } 
   
  if(textMessage.indexOf("LOCATION")>=0)
  {
    String message = "Lat: " +lat_str +" and " +"long: " +lng_str ;
    delay(100);
    sendSMS(message);
    Serial.println("location is resquested");
    textMessage = "";
  }
  
}


void loop() {
  Location();
   // recieveSend();   
    
}



void Location(void)
{
   digitalWrite(A,LOW);    digitalWrite(B,LOW);
   while (mySerial.available() > 0) //while data is available
    if (gps.encode(mySerial.read())) //read gps data
    {
      if (gps.location.isValid()) //check whether gps location is valid
      {
        latitude = gps.location.lat();
        lat_str = String(latitude , 6); // latitude location is stored in a string
        longitude = gps.location.lng();
        lng_str = String(longitude , 6); //longitude location is stored in a string
        Serial.print("Latitude: ");
        Serial.print (lat_str);
        Serial.print("    ");
        Serial.print("Longitude:");
        Serial.println (lng_str);
        delay(100);
         recieveSend();
      }
     
    }
 
}

// Function that sends SMS
void sendSMS(String message){
  // AT command to set SIM900 to SMS mode
  mySerial.println("AT"); //Once the handshake test is successful, it will back to OK
  updateSerial();

  mySerial.println("AT+CMGF=1"); // Configuring TEXT mode
  updateSerial();
  mySerial.println("AT+CMGS=\"+2347064625756\"");//You can change the phone number 
  updateSerial();
  mySerial.println(message); //text content
  updateSerial();
  mySerial.write(26);
  /*
  mySerial.print("AT+CMGF=1\r"); 
  delay(100);

  // REPLACE THE X's WITH THE RECIPIENT'S MOBILE NUMBER
  // USE INTERNATIONAL FORMAT CODE FOR MOBILE NUMBERS
  mySerial.println("AT + CMGS = \"+2349010864064\""); 
  delay(100);
  // Send the SMS
  mySerial.println(message); 
  delay(100);

  // End AT command with a ^Z, ASCII code 26
  mySerial.println((char)26); 
  delay(100);
  mySerial.println();
  // Give module time to send SMS
  delay(3000);  */
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






















void Waste(void)
{
   if (gps.date.isValid()) //check whether gps date is valid
      {
        date_str = "";
        date = gps.date.day();
        month = gps.date.month();
        year = gps.date.year();
        if (date < 10)
          date_str = '0';
        date_str += String(date);// values of date,month and year are stored in a string
        date_str += " / ";

        if (month < 10)
          date_str += '0';
        date_str += String(month); // values of date,month and year are stored in a string
        date_str += " / ";
        if (year < 10)
          date_str += '0';
        date_str += String(year); // values of date,month and year are stored in a string
      }
      if (gps.time.isValid())  //check whether gps time is valid
      {
        time_str = "";
        hour = gps.time.hour();
        minute = gps.time.minute();
        second = gps.time.second();
        minute = (minute + 30); // converting to IST
        if (minute > 59)
        {
          minute = minute - 60;
          hour = hour + 1;
        }
        hour = (hour + 5) ;
        if (hour > 23)
          hour = hour - 24;   // converting to IST
        if (hour >= 12)  // checking whether AM or PM
          pm = 1;
        else
          pm = 0;
        hour = hour % 12;
        if (hour < 10)
          time_str = '0';
        time_str += String(hour); //values of hour,minute and time are stored in a string
        time_str += " : ";
        if (minute < 10)
          time_str += '0';
        time_str += String(minute); //values of hour,minute and time are stored in a string
        time_str += " : ";
        if (second < 10)
          time_str += '0';
        time_str += String(second); //values of hour,minute and time are stored in a string
        if (pm == 1)
          time_str += " PM ";
        else
          time_str += " AM ";
      } 
}
