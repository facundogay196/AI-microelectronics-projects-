#include "DisplayUi.h"
#include "Sensors.h"

static void drawBattery(Adafruit_SSD1306 &display, uint8_t x, uint8_t y, uint8_t pct) {
  display.drawRect(x, y, 10, 5, SSD1306_WHITE);
  display.drawRect(x + 10, y + 1, 2, 3, SSD1306_WHITE);
  uint8_t fill = map(pct, 0, 100, 0, 8);
  if (fill > 0) display.fillRect(x + 1, y + 1, fill, 3, SSD1306_WHITE);
}

static void drawMoonIcon(Adafruit_SSD1306 &display, uint8_t cx, uint8_t cy, uint8_t r, float illumPct) {
  display.drawCircle(cx, cy, r, SSD1306_WHITE);
  int8_t phaseShift = static_cast<int8_t>(map(static_cast<int>(illumPct), 0, 100, -r, r));
  for (int8_t y = -r + 1; y < r; y++) {
    int8_t xLim = static_cast<int8_t>(sqrt(static_cast<float>(r * r - y * y)));
    int8_t xStart = -xLim + phaseShift;
    for (int8_t x = xStart; x <= xLim; x++) {
      if (x >= -xLim && x <= xLim) display.drawPixel(cx + x, cy + y, SSD1306_WHITE);
    }
  }
}

static void drawThermometerIcon(Adafruit_SSD1306 &display, uint8_t x, uint8_t y) {
  display.drawRect(x, y, 4, 9, SSD1306_WHITE);
  display.fillCircle(x + 2, y + 10, 3, SSD1306_WHITE);
  display.fillRect(x + 1, y + 3, 2, 5, SSD1306_WHITE);
}

static void drawHeader(Adafruit_SSD1306 &display, const UiState &ui) {
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(3, 1);
  if (ui.mode == MODE_TIME) display.print("TIME");
  else if (ui.mode == MODE_SENSOR) display.print("SENS");
  else display.print("SET ");

  display.setCursor(46, 1);
  if (ui.alarmOn) display.print("ALM ");
  if (ui.sigOn) display.print("SIG ");
  if (ui.btOn) display.print("BT");
  drawBattery(display, 114, 2, ui.batteryPct);
}

static void drawMainClock(Adafruit_SSD1306 &display, const UiState &ui) {
  char hhmm[6];
  char ss[3];
  snprintf(hhmm, sizeof(hhmm), "%02u:%02u", ui.hour, ui.minute);
  snprintf(ss, sizeof(ss), "%02u", ui.second);

  display.setTextSize(3);
  display.setCursor(2, 12);
  display.print(hhmm);

  // Segundos al lado de la hora sin separador ":".
  display.setTextSize(2);
  display.setCursor(98, 20);
  display.print(ss);
}

static void drawSensorStrip(Adafruit_SSD1306 &display, const UiState &ui) {
  display.drawLine(1, 40, 126, 40, SSD1306_WHITE);
  display.drawLine(43, 41, 43, 62, SSD1306_WHITE);
  display.drawLine(80, 41, 80, 62, SSD1306_WHITE);

  display.setTextSize(1);

  // Luna
  drawMoonIcon(display, 22, 47, 5, ui.moonIllum);
  display.setCursor(13, 54);
  display.print(static_cast<int>(ui.moonIllum));
  display.print("%");

  // Temperatura
  drawThermometerIcon(display, 46, 46);
  display.setCursor(56, 45);
  display.print("TEMP");
  display.setCursor(56, 54);
  display.print(ui.tempC, 1);

  // Brújula
  display.setCursor(82, 45);
  display.print("BRUJULA");
  display.setCursor(93, 54);
  display.print(static_cast<int>(ui.smoothCompass));
  display.setCursor(114, 54);
  display.print(cardinalFromDegrees(ui.smoothCompass));
}

static void drawFocusFrame(Adafruit_SSD1306 &display, const UiState &ui) {
  if (ui.mode != MODE_TIME) return;

  // Foco activo por inversion sin tocar lineas divisorias (sin marco).
  if (ui.focus == FOCUS_MOON) {
    display.fillRect(3, 42, 39, 20, SSD1306_INVERSE);
  } else if (ui.focus == FOCUS_TEMP) {
    display.fillRect(44, 42, 36, 20, SSD1306_INVERSE);
  } else {
    display.fillRect(81, 42, 45, 20, SSD1306_INVERSE);
  }
}

void drawScreen(Adafruit_SSD1306 &display, const UiState &ui, unsigned long nowMs) {
  if (ui.invertBlink) {
    display.invertDisplay((nowMs / 300) % 2);
  } else {
    display.invertDisplay(false);
  }

  display.clearDisplay();
  display.drawRect(0, 0, 128, 64, SSD1306_WHITE);
  drawHeader(display, ui);
  drawMainClock(display, ui);
  drawSensorStrip(display, ui);
  drawFocusFrame(display, ui);
  display.display();
}

