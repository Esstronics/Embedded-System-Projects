#define highSp A0
#define lowSp  A1
#define left1 2
#define left2 3
#define right1 4
#define right2 5

int ldrLeft,ldrRight,ldrMid;
float dura1,dura2,dura3;
int   front,left,right;
String i;

void setup() {
  pinMode(left1,OUTPUT);  pinMode(left2,OUTPUT);
  pinMode(right1,OUTPUT); pinMode(right2,OUTPUT);
  pinMode(highSp,OUTPUT); pinMode(lowSp,OUTPUT);
  Serial.begin(9600); 
}

void loop() {
RobotControl();

}

void RobotControl(void)
{
while (Serial.available() >0);
i = Serial.read();
 // Front Movement
 if (i = "Front")
 {
 frontMovement();
 }
 //Right movement
 else if (i = "Right")
 {
    rightMovement();
 }

 //left movement
 else if(i = "Left") 
 {
     leftMovement();
 }
 
 else if (i = "Stop")
 {
 stopMovement();
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
