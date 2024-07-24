int button  = 33;
int buttonState;
void setup() {
pinMode(button,INPUT);
Serial.begin(9600);
}

void loop() {
buttonState = digitalRead(button);
Serial.println(buttonState);
delay(500);
}
