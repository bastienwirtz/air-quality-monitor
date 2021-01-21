#include <Button2.h>;
#include <esp_adc_cal.h>
#include <sps30.h>
#include "Screen.h"
#include "PMSensor.h"
#include "Cloud.h"
#include "Context.h"

Context context;
Screen screen = Screen(&context);
PMSensor pms = PMSensor(&context.particleMatter, &context.AQI);
Cloud cloud = Cloud("<ssid>", "<password>");

Button2 btnTop(35);
Button2 btnBottom(0);

unsigned long lastIntervalCheck = 0;
const long readInterval = 15000; // 15s

void setup()
{
    setButtonsHandler();
    screen.showSplash("Connecting WiFi");
    
    if (!cloud.connect()) {
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
        screen.setView(SCREEN_PM25);
        screen.refresh();
    }
}

void loop()
{
    btnTop.loop();
    btnBottom.loop();

    // Data update loop
    if (timesUp(readInterval)) {
        pms.update();
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

bool timesUp(long interval) {
    unsigned long currentCheck = millis();
    if (currentCheck - lastIntervalCheck >= readInterval) {
        lastIntervalCheck = currentCheck;
        return true;
    } else {
        return false;
    }
}
