#include "Screen.h"

Screen::Screen()
{
    this->tft.init();
    this->tft.setRotation(1);
    this->tft.setTextSize(2);

    this->w = this->tft.width();
    this->h = this->tft.height();

    // TFT_BL has been set in the TFT_eSPI library in the User Setup file TTGO_T_Display.h
    pinMode(TFT_BL, OUTPUT);
    digitalWrite(TFT_BL, HIGH);
}

void Screen::toggleBacklight()
{
    digitalWrite(TFT_BL, !digitalRead(TFT_BL));
}

void Screen::nextView()
{
    this->currentView++;
    if (this->currentView == TOTAL_SCREEN)
    {
        this->currentView = 0;
    }
}

void Screen::setView(uint8_t view)
{
    this->currentView = view;
}

void Screen::refresh()
{
    switch (this->currentView) {
        case SCREEN_STATUS:
            this->showStatus();
            break;
        case SCREEN_PM25:
            this->showMainConcentration();
            break;
        case SCREEN_PMALL:
            this->showAllConcentration();
            break;
    }
}

// Data binding
void Screen::setPmConcentration(float pm1, float pm2_5, float pm4, float pm10)
{
    this->pm1 = pm1;
    this->pm2_5 = pm2_5;
    this->pm4 = pm4;
    this->pm10 = pm10;
}

// Views
void Screen::showSplash()
{
    this->tft.fillScreen(TFT_RED);
    this->tft.setTextColor(TFT_WHITE, TFT_RED);
    this->tft.drawCentreString("Initialization...", (this->w/2)-24, this->h/2, 2);
}

void Screen::showMainConcentration()
{
    this->tft.fillScreen(TFT_BLACK);
    this->tft.setTextColor(TFT_WHITE, TFT_BLACK);
    
    tft.setCursor(10, 10);
    tft.print("PM2.5: ");
    tft.print(this->pm2_5);
    tft.println("ug/m3");
}

void Screen::showAllConcentration()
{
    this->tft.fillScreen(TFT_BLACK);
    this->tft.setTextColor(TFT_WHITE, TFT_BLACK);
    
    tft.setCursor(0, 0);
    tft.print("PM1: ");
    tft.println(this->pm1);
    tft.print("PM2.5: ");
    tft.println(this->pm2_5);
    tft.print("PM4: ");
    tft.println(this->pm4);
    tft.print("PM10: ");
    tft.println(this->pm10);
}

void Screen::showStatus()
{
    this->tft.fillScreen(TFT_GREENYELLOW);
    this->tft.setTextDatum(TL_DATUM);
    tft.setCursor(0, 60);
    tft.println("Status");
}
