#ifndef CONFIG_H
#define CONFIG_H

#include <Arduino.h>

// OLED 0.96" tipico
static const uint8_t SCREEN_WIDTH = 128;
static const uint8_t SCREEN_HEIGHT = 64;
static const int8_t OLED_RESET = -1;
static const uint8_t OLED_ADDR = 0x3C;

// Pines ejemplo ESP32 (cambia segun tu hardware)
static const uint8_t BTN_LEFT = 25;
static const uint8_t BTN_RIGHT_UP = 26;
static const uint8_t BTN_RIGHT_DOWN = 27;

#endif

