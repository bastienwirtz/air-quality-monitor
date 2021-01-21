#include <sps30.h>
#include "PMSensor.h"

#ifndef AQM_CONTEXT
#define AQM_CONTEXT

// Contain app state, sensors values, device status, ...
struct Context 
{
    sps30_measurement particleMatter;
    aqi_measurement AQI;
};

#endif
