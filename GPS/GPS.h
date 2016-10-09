#ifndef GPS_H
#define GPS_H
#include <string.h>
#include <stdio.h>
#include "myMATH.h"








struct tPVState
{
  cVector<3> Position;
  cVector<3> Velocity;
};


class cPVEstimation
{
  public:
    cPVEstimation();
    void begin(unsigned long _current_time, cVector<3>& _initial_position);
    void update(unsigned long _current_time, cVector<3>& _position_measurement);
    tPVState PosVel;

  private:
    unsigned long time_of_last_step;
};






cPVEstimation::cPVEstimation()
{

}

void cPVEstimation::begin(unsigned long _current_time, cVector<3>& _initial_position)
{
  PosVel.Position = _initial_position;
  time_of_last_step = _current_time;
}

void cPVEstimation::update(unsigned long _current_time, cVector<3> &_position_measurement)
{
  float Kp = 4, Kd = 4;
  float dt = _current_time - time_of_last_step;



}












#endif
