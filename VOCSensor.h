#include <Adafruit_SGP30.h>
#include <Wire.h>

#ifndef AQM_VOC
#define AQM_VOC

struct measurement {
  int16_t value = 0;
  char *libelle = "unknown";
  int color = 0xD69A;
};

struct gas_measurement {
  measurement tvoc;
  measurement eco2;
};

class VOCSensor {
private:
  Adafruit_SGP30 sgp;
  gas_measurement *measurement;
  void updateVOCRange();
  void updateCO2Range();

public:
  VOCSensor(gas_measurement *m);
  bool init();
  void update();
};

#endif
