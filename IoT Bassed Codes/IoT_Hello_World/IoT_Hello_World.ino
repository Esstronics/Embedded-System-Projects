#define led1 5 
#define led2 4
#define led3 2
#define ldr A0
void setup() {
  // put your setup code here, to run once:
pinMode(led1,OUTPUT);
pinMode(led2,OUTPUT);
pinMode(led3,OUTPUT);
pinMode(ldr,INPUT);
Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  int ldrValue = analogRead(ldr);
  Serial.println(ldrValue);
  delay(300);
  if (ldrValue <= 10){
digitalWrite(led1,HIGH);
digitalWrite(led2,LOW);
digitalWrite(led3,LOW);
delay(1000);
digitalWrite(led1,LOW);
digitalWrite(led2,HIGH);
digitalWrite(led3,LOW);
delay(1000);
}
else if ((ldrValue >=12) && (ldrValue <=22)){
digitalWrite(led1,LOW);
digitalWrite(led2,LOW);
digitalWrite(led3,HIGH);
delay(1000);
digitalWrite(led1,HIGH);
digitalWrite(led2,LOW);
digitalWrite(led3,HIGH);
delay(1000);
}
else if (ldrValue >=29){
digitalWrite(led1,HIGH);
digitalWrite(led2,HIGH);
digitalWrite(led3,LOW);
delay(1000);
digitalWrite(led1,LOW);
digitalWrite(led2,HIGH);
digitalWrite(led3,HIGH);
delay(1000);
}
}
