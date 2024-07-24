#include <ESP8266WiFi.h>

#define highSp A0
#define lowSp  A1
#define left1 2
#define left2 3
#define right1 4
#define right2 5

WiFiServer server(80);

int ldrLeft,ldrRight,ldrMid;
float dura1,dura2,dura3;
int   front,left,right;
String i;

void setup() {
  pinMode(left1,OUTPUT);  pinMode(left2,OUTPUT);
  pinMode(right1,OUTPUT); pinMode(right2,OUTPUT);
  pinMode(highSp,OUTPUT); pinMode(lowSp,OUTPUT);
  Serial.begin(9600); 

   WiFi.disconnect();
  delay(3000);
  Serial.println("Start");
   WiFi.begin("Uthman1","uthman7890");
  while ((!(WiFi.status() == WL_CONNECTED))){
    delay(300);
    Serial.print("...");

  }
  Serial.println("Connected!");
  Serial.println((WiFi.localIP().toString()));
  server.begin();

  
}

void loop() {
RobotControl();

}

void RobotControl(void)
{
 WiFiClient client = server.available();
    if (!client) { return; }
    while(!client.available()){  delay(1); }
    i = (client.readStringUntil('\r'));
    i.remove(0, 5);
    i.remove(i.length()-9,9);
 if (i = "Front")
 {
 frontMovement();
 delay(1);
 }
 //Right movement
 else if (i = "Right")
 {
    rightMovement();
    delay(1);
 }

 //left movement
 else if(i = "Left") 
 {
    leftMovement();
    delay(1);
 }
 
 else if (i = "Stop")
 {
    stopMovement();
    delay(1);
 }
}





void leftMovement(void)
{
 digitalWrite(left1,LOW);
 digitalWrite(left2,LOW);
 digitalWrite(right1,LOW);
 digitalWrite(right2,HIGH);
}

void rightMovement(void)
{
 digitalWrite(left1,HIGH);
 digitalWrite(left2,LOW);
 digitalWrite(right1,LOW);
 digitalWrite(right2,LOW);
}

void frontMovement(void)
{
 digitalWrite(left1,HIGH);
 digitalWrite(left2,LOW);
 digitalWrite(right1,LOW);
 digitalWrite(right2,HIGH);
}

void stopMovement(void)
{
 digitalWrite(left2,LOW);
 digitalWrite(left1,LOW);
 digitalWrite(right2,LOW);
 digitalWrite(right1,LOW); 
}
