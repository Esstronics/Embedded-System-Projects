const byte ROWS = 5;
const byte COLS = 4;
char keys[ROWS][COLS] = {{"1","2","3","A"},{"4","5","6","B"},{"7","8","9","C"},{"*","0","#"}};
byte rowPins[ROWS]= {6,7,8,9,};
byte colPins[COLS] = {2,3,4,5};
Keypad keypad = Keypad (makeKeymap(Keys),rowPins,colPins,ROWS,COLS);
char KEY[4] = {'1','2','3','4'};
char attempt[4] ={0,0,0,0};
int z 0;
void setup() {
  Serial.begin(9600);
}
  void correctKEY(){
  Serial.println(" KEY ACCEPTED....... ")
  }
  void incorrectKEY(){
    Serial.println("KEY REJECTED");
  }


 void  checkKEY ()
 {
  int correct = 0;
  int i;
  for ( i = 0 ; i<4 ; i++)
  {
    if (attempt[1] == KEY[i];)
    {
      correct++;
    }
  }
  if (correct == 4){
    correctKEY();
  }
  for (int zz= 0 ; zz< 4 ; zz++)
  {
    attempt[zz] =0 ;
  }
 }
 void readKeypad()
 {
  char Key = Keypad.getKey();
  if (KEy != NO_KEY)
  {
    switch (Key)
    {
      case "*" :
      z= 0 ;
      break;
      case '#':
      delay (100);
      checkKEY();
      break;
      default:
        attempt[z] =Key;
        z++
    }
  }
 }

void loop() {
   readKeypad();
}
