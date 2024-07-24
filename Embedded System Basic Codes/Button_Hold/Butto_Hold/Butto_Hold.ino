#define button 3
#define led 13
int State;
void setup() {
pinMode(3,INPUT);
pinMode(led,OUTPUT);
Serial.begin(9600);
}

void loop() {
  int i =0;
  State = digitalRead(3);
   Serial.println(State);
 if (State ==HIGH)
  {
   for (i = 0; i < 31 ; i++)
    {
      delay(100);
    }
    if (i = 30)
    {
      digitalWrite(led,HIGH);
      delay(3000);
      digitalWrite(led,LOW);
    }
  }

  else 
  {
   if (State ==LOW)
   {
    i = 0;
    digitalWrite(led,LOW); 
   }
  }
}
