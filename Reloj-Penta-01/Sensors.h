#ifndef SENSORS_H
#define SENSORS_H

#include <Arduino.h>
#include "UiState.h"

void initSensors();
void updateSensors(UiState &ui, unsigned long nowMs);
void tickClock(UiState &ui);
const char *cardinalFromDegrees(float deg);

#endif

