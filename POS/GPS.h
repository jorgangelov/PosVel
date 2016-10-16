#ifndef GPS_H
#define GPS_H
#include <string.h>
#include <stdio.h>
#include "myMATH.h"
#define EARTH_RADIUS_M 6371000


struct tPVState
{
  cVector<3> Position;
  cVector<3> Velocity;
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
