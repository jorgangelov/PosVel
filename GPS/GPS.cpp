#include "GPS.h"

cPVEstimation::cPVEstimation()
{

}

void cPVEstimation::begin(unsigned long _current_time, tPosition _initial_position)
{
  PosVel.Position = _initial_position;
  time_of_last_step = _current_time;
}

tPVState cPVEstimation::getPVState(const tPosition& _position_measurement, unsigned long _current_time)
{
  tPVState Updated_State;
  float Kp = 4, Kd = 4;
  float dt = _current_time - time_of_last_step;



  return Updated_State;
}
