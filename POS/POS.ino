#include "TinyGPS++.h"
#include "COMM.h"
#include "GPS.h"
#include "Wire.h"
#include "PreCalibration.h"


TinyGPSPlus gps;
cSerial Uart;
cPVEstimation Estimator;
cVector<3> initial_LLA;
cVector<3> delta_NED;
bool isGPSvalid = false;

I2CPackage package;

unsigned long watchdog = 0;

char Buffer[600];
uint16_t num;

void setup()
{
  blink(2);
  preCalibrate();
  Wire.begin(42);
  Wire.onRequest(sendData);
    
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

  blink(15);

  // Waiting for Second FIX
  bool got_initial_pos = false;

  while ( !got_initial_pos)
  {
    if (Uart.getData(Buffer) )
    {
      // Parsing
      char* gpsStream = Buffer;
      while (*gpsStream)
      {
        gps.encode(*(gpsStream++));
      }
      if (gps.location.isUpdated())
      {
        got_initial_pos = true;
      }

    }

  }

  initial_LLA(1) = gps.location.lat();
  initial_LLA(2) = gps.location.lng();
  initial_LLA(3) = gps.altitude.meters();
  Estimator.begin(millis());



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
      if (isGPSvalid = gps.location.isUpdated())
      {
        watchdog = 0;
        delta_NED(1) = (gps.location.lat() - initial_LLA(1)) * (PI / 180) * EARTH_RADIUS_M;
        delta_NED(2) = (gps.location.lng() - initial_LLA(2)) * (PI / 180) * EARTH_RADIUS_M;
        delta_NED(3) = (gps.altitude.meters() - initial_LLA(3));
        isGPSvalid = true;
      }
      else
      {
        isGPSvalid = false;
      }

    }
    else
    {
      watchdog++;
      if (watchdog > 5000)
        isGPSvalid = false;
    }




    Estimator.update(millis(), delta_NED);

    cli();
    package.delta_NED_readyTosend[0] = Estimator.PosVel.Position(1);
    package.delta_NED_readyTosend[1] = Estimator.PosVel.Position(2);
    package.delta_NED_readyTosend[2] = Estimator.PosVel.Position(3);
    package.delta_UVW_readyTosend[0] = Estimator.PosVel.Velocity(1);
    package.delta_UVW_readyTosend[1] = Estimator.PosVel.Velocity(2);
    package.delta_UVW_readyTosend[2] = Estimator.PosVel.Velocity(3);
    package.isGPSvalid_readyTosend = isGPSvalid;
    sei();
    if (isGPSvalid)
    {
      PORTB |= (1 << PORTB5);
    }
    else
    {
      PORTB &= ~(1 << PORTB5);
    }

  }




}

void loop()
{
}

void sendData()
{
  Wire.write((uint8_t*)&package, sizeof(package));
}
