#define x A0
#define y A1
#define z A2
int xRead = 0;
int yRead = 0;
int zRead = 0;

void setup() {
pinMode(x,INPUT);
pinMode(y,INPUT);
pinMode(z,INPUT);
Serial.begin(9600);

}

void loop() {
xRead = analogRead(x)-320;
yRead = analogRead(y);
zRead = analogRead(z)-266;
int angles = (xRead * 90) / 82;
Serial.print("x: ");
Serial.println(angles);

Serial.print(xRead);
/*Serial.print("       y: ");
Serial.print(yRead);*/
Serial.print("       z: ");
Serial.println(zRead);
delay(500);
}
