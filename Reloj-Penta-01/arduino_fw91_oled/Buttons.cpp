#include "Buttons.h" // ULTIMO

void initButtons(ButtonState &buttons) {
  pinMode(BTN_LEFT, INPUT_PULLUP);
  pinMode(BTN_RIGHT_UP, INPUT_PULLUP);
  pinMode(BTN_RIGHT_DOWN, INPUT_PULLUP);
  buttons = ButtonState();
}

void updateButtons(ButtonState &buttons) {
  uint8_t leftNow = digitalRead(BTN_LEFT);
  uint8_t rightUpNow = digitalRead(BTN_RIGHT_UP);
  uint8_t rightDownNow = digitalRead(BTN_RIGHT_DOWN);

  buttons.pressedLeft = (buttons.lastLeft == HIGH && leftNow == LOW);
  buttons.pressedRightUp = (buttons.lastRightUp == HIGH && rightUpNow == LOW);
  buttons.pressedRightDown = (buttons.lastRightDown == HIGH && rightDownNow == LOW);

  buttons.lastLeft = leftNow;
  buttons.lastRightUp = rightUpNow;
  buttons.lastRightDown = rightDownNow;
}

void handleUiInput(UiState &ui, ButtonState &buttons) {
  // Cualquier boton avanza el cuadrante activo.
  bool anyPressed = buttons.pressedLeft || buttons.pressedRightUp || buttons.pressedRightDown;
  if (anyPressed) {
    ui.focus = static_cast<SensorFocus>((ui.focus + 1) % 3);
  }
}

