#include <sps30.h>

#ifndef AQM_PMS
#define AQM_PMS

struct AQI
{
    int16_t value = 0;
    char* libelle = "unknown";
    int color = 0xD69A;
};

struct aqi_measurement
{
    AQI aqi_1p0;
    AQI aqi_2p5;
    AQI aqi_4p0;
    AQI aqi_10p0;
};

class PMSensor {
    private:
        sps30_measurement* measurement;
        aqi_measurement* aqi;
        AQI getAQI(float concentration);
        
    public:
        PMSensor(struct sps30_measurement* m, struct aqi_measurement* aqi);
        bool init();
        void update();
};

#endif
