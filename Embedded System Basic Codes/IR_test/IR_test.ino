#define IR 6
int IrValue;

void setup() {
  pinMode(IR,INPUT);
  Serial.begin(9600); 

}

void loop() {
  IrValue = digitalRead(IR);
  Serial.println(IrValue);
  delay(200);
}
