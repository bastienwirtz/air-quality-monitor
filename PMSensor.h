#include "Measurement.h"
#include <sps30.h>

#ifndef AQM_PMS
#define AQM_PMS

struct aqi_measurement {
  measurement aqi_1p0;
  measurement aqi_2p5;
  measurement aqi_4p0;
  measurement aqi_10p0;
};

class PMSensor {
private:
  sps30_measurement pm;
  aqi_measurement *aqi;
  measurement getAQI(float concentration);

public:
  PMSensor(struct aqi_measurement *aqi);
  bool init();
  void update();
};

#endif
