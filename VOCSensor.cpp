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
  this->updateVOCRange();
  this->updateCO2Range();
}

void VOCSensor::updateVOCRange() {
  // VOC range from https://www.airthings.com/what-is-voc
  this->measurement->tvoc.value = this->sgp.TVOC;
  if (this->sgp.TVOC < 250) {
    this->measurement->tvoc.libelle = "Low";
    this->measurement->tvoc.color = 0x07E0;
  } else if (this->sgp.TVOC < 2000) {
    this->measurement->tvoc.libelle = "Moderate";
    this->measurement->tvoc.color = 0xFFE0;
  } else {
    this->measurement->tvoc.libelle = "High";
    this->measurement->tvoc.color = 0xF800;
  }
}

void VOCSensor::updateCO2Range() {
  // CO2 Range from https://www.kane.co.uk/knowledge-centre/what-are-safe-levels-of-co-and-co2-in-rooms
  this->measurement->eco2.value = this->sgp.eCO2;
  if (this->sgp.eCO2 < 500) {
    this->measurement->eco2.libelle = "Normal";
    this->measurement->eco2.color = 0x07E0;
  } else if (this->sgp.eCO2 < 1000) {
    this->measurement->eco2.libelle = "Fair";
    this->measurement->eco2.color = 0xFFE0;
  } else if (this->sgp.eCO2 < 2000) {
    this->measurement->eco2.libelle = "High";
    this->measurement->eco2.color = 0xFDA0;
  } else if (this->sgp.eCO2 < 5000) {
    this->measurement->eco2.libelle = "Very high";
    this->measurement->eco2.color = 0xF800;
  } else {
    this->measurement->eco2.libelle = "Dangerous";
    this->measurement->eco2.color = 0x7800;
  }
}
