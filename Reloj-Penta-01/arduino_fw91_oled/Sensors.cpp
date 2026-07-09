
#include "Sensors.h"
#include <OneWire.h>
#include <DallasTemperature.h>
#include <time.h>
float getMoonPhase();
#define DS18B20_PIN 4

OneWire oneWire(DS18B20_PIN);
DallasTemperature ds18b20(&oneWire);

static unsigned long tTemp = 0;
static unsigned long tCompass = 0;
static unsigned long tMoon = 0;
static bool moonInitialized = false;
static const float kCompassAlpha = 0.2f;


void initSensors() {
  
  ds18b20.begin();
}

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
// En el futuro tengo que cambiar 10000UL (10 segundos) a 8 horas ya que cada ese tiempo cambia aprox 1,1%
  if (!moonInitialized || nowMs - tMoon >= 3600000UL) {
    tMoon = nowMs;
    moonInitialized = true;
    // Placeholder fase lunar real (recalculo horario).
    
    ui.moonIllum = getMoonPhase();
    

    Serial.print("Luna: ");
    Serial.println(ui.moonIllum);
  }
}

void tickClock(UiState &ui) {
  struct tm timeinfo;

  if (getLocalTime(&timeinfo)) {
    ui.hour = timeinfo.tm_hour;
    ui.minute = timeinfo.tm_min;
    ui.second = timeinfo.tm_sec;
  }
}

const char *cardinalFromDegrees(float deg) {
  static const char *dirs[] = {"N", "NE", "E", "SE", "S", "SW", "W", "NW"};
  int idx = static_cast<int>((deg + 22.5f) / 45.0f) % 8;
  return dirs[idx];
}

