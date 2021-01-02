#include <WiFi.h>
#include <Button2.h>;
#include <esp_adc_cal.h>
#include <sps30.h>
#include "Screen.h"

#define BUTTON_1 35
#define BUTTON_2 0

Screen screen = Screen(); 
Button2 btnTop(BUTTON_1);
Button2 btnBottom(BUTTON_2);

const char *WIFI_SSID = "";
const char *WIFI_PASSWORD = "";

unsigned long previousTick = 0;
const long readInterval = 15000; // 15s


void setup()
{
    screen.showSplash();

    setButtonsHandler();
    wifiConnect();
    initialiseParticleSensor();

    screen.setView(SCREEN_PM25);
    screen.refresh();
}

void loop()
{
    btnTop.loop();
    btnBottom.loop();

    // Data update loop
    unsigned long currentTick = millis();
    if (currentTick - previousTick >= readInterval) {
        // save the last time you blinked the LED
        previousTick = currentTick;

        struct sps30_measurement m;
        sps30_read_measurement(&m);

        screen.setPmConcentration(m.mc_1p0, m.mc_2p5, m.mc_4p0, m.mc_10p0);
        screen.refresh();
    }
    delay(5);
}

void setButtonsHandler()
{
    btnTop.setPressedHandler([](Button2 &b) {
        screen.nextView();
        screen.refresh();
    });

    btnBottom.setPressedHandler([](Button2 &b) {
        screen.toggleBacklight();
    });
}

void wifiConnect()
{
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    WiFi.disconnect();
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

    int8_t timeout = 5;
    while (WiFi.status() != WL_CONNECTED && timeout > 0) 
    {
        // Loop until the connection is established
        timeout--;
        delay(1000);
    }
}

void initialiseParticleSensor()
{
    sensirion_i2c_init();
    int8_t timeout = 5;
    while (sps30_probe() != 0 && timeout > 0)
    {
        // SPS sensor probing failed
        timeout--;
        delay(500);
    }

    // Auto clean every 4 days
    if (sps30_set_fan_auto_cleaning_interval_days(4))
    {
        // error setting the auto-clean interval
    }

    if (sps30_start_measurement() < 0)
    {
        // error starting measurement
    }

    /* start measurement and wait for 10s to ensure the sensor has a
     * stable flow and possible remaining particles are cleaned out */
    delay(10000);
}
