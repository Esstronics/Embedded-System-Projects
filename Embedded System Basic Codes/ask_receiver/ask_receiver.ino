#include <RH_ASK.h>
#include <SPI.h> 


RH_ASK driver(2000, 2, 4, 5); 
 
void setup()
{
    Serial.begin(9600);	 
    if (!driver.init()){
      Serial.println("init failed");
    }
}

void loop()
{
    uint8_t buf[12];
    uint8_t buflen = sizeof(buf);
 String recv;
    if (driver.recv(buf, &buflen))
    {
      Serial.println((char*)buf);
    }
}
