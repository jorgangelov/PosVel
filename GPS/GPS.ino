#include "GPS.h"
#include "GPS_MODULE.h"

cNEO NEO;
cSerial SER;


void setup() {

blink(3);  
NEO.begin();

}

void loop() {
NEO.update();
//SER.show();
//Serial.println("bla");
}
