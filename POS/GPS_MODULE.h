#include "COMM.h"
#include "myMATH.h"

class cNEO
{
public:
    cSerial Uart;
    cVector<3> position_measurement;
    unsigned long time;

    void begin();
    void update();
    bool isGPSavailable();

};
