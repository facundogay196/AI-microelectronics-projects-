#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "WiFi_y_NTP.h"
#include "Config.h"
#include "UiState.h"
#include "Sensors.h"
#include "Buttons.h"
#include "DisplayUi.h"

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
UiState ui;
ButtonState buttons;

unsigned long tSec = 0;
unsigned long tFrame = 0;

void setOledContrast(uint8_t value) {
  display.ssd1306_command(SSD1306_SETCONTRAST);
  display.ssd1306_command(value);
}
void setup() {
  
  Serial.begin(115200);

  delay(1000);

  Serial.println();
  Serial.println("===== RELOJ PENTA =====");
  
  initButtons(buttons);
  
  ui.wifiOn = conectarWiFi();

  initSensors();

  if (!display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR)) {
    while (true) delay(10);
  }

 setOledContrast(40); // brillo bajo
  display.clearDisplay();
  display.display();
}


void loop() {
  unsigned long now = millis();

  updateButtons(buttons);
  handleUiInput(ui, buttons);
  updateSensors(ui, now);

  if (now - tSec >= 1000) {
    tSec = now;
    tickClock(ui);
  }

  if (now - tFrame >= 200) {
    tFrame = now;
    drawScreen(display, ui, now);
  }
}

