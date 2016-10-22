#ifndef GPS_H
#define GPS_H
#include <string.h>
#include <stdio.h>
#include "myMATH.h"
#define EARTH_RADIUS_M 6371000
#define GPS_I2C_ID 42

struct tPVState
{
  cVector<3> Position;
  cVector<3> Velocity;
};


struct I2CPackage
{
I2CPackage():isGPSvalid_readyTosend(false)
  {

  }

volatile float delta_NED_readyTosend[3];
volatile float delta_UVW_readyTosend[3];
volatile bool isGPSvalid_readyTosend;
};


class cPVEstimation
{
  public:
    cPVEstimation();
    void begin(unsigned long _current_time);
    void update(unsigned long _current_time, cVector<3> _position_measurement);
    tPVState PosVel;

  private:
    unsigned long time_of_last_step;
};





#endif
