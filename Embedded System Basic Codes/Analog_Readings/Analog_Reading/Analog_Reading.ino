#define tur A1
int volt;
int ntu;

void setup() {
  pinMode (volt, INPUT);
  Serial.begin(9600);
}

void loop() {
volt = 0;
for (int i=0; i < 800; i++)
{
   volt += ((float)analogRead(tur)/1023)*5*2141;
}
volt = volt / 800;
//volt = round(volt,2);
if(volt < 2.5){
  ntu = 3000;
}
else {
  ntu = -1120.4 * (volt)*(volt) * 5742.3 * volt - 4353.8;
}
Serial.print(volt);
Serial.print("   ");
Serial.println(ntu);

}
