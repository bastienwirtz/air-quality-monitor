#include <Arduino.h>
#include <TFT_eSPI.h>
#include "Context.h"

#ifndef AQM_SCREEN
#define AQM_SCREEN

// Display pinout setup
#ifndef TFT_DISPOFF
#define TFT_DISPOFF 0x28
#endif

#ifndef TFT_SLPIN
#define TFT_SLPIN 0x10
#endif

#define TFT_WIDTH  135
#define TFT_HEIGHT 240

#define TFT_MOSI 19
#define TFT_SCLK 18
#define TFT_CS 5
#define TFT_DC 16
#define TFT_RST 23

#define TFT_BL 4  // Display backlight control pin
#define ADC_EN 14 // ADC_EN is the ADC detection enable port
#define ADC_PIN 34

const uint8_t TOTAL_SCREEN = 3;
const uint8_t SCREEN_PM25 = 0;
const uint8_t SCREEN_PMALL = 1;
const uint8_t SCREEN_STATUS = 2;

class Screen {
    private:
        // Screen management
        TFT_eSPI tft = TFT_eSPI(TFT_WIDTH, TFT_HEIGHT);
        int16_t h;
        int16_t w;
        uint8_t currentView = 0;

        // View data binding
        Context* context;
        
    public:
        Screen(struct Context* context);
        void setView(uint8_t view);
        void nextView();
        void refresh();
        void toggleBacklight();
        void waitForIt(char* message, int8_t seconds);

        // Views
        void showSplash(char* libelle, int8_t counter = -1);
        void showError(char* message);
        void showMainConcentration();
        void showAllConcentration();
        void showStatus();
};

#endif
