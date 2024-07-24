#define a  A0
#define buzzer 5

void setup() {
  // put your setup code here, to run once:
  pinMode(a , INPUT); pinMode(buzzer , OUTPUT); 
  Serial.begin(9600) ; 

}

void loop() {
  // put your main code here, to run repeatedly:
 int aValue = analogRead(a); 
 Serial.print("Gas Value: ");  Serial.println(aValue);
  delay(100);  
  if (aValue >= 500)
  {
    digitalWrite(buzzer,HIGH);
    delay(2000);
    digitalWrite(buzzer,LOW);
  }
  else
  {
    digitalWrite(buzzer,LOW);
  }
}
