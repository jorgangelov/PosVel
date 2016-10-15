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
    // Read Buffer
    char line[500];
    uint8_t num_bytes = Uart.getData(line);
    line[num_bytes] = '\0';


    bool found_beginning = false;
    char* token;

    // Find First Entrie
    token = strtok(line, ", \n");

    // Check if sth is found and if it matches the Header
    if ( token != NULL && (strcmp(token, "$GPGGA") == 0) )
    {
      found_beginning = true;
    }

    // Do while sth is found and it doesnt match the header
    while (token != NULL && !found_beginning)
    {
      token = strtok(NULL, ", \n");
      if (strcmp(token, "$GPGGA") == 0)
      {
        found_beginning = true;
      }

    }

    // Found the Header
    if (found_beginning)
    {
      float numbers[15];
      int i = 0;
      // Do while sth is found and not more than 15 Entries are found
      while (token != NULL && i < 15 && strcmp(token,"$GPGSA") != 0)
      {
        token = strtok(NULL,",\n");
        numbers[i] = atof(token);
        i++;
      }

      if (i >= 14)
      {
        position_measurement(1) = numbers[1];
        position_measurement(2) = numbers[3];
        position_measurement(3) = numbers[8];
      }
    }

  }

}

