#include <SPI.h>
#include <SD.h>
int soundPin = 6;
const int chipSelect = 10;
int soundValue;
void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
 Serial.print("Initializing SD card...");
 pinMode(6,INPUT);
  // see if the card is present and can be initialized:
  if (!SD.begin(chipSelect)) {
    Serial.println("Card failed, or not present");
    // don't do anything more:
    while (1);
  }
  Serial.println("card initialized.");
}
void loop() {
  //
    String dataString = "";
  soundValue = digitalRead (6);
     if ( soundValue == 1) {
  Serial.println("SOUND OCCUR");
  dataString = "Sound Occur";
  delay(500);
  dataString += "";
 }
 else {
  Serial.print("No Sound occur");
  delay(500);
    }

  // open the file. note that only one file can be open at a time,
  // so you have to close this one before opening another.
  File dataFile = SD.open("code.txt", FILE_WRITE);

  // if the file is available, write to it:
  if (dataFile) {
    dataFile.println(dataString);
    dataFile.close();
    // print to the serial port too:
    Serial.println(dataString);
  }
  // if the file isn't open, pop up an error:
  else {
    Serial.println("error opening code.txt");
  }
}
