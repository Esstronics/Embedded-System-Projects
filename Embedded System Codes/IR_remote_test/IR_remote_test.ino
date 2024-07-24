#include<IRremote.h>
int IR = 11;  //input pin

IRrecv irrecv(IR); // congfigure the library to recieving format
decode_results results;  // recieving variable


void setup() {
Serial.begin(9600);
irrecv.enableIRIn();

}

void loop() {
if (irrecv.decode(&results)){
 int me  = results.value;

 Serial.println(results.value,DEC);  //results.value or me
 irrecv.resume(); //continue waiting to recieve signal
}
}
