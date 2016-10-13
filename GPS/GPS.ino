#include "GPS.h"
#include "GPS_MODULE.h"

cNEO NEO;
cSerial SER;
cPVEstimation Estimator;

void setup() {

  blink(3);
  NEO.begin();
  Estimator.begin(millis(),NEO.position_measurement);

}

void loop() {
  NEO.update();
  Estimator.update(millis(),NEO.position_measurement);
  Serial.print("x: ");
  Serial.print(Estimator.PosVel.Position(1));
  Serial.print(" y: ");
  Serial.print(Estimator.PosVel.Position(2));
  Serial.print(" z: ");
  Serial.println(Estimator.PosVel.Position(3));

}
