#include "PMSensor.h"
#include "VOCSensor.h"
#include <sps30.h>

#ifndef AQM_CONTEXT
#define AQM_CONTEXT

struct Context {
  aqi_measurement AQI;
  gas_measurement gas;
};

#endif
