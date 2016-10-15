#include "GPS.h"
#include "GPS_MODULE.h"

cNEO NEO;
cSerial SER;
cPVEstimation Estimator;

void setup() {

  blink(3);
  NEO.begin();
  Estimator.begin(millis(), NEO.position_measurement);

}

void loop() {

  NEO.update();
  Estimator.update(millis(), NEO.position_measurement);
  if (Estimator.PosVel.Position(1) != 0)
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


}
