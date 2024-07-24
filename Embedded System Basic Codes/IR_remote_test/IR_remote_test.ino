#include <Password.h>
#include<IRremote.h>
int IR = 11;

IRrecv irrecv(IR);
decode_results results;
Password password = "222";

#define CHm   16753245
#define CH    16736925
#define CHp   16769565
#define Prev  16720605
#define Next  16712445
#define p/ps  16761405
#define Volm  16769055
#define Volp  16754775
#define EQ    16748655
#define Zero  16738455
#define Hund  16750695
#define Tund  16756815
#define One   16724175
#define Two   16718055
#define Three 16743045
#define four  16716015
#define five  16726215
#define six   16734885
#define seven 16728765
#define eight 16730805
#define nine  16732845


void setup() {
Serial.begin(9600);
irrecv.enableIRIn();

}

void loop() {
if (irrecv.decode(&results)){
 int me  = results.value;
 switch(me)
 {
  case CHm:
    Serial.println("CH-");
    break;
  case CH:
    Serial.println("CH");
    break;
  case CHp:
    Serial.println("CH+");
    break;
  case Volm:
    Serial.println("Vol-");
    break;
  case Volp:
    Serial.println("Vol+");
    break;
  case EQ:
    Serial.println("EQ");
    checkPassword();
    break;
  case Zero:
    Serial.println("0");
    break;
  case Hund:
    Serial.println("100+");
    break;
  case Tund:
    Serial.println("200+");
    break;
  case One:
    Serial.println("1");
    password.append('1');
    break;
  case Two:
    Serial.println("2");
    password.append('2');
    break;
  case Three:
    Serial.println("3");
    password.append('3');
    break;
  case four:
    Serial.println("4");
    password.append('4');
    break;
  case five:
    Serial.println("5");
    break;
  case six:
    Serial.println("6");
    break;
  case seven:
    Serial.println("7");
    break;
  case eight:
    Serial.println("8");
    break;
  case nine:
    Serial.println("9");
    break;
  
 }
 // Serial.println(results.value,DEC);
  irrecv.resume();
}
}



void checkPassword(void){
  if (password.evaluate()){
    Serial.println("Success");
    password.reset();
  }
  else {
    Serial.println("Wrong");
    password.reset() ;
  }
}
