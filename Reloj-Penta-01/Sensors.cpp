
#include "Sensors.h"
#include <OneWire.h>
#include <DallasTemperature.h>


#define DS18B20_PIN 4

OneWire oneWire(DS18B20_PIN);
DallasTemperature ds18b20(&oneWire);

static unsigned long tTemp = 0;
static unsigned long tCompass = 0;
static unsigned long tMoon = 0;
static const float kCompassAlpha = 0.2f;


void initSensors() {
  
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }

  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);

  ds18b20.begin();
}
float getMoonPhase();
void updateSensors(UiState &ui, unsigned long nowMs) {
  if (nowMs - tTemp >= 5000) {
    tTemp = nowMs;
    ds18b20.requestTemperatures();

    float t = ds18b20.getTempCByIndex(0);

    if (t != DEVICE_DISCONNECTED_C) {
     ui.tempC = t;
    }
  }

  if (nowMs - tCompass >= 125) {
    tCompass = nowMs;
    // Placeholder heading real.
    ui.compassDeg += 1.5f;
    if (ui.compassDeg >= 360.0f) ui.compassDeg -= 360.0f;
    ui.smoothCompass = kCompassAlpha * ui.compassDeg + (1.0f - kCompassAlpha) * ui.smoothCompass;
  }

  if (nowMs - tMoon >= 3600000UL) {
    tMoon = nowMs;
    // Placeholder fase lunar real (recalculo horario).
    ui.moonIllum = getMoonPhase();
  }
}

void tickClock(UiState &ui) {
  ui.second++;
  if (ui.second >= 60) {
    ui.second = 0;
    ui.minute++;
    if (ui.minute >= 60) {
      ui.minute = 0;
      ui.hour = (ui.hour + 1) % 24;
    }
  }
}

const char *cardinalFromDegrees(float deg) {
  static const char *dirs[] = {"N", "NE", "E", "SE", "S", "SW", "W", "NW"};
  int idx = static_cast<int>((deg + 22.5f) / 45.0f) % 8;
  return dirs[idx];
}

