#ifndef UI_STATE_H
#define UI_STATE_H

#include <Arduino.h>

enum ScreenMode { MODE_TIME, MODE_SENSOR, MODE_SET };
enum SensorFocus { FOCUS_MOON, FOCUS_TEMP, FOCUS_COMPASS };

struct UiState {
  ScreenMode mode = MODE_TIME;
  SensorFocus focus = FOCUS_MOON;

  uint8_t hour = 10;
  uint8_t minute = 28;
  uint8_t second = 45;

  float tempC = 24.3f;
  float compassDeg = 248.0f;
  float smoothCompass = 248.0f;
  float moonIllum = 63.0f;

  bool alarmOn = true;
  bool sigOn = true;
  bool btOn = false;
  uint8_t batteryPct = 72;

  bool invertBlink = false;
};

#endif

