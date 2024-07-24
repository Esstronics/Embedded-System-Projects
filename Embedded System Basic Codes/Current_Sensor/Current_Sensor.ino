int analogIn = A0;
double mVperAmp = 0.185; // use 100 for 20A Module and 66 for 30A Module
double RawValue;
double ACSoffset = 2.49;
double Voltage;
double Amps;

void setup(){
  
  pinMode(analogIn,INPUT);
  Serial.begin(9600);

}

void loop(){
RawValue = analogRead(analogIn);
Voltage = (RawValue / 1023.0) * 5; // Gets you mV
Amps = ((Voltage - ACSoffset) / mVperAmp);
Serial.print(RawValue);
Serial.print("Amps = "); // shows the voltage measured
Serial.println(Amps,2); // the '2' after Amps allows you to display 2 digits after decimal point
delay(1000);
}
