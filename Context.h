#include "PMSensor.h"
#include "VOCSensor.h"
#include <sps30.h>

#ifndef AQM_CONTEXT
#define AQM_CONTEXT

// Contain app state, sensors values, device status, ...
struct Context {
  sps30_measurement particleMatter;
  aqi_measurement AQI;
  gas_measurement gas;
};

#endif
