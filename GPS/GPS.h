#ifndef GPS_H
#define GPS_H
#include <string.h>


struct tPosition
{
  tPosition()
  {
    memset(this, 0, sizeof(*this));
  }

  float x_I;
  float y_I;
  float z_I;
};



struct tVelocity
{
  tVelocity()
  {
    memset(this, 0, sizeof(*this));
  }
  float u_I;
  float v_I;
  float w_I;
};

struct tPVState
{
  tPosition Position;
  tVelocity Velocity;
};


class cPVEstimation
{
  public:
    cPVEstimation();
    void begin(unsigned long _current_time, tPosition _initial_position);
    tPVState getPVState(const tPosition& _position_measurement, unsigned long _current_time);

  private:
    unsigned long time_of_last_step;
    tPVState PosVel;
};













#endif
