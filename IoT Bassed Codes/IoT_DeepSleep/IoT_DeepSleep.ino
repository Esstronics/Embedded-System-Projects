
void setup()
{
  pinMode(14, OUTPUT);
  for (int count = 0; count < 5; count++) {
    digitalWrite(14,HIGH);
    delay(1000);
    digitalWrite(14,LOW);
    delay(1000);
    ESP.deepSleep(10e6);
   }

}
  }


void loop()
{
  
}
