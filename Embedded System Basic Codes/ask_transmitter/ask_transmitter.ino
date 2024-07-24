#include <RH_ASK.h>
#include <SPI.h> 

RH_ASK driver(2000, 4, 2, 5); 
  
void setup()
{
    Serial.begin(9600);	  // Debugging only
    if (!driver.init()){
       Serial.println("init failed");
    }
}

void loop()
{
    const char *msg = "hello World!";

    driver.send((uint8_t *)msg, strlen(msg));
    driver.waitPacketSent();
    Serial.println(msg);
    delay(200);
}
