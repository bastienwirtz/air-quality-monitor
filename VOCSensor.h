#include <Adafruit_SGP30.h>
#include <Wire.h>

#ifndef AQM_VOC
#define AQM_VOC

struct gas_measurement {
  uint16_t tvoc = 0;
  uint16_t eco2 = 0;
};

class VOCSensor {
private:
  Adafruit_SGP30 sgp;
  gas_measurement *measurement;

public:
  VOCSensor(gas_measurement *m);
  bool init();
  void update();
};

#endif
