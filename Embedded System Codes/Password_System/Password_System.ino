#include <IRremote.hpp>
#include <Password.h>

int IR = 2;

IRrecv irrecv(IR);
decode_results results;
Password pass = "1234";

#define Power      16753245
#define Mode       16736925
#define Mute       16769565
#define Play       16720605
#define Previous   16712445
#define Next       16761405
#define EQ         16769055
#define Vol-       16754775
#define Vol+       16748655
#define RPT        16750695
#define U/Sd       16756815
#define zero       16738455
#define one        16724175
#define two        16718055
#define three      16743045
#define four       16716015
#define five       16726215
#define six        16734885
#define seven      16728765
#define eight      16730805
#define nine       16732845



void setup() {
  Serial.begin(9600);
  irrecv.enableIRIn();
}

void loop() {
  if (irrecv.decode(&results)) {
    int me = results.value;
    
    switch(me) {
      case Power:
        pass.reset();
        break;
      case zero:
        pass.append('0');
        break;
      case one:
        pass.append('1');
        break;
      case two:
        pass.append('2');
        break;
      case three:
        Serial.print("3");
        pass.append('3');
        break;
      case four:
        Serial.print("4");
        pass.append('4');
        break;
      case five:
        Serial.print("5");
        pass.append('5');
        break;
      case six:
        pass.append('6');
        break;
      case seven:
        pass.append('7');
        break;
      case eight:
        pass.append('8');
        break;
      case nine:
        pass.append('9');
        break;
    }
   // Serial.print(results.value);
    irrecv.resume();
  }
}
