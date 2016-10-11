#include "GPS_MODULE.h"


void cNEO::begin()
{
    Uart.begin();
    Serial.println("GPS Module Started!");
}
