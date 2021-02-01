#include "PMSensor.h"
#include <Arduino.h>

PMSensor::PMSensor(sps30_measurement *m, aqi_measurement *aqi) {
  this->measurement = m;
  this->aqi = aqi;
}

bool PMSensor::init() {
  sensirion_i2c_init();
  int8_t timeout = 5;
  while (sps30_probe() != 0 && timeout > 0) {
    // SPS sensor probing failed
    timeout--;
    delay(1500);
  }

  if (sps30_probe() != 0) {
    return false;
  }

  // Auto clean every 4 days
  sps30_set_fan_auto_cleaning_interval_days(4);

  // Initialisation is successful if able to get a measurement
  return sps30_start_measurement() == 0;
}

void PMSensor::update() {
  sps30_read_measurement(this->measurement);
  this->aqi->aqi_1p0 = this->getAQI(this->measurement->mc_1p0);
  this->aqi->aqi_2p5 = this->getAQI(this->measurement->mc_2p5);
  this->aqi->aqi_4p0 = this->getAQI(this->measurement->mc_4p0);
  this->aqi->aqi_10p0 = this->getAQI(this->measurement->mc_10p0);
}

AQI PMSensor::getAQI(float concentration) {
  float cLow = 0.0;
  float cHi = 0.0;
  int16_t aqiLow = 0;
  int16_t aqiHi = 0;
  char *libelle = "";
  int color;

  if (concentration <= 12.0) {
    cLow = 0.0;
    cHi = 12.0;
    aqiLow = 0;
    aqiHi = 50;
    libelle = "Good";
    color = 0x07E0;
  } else if (concentration <= 35.4) {
    cLow = 12.1;
    cHi = 35.5;
    aqiLow = 51;
    aqiHi = 100;
    libelle = "Moderate";
    color = 0xFFE0;
  } else if (concentration <= 55.4) {
    cLow = 35.5;
    cHi = 55.4;
    aqiLow = 101;
    aqiHi = 150;
    libelle = "Unhealthy (Sensitive Groups)";
    color = 0xFDA0;
  } else if (concentration <= 150.4) {
    cLow = 55.5;
    cHi = 150.4;
    aqiLow = 151;
    aqiHi = 200;
    libelle = "Unhealthy";
    color = 0xF800;
  } else if (concentration <= 250.4) {
    cLow = 150.5;
    cHi = 250.4;
    aqiLow = 201;
    aqiHi = 300;
    libelle = "Very Unhealthy";
    color = 0x915C;
  } else {
    cLow = 250.5;
    cHi = 500.4;
    aqiLow = 301;
    aqiHi = 500;
    libelle = "Hazardous";
    color = 0x7800;
  }

  AQI aqi;
  aqi.value = ((aqiHi - aqiLow) / (cHi - cLow)) * (concentration - cLow) + aqiLow;
  aqi.libelle = libelle;
  aqi.color = color;

  if (aqi.value > 500) {
    aqi.value = 500;
  }

  return aqi;
}
