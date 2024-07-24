#include <Key.h>
#include <Keypad.h>
const byte ROWS = 4;
const byte COLS = 4;
char keys [ROWS][COLS] = {
  {'A', '1', '2', '3'},
  {'B', '4', '5', '6'},
  {'C', '7', '8', '9'},
  {'D', '*', '0', '#'}
  };
byte rowPins[ROWS]= {9,8,7,6};
byte colPins[COLS] = {5,4,3,2};
Keypad customKeypad = Keypad(makeKeymap(Keys), rowPins, colPins , ROWS , COLS);
void setup() {
  Serial.begin(9600);
}
void loop() {
   char customKey = customKeypad.getKey();
   if (customKey)
   {
    Serial.println(customKey);
    delay(600);
   }
}
