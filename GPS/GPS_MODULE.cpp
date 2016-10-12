#include "GPS_MODULE.h"


void cNEO::begin()
{
    Uart.begin();
    Serial.println("GPS Module Started!");
}


void cNEO::update()
{
  if (Uart.available())
  {
      char line[200];
      uint8_t num_bytes = Uart.getData(line);
      line[num_bytes] = '\0';
      
      char* token;
      token = strtok(line,",");
      while(token != NULL)
      {
      if (*token == "$GPGGA")
        {
            
        }
      token = strtok(NULL,",");
      }
 
      

  }

}

