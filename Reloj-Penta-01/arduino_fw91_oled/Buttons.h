#ifndef BUTTONS_H
#define BUTTONS_H

#include <Arduino.h>
#include "Config.h"
#include "UiState.h"

struct ButtonState {
  uint8_t lastLeft = HIGH;
  uint8_t lastRightUp = HIGH;
  uint8_t lastRightDown = HIGH;
  bool pressedLeft = false;
  bool pressedRightUp = false;
  bool pressedRightDown = false;
};

void initButtons(ButtonState &buttons);
void updateButtons(ButtonState &buttons);
void handleUiInput(UiState &ui, ButtonState &buttons);

#endif

