#include "GPS.h"
#include "GPS_MODULE.h"

cNEO NEO;
cSerial SER;
cPVEstimation Estimator;

void setup() {

  NEO.begin();
  // Wait for GPS
  while (NEO.isGPSavailable == false)
  {
  NEO.update();
  }

  // GPS Found
  Serial.println("GPS Found!");
  blink(2);

  // INIT Esrimator
  Estimator.begin(millis(), NEO.position_measurement);

  // Start Estimating
  bool EstimationActive = true;
  while (EstimationActive)
  {
    NEO.update();
    Estimator.update(millis(),(NEO.position_measurement-Estimator.Init_Pos));
    
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

void loop() {

}
