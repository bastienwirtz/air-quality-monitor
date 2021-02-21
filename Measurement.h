#ifndef AQM_MEASUREMENT
#define AQM_MEASUREMENT

struct measurement {
  int value = 0;
  char *libelle = "unknown";
  int color = 0xD69A;
  float rawValue = 0.0;
};

#endif
