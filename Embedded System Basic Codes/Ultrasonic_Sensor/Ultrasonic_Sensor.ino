#define trig 14
#define echo 27

int dist,dura;

void setup()
{
  Serial.begin(9600);
  pinMode(trig,OUTPUT);  pinMode(echo,INPUT);
  
}
 void loop(){
  digitalWrite(trig,HIGH); delayMicroseconds(20);
  digitalWrite(trig,LOW);  delayMicroseconds(20);
  dura = pulseIn(echo,HIGH);
  dist = (dura * 0.034)/2;
  Serial.println(dist);
  delay(100);
 }
