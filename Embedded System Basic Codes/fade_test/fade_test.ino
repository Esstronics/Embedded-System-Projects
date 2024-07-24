
int me = 0;
void setup() {
  // put your setup code here, to run once:
pinMode(me,OUTPUT);
}

void loop() {
  int you;
  for (me = 0 ; me <= 255 ;me ++)
  {
     you = you + 6;
    
  }
delay(100);
digitalWrite(me,you);
}
