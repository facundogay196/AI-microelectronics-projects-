#include <WiFi.h>

const char* ssid = "Usuario";
const char* password = "contraseña";

#include "time.h"

const char* ntpServer = "pool.ntp.org";
const long gmtOffset_sec = 3600;      // Malta = UTC+1
const int daylightOffset_sec = 3600;  // horario verano (si aplica)
