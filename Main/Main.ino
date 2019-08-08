#include "SmartHomeDevice.h"

#define SERIAL_SPEED 9600

void setup() 
{
    pinMode(2, OUTPUT);
    Serial.begin(SERIAL_SPEED);
}

void loop() 
{
    static bool state = false;

    if (!state)
    {
        digitalWrite(2, HIGH);
        state = true;
    }
    else
    {
        digitalWrite(2, LOW);
        state = false;
    }
  
    int availableSerialBytes = Serial.available();
    
    if (availableSerialBytes > 0)
    {
        char *buff = new char[availableSerialBytes];
        memset(buff, 0, availableSerialBytes);

        for (int i = 0; i < availableSerialBytes; i++)
            buff[i] = Serial.read();

        Serial.print("Received data from serial port: ");
        Serial.println(buff);
    }
    
    Serial.println("ESP8266 ready to go v2.0!");
    delay(1000);
}
