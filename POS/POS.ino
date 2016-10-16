#include "TinyGPS++.h"
#include "COMM.h"
#include "GPS.h"

TinyGPSPlus gps;
cSerial Uart;
cPVEstimation Estimator;
cVector<3> initial_LLA;
cVector<3> delta_NED;


char Buffer[1000];
uint16_t num;

void setup()
{
  Uart.begin();
  Serial.println("Waiting for GPS...");

  // Waiting for first FIX
  while ( !gps.location.isValid() )
  {

    if (Uart.getData(Buffer) )
    {
      // Parsing
      char* gpsStream = Buffer;
      while (*gpsStream)
      {
        gps.encode(*(gpsStream++));
      }

    }
  }


  Serial.println("FOUND GPS!");
  blink(10);

  // Waiting for Second FIX
  while ( !gps.location.isValid() )
  {

    if (Uart.getData(Buffer) )
    {
      // Parsing
      char* gpsStream = Buffer;
      while (*gpsStream)
      {
        gps.encode(*(gpsStream++));
      }

    }
  }

  initial_LLA(1) = gps.location.lat();
  initial_LLA(2) = gps.location.lng();
  initial_LLA(3) = gps.altitude.meters();


  // Starting Loop
  while (1)
  {


    // New Data
    if (Uart.getData(Buffer) )
    {
      // Parsing
      char* gpsStream = Buffer;
      while (*gpsStream)
      {
        gps.encode(*(gpsStream++));
      }

      // Check if valid Position
      if (gps.location.isValid())
      {
        delta_NED(1) = (gps.location.lat() - initial_LLA(1)) * (PI / 180) * EARTH_RADIUS_M;
        delta_NED(2) = (gps.location.lng() - initial_LLA(2)) * (PI / 180) * EARTH_RADIUS_M;
        delta_NED(3) = (gps.altitude.meters() - initial_LLA(3));
      }

    }
    Estimator.update(millis(), delta_NED);

    static int i = 0;
    i++;
    if (i > 500)
    {
      displayInfo();
      i = 0;
    }


  }




}

void loop()
{
}

void displayInfo()
{
  Serial.print("x: ");
  Serial.print(Estimator.PosVel.Position(1));
  Serial.print(" y: ");
  Serial.print(Estimator.PosVel.Position(2));
  Serial.print(" z: ");
  Serial.print(Estimator.PosVel.Position(3));
  Serial.print(" u: ");
  Serial.print(Estimator.PosVel.Velocity(1));
  Serial.print(" v: ");
  Serial.print(Estimator.PosVel.Velocity(2));
  Serial.print(" w: ");
  Serial.println(Estimator.PosVel.Velocity(3));


}
