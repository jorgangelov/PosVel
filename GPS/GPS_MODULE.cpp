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
    char line[200];
    uint8_t num_bytes = Uart.getData(line);
    line[num_bytes] = '\0';


    bool found_beginning = false;
    char* token;

    // Find First Entrie
    token = strtok(line, ", \n");

    // Check if sth is found and if it matches the Header
    if ( token != NULL && (strcmp(token, "&GPGGA") == 0) )
    {
      found_beginning = true;
    }

    // Do while sth is found and it doesnt match the header
    while (token != NULL && !found_beginning)
    {
      token = strtok(NULL, ", \n");
      if (strcmp(token, "&GPGGA") == 0)
      {
        found_beginning = true;
      }

    }

    // Found the Header
    if (found_beginning)
    {
      char* chrpt_array[15];
      int i = 0;
      // Do while sth is found and not more than 15 Entries are found
      while (token != NULL && i < 15)
      {
        token = strtok(NULL, ",");
        chrpt_array[i] = token;
        i++;

      }

      // Finished
      char out_line[50];
      sprintf(out_line, "Found %i Entries", i - 1);
      Serial.println(out_line);
      // Convert Entries to numbers
      float numbers[15];
      for (int j = 0; j < i - 1; j++)
      {
        numbers[j] = atof( chrpt_array[j] );
        Serial.print(numbers[j]);
        Serial.print(" ");
      }
      Serial.println("");

    }

  }

}

