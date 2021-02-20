#include "Screen.h"

Screen::Screen(Context *context) {
  this->tft.init();
  this->tft.setRotation(1);
  this->tft.setTextSize(2);
  this->w = this->tft.width();
  this->h = this->tft.height();
  this->context = context;

  // TFT_BL has been set in the TFT_eSPI library in the User Setup file TTGO_T_Display.h
  pinMode(TFT_BL, OUTPUT);
  digitalWrite(TFT_BL, HIGH);
}

void Screen::toggleBacklight() { digitalWrite(TFT_BL, !digitalRead(TFT_BL)); }

void Screen::nextView() {
  this->currentView++;
  if (this->currentView == TOTAL_SCREEN) {
    this->currentView = 0;
  }
}

void Screen::waitForIt(char *message, int8_t seconds) {
  for (int8_t i = seconds; i >= 1; i--) {
    if (i < 3) {
      this->showSplash("Almost there...", i);
    } else {
      this->showSplash(message, i);
    }
    delay(1000);
  }
}

void Screen::setView(uint8_t view) { this->currentView = view; }

void Screen::refresh() {
  switch (this->currentView) {
  case SCREEN_PM25:
    this->showMainConcentration();
    break;
  case SCREEN_ECO2:
    this->showeco2();
    break;
  case SCREEN_TVOC:
    this->showtvoc();
    break;
  case SCREEN_ALL:
    this->showAllData();
    break;
  }
}

// Views
void Screen::showSplash(char *libelle, int8_t counter) {
  this->tft.fillScreen(TFT_DARKCYAN);
  this->tft.setTextColor(TFT_WHITE, TFT_DARKCYAN);
  this->tft.setTextDatum(MC_DATUM);
  int8_t ypos = this->h / 2;
  if (counter >= 0) {
    this->tft.setTextSize(3);
    this->tft.drawString(String(counter), this->w / 2, ypos - 15, 1);
    ypos += 15;
  }
  this->tft.setTextSize(1);
  this->tft.drawString(libelle, this->w / 2, ypos, 1);
}

void Screen::showError(char *message) {
  this->tft.fillScreen(TFT_RED);
  this->tft.setTextColor(TFT_WHITE, TFT_RED);
  this->tft.setTextDatum(MC_DATUM);
  this->tft.setTextSize(2);
  this->tft.drawString(message, this->w / 2, this->h / 2, 1);
}

void Screen::showMainConcentration() {
  this->tft.fillScreen(TFT_BLACK);
  this->tft.setTextColor(TFT_WHITE, TFT_BLACK);

  this->tft.setTextSize(6);
  this->tft.setTextDatum(TL_DATUM);
  this->tft.drawString(String(this->context->AQI.aqi_2p5.value), 10, 10, 1);

  this->tft.setTextSize(4);
  this->tft.setTextDatum(TR_DATUM);
  this->tft.drawString("AQI", this->w, 10, 1);

  this->tft.setTextSize(2);
  this->tft.setTextDatum(BR_DATUM);
  this->tft.drawString("PM2.5", this->w, this->h, 1);

  this->tft.setTextDatum(BL_DATUM);
  this->tft.fillCircle(18, this->h - 35, 8, this->context->AQI.aqi_2p5.color);
  this->tft.drawString(this->context->AQI.aqi_2p5.libelle, 35, this->h - 25, 1);
  this->tft.drawString(String(this->context->particleMatter.mc_2p5) + "ug/m3", 10, this->h, 1);
}

void Screen::showeco2() {
  this->tft.fillScreen(TFT_BLACK);
  this->tft.setTextColor(TFT_WHITE, TFT_BLACK);

  this->tft.setTextSize(6);
  this->tft.setTextDatum(TL_DATUM);
  this->tft.drawString(String(this->context->gas.eco2.value), 10, 10, 1);

  this->tft.setTextSize(4);
  this->tft.setTextDatum(TR_DATUM);
  this->tft.drawString("eCO2", this->w, 10, 1);

  this->tft.setTextSize(2);
  this->tft.setTextDatum(BR_DATUM);
  this->tft.drawString("ppm", this->w, this->h, 1);

  this->tft.setTextDatum(BL_DATUM);
  this->tft.fillCircle(18, this->h-10, 8, this->context->gas.eco2.color);
  this->tft.drawString(this->context->gas.eco2.libelle, 35, this->h, 1);
}

