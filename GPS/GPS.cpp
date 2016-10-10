#include "GPS.h"




cPVEstimation::cPVEstimation()
{

}

void cPVEstimation::begin(unsigned long _current_time, cVector<3> _initial_position)
{
  PosVel.Position = _initial_position;
  time_of_last_step = _current_time;
}

void cPVEstimation::update(unsigned long _current_time, cVector<3> _position_measurement)
{
  float Kp = 4, Kd = 4;
  float dt = (_current_time - time_of_last_step)*0.001;
  
  cVector<3> e_pos = _position_measurement - PosVel.Position;
  
  PosVel.Velocity = PosVel.Velocity + dt*Kp*e_pos;
  PosVel.Position = PosVel.Position + dt*(PosVel.Velocity + Kd*e_pos);

  
}

