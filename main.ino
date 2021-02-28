#include <Button2.h>;
#include <esp_adc_cal.h>
#include "Screen.h"
#include "PMSensor.h"
#include "VOCSensor.h"
#include "Cloud.h"
#include "Context.h"

// Configuration
char* wifiSsid = "";
char* wifiPassword = "";
char* mqttServer = "";
char* mqttUser = "";
char* mqttPassword = "";

Context context;
Screen screen = Screen(&context);
PMSensor pms = PMSensor(&context.AQI);
VOCSensor voc = VOCSensor(&context.gas);
Cloud cloud = Cloud(deviceName, wifiSsid, wifiPassword, mqttServer, mqttUser, mqttPassword);

Button2 btnTop(35);
Button2 btnBottom(0);

unsigned long lastIntervalCheck = 0;
const long readInterval = 15000; // 15s

void setup()
{
    screen.showSplash("Connecting WiFi");
    if (!cloud.connect()) {
        screen.showError("Fail!");
        delay(500);
    }

    screen.showSplash("Initialise gas sensor");
    delay(500);
    if (!voc.init()) {
        screen.showError("Fail!");
        delay(500);
    }

    screen.showSplash("Initialise particle sensor");
    if (!pms.init()) {
        screen.showError("Fail!");
        delay(500);
    } else {
        /* start measurement and wait for 10s to ensure the sensor has a
        * stable flow and possible remaining particles are cleaned out */
        screen.waitForIt("Cleaning extra dust", 10);
        pms.update();
    }

    setButtonsHandler();
    screen.setView(SCREEN_PM25);
    screen.refresh();
}

void loop()
{
    btnTop.loop();
    btnBottom.loop();

    // Data update loop
    if (timesUp(readInterval)) {
        pms.update();
        voc.update();
        screen.refresh();
        cloud.send("home/livingroom/airquality", formatCloudData().c_str());
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

bool timesUp(long interval) {
    unsigned long now = millis();
    if (now - lastIntervalCheck >= readInterval) {
        lastIntervalCheck = now;
        return true;
    } else {
        return false;
    }
}

String formatCloudData() {
    char cloudDataBuffer[355];
    sprintf(cloudDataBuffer, "{"
            "\"tvoc\":%d,"
            "\"eco2\":%d,"
            "\"mc_1p0\":%f,"
            "\"mc_2p5\":%f,"
            "\"mc_4p0\":%f,"
            "\"mc_10p0\":%f,"
            "\"aqi_1p0\":%d,"
            "\"aqi_2p5\":%d,"
            "\"aqi_4p0\":%d,"
            "\"aqi_10p0\":%d,"
            "\"aqi_main_value\":%d,"
            "\"aqi_main_libelle\":\"%s\""
        "}",
            context.gas.tvoc.value,
            context.gas.eco2.value,
            context.AQI.aqi_1p0.rawValue,
            context.AQI.aqi_2p5.rawValue,
            context.AQI.aqi_4p0.rawValue,
            context.AQI.aqi_10p0.rawValue,
            context.AQI.aqi_1p0.value,
            context.AQI.aqi_2p5.value,
            context.AQI.aqi_4p0.value,
            context.AQI.aqi_10p0.value,
            context.AQI.aqi_2p5.value,
            context.AQI.aqi_2p5.libelle
    );
    return String(cloudDataBuffer);
} 
