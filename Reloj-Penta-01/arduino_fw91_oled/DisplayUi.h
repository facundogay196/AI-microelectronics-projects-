#ifndef DISPLAY_UI_H
#define DISPLAY_UI_H

#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "UiState.h"

void drawScreen(Adafruit_SSD1306 &display, const UiState &ui, unsigned long nowMs);

#endif