void Screen::showtvoc() {
  this->tft.fillScreen(TFT_BLACK);
  this->tft.setTextColor(TFT_WHITE, TFT_BLACK);

  this->tft.setTextSize(6);
  this->tft.setTextDatum(TL_DATUM);
  this->tft.drawString(String(this->context->gas.tvoc.value), 10, 10, 1);

  this->tft.setTextSize(4);
  this->tft.setTextDatum(TR_DATUM);
  this->tft.drawString("TVOC", this->w, 10, 1);

  this->tft.setTextSize(2);
  this->tft.setTextDatum(BR_DATUM);
  this->tft.drawString("ppb", this->w, this->h, 1);

  this->tft.setTextDatum(BL_DATUM);
  this->tft.fillCircle(18, this->h-10, 8, this->context->gas.tvoc.color);
  this->tft.drawString(this->context->gas.tvoc.libelle, 35, this->h, 1);
}

void Screen::showAllData() {
  this->tft.fillScreen(TFT_BLACK);
  this->tft.setTextColor(TFT_WHITE, TFT_BLACK);
  this->tft.setTextFont(1);
  uint8_t currentLineTop = 10;
  uint8_t lineGap = 5;

  this->tft.setTextDatum(MC_DATUM);
  this->tft.setTextSize(2);
  int8_t ypos = this->h / 2;
  this->tft.drawString("Everything!", this->w / 2, 10);
  currentLineTop += 10;

  this->tft.setTextDatum(TL_DATUM);
  this->tft.setTextSize(1);
  uint8_t lineHeight = this->tft.fontHeight();

  currentLineTop += lineHeight + lineGap;
  this->tft.fillCircle(14, currentLineTop + 2, 4, this->context->AQI.aqi_1p0.color);
  this->tft.drawString("PM1: " + String(this->context->AQI.aqi_1p0.value) + " (" +
                           String(this->context->particleMatter.mc_1p0) + "ug/m3)",
                       25, currentLineTop);

  currentLineTop += lineHeight + lineGap;
  this->tft.fillCircle(14, currentLineTop + 2, 4, this->context->AQI.aqi_2p5.color);
  this->tft.drawString("PM2.5: " + String(this->context->AQI.aqi_2p5.value) + " (" +
                           String(this->context->particleMatter.mc_2p5) + "ug/m3)",
                       25, currentLineTop);

  currentLineTop += lineHeight + lineGap;
  this->tft.fillCircle(14, currentLineTop + 2, 4, this->context->AQI.aqi_4p0.color);
  this->tft.drawString("PM4: " + String(this->context->AQI.aqi_4p0.value) + " (" +
                           String(this->context->particleMatter.mc_4p0) + "ug/m3)",
                       25, currentLineTop);

  currentLineTop += lineHeight + lineGap;
  this->tft.fillCircle(14, currentLineTop + 2, 4, this->context->AQI.aqi_10p0.color);
  this->tft.drawString("PM10: " + String(this->context->AQI.aqi_10p0.value) + " (" +
                           String(this->context->particleMatter.mc_10p0) + "ug/m3)",
                       25, currentLineTop);

  currentLineTop += lineHeight + lineGap;
  this->tft.fillCircle(14, currentLineTop + 2, 4, this->context->gas.tvoc.color);
  this->tft.drawString("TVOC: " + String(this->context->gas.tvoc.value), 25, currentLineTop);

  currentLineTop += lineHeight + lineGap;
  this->tft.fillCircle(14, currentLineTop + 2, 4, this->context->gas.eco2.color);
  this->tft.drawString("eCO2: " + String(this->context->gas.eco2.value), 25, currentLineTop);
}
