#include <WiFi.h>

const char* ssid = "Grace's Home";
const char* password = "Apolos2023&$$";

#include "time.h"

const char* ntpServer = "pool.ntp.org";
const long gmtOffset_sec = 3600;      // Malta = UTC+1
const int daylightOffset_sec = 3600;  // horario verano (si aplica)