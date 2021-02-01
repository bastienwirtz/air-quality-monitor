#include "VOCSensor.h"

VOCSensor::VOCSensor(gas_measurement *m) { this->measurement = m; }

bool VOCSensor::init() {
  if (!this->sgp.begin()) {
    return false;
  }
  // sgp.setIAQBaseline(0x8E68, 0x8F41);
  return true;
}

void VOCSensor::update() {
  this->sgp.IAQmeasure();
  this->measurement->tvoc = sgp.TVOC;
  this->measurement->eco2 = sgp.eCO2;
}
