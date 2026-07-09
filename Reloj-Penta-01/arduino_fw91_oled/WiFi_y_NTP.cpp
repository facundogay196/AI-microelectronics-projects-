#include "WiFi_y_NTP.h"
#include <WiFi.h>
#include <time.h>

const char* ssid = "Grace’s Home";
const char* password = "Apolos2023&$$";

const char* ntpServer = "pool.ntp.org";
const long gmtOffset_sec = 3600;
const int daylightOffset_sec = 3600;

bool conectarWiFi()
{
    Serial.println();
    Serial.println("=================================");
    Serial.println("Iniciando conexion WiFi...");
    Serial.print("SSID: ");
    Serial.println(ssid);

    WiFi.mode(WIFI_STA);
    WiFi.disconnect(true);
    delay(500);

    WiFi.begin(ssid, password);

    unsigned long inicio = millis();

    while (WiFi.status() != WL_CONNECTED)
    {
        Serial.print(".");

        delay(500);

        if (millis() - inicio > 15000)
        {
            Serial.println();
            Serial.println("ERROR: No fue posible conectar al WiFi.");

            Serial.print("Codigo WiFi.status(): ");
            Serial.println(WiFi.status());

            return false;
        }
    }

    Serial.println();
    Serial.println("WiFi conectado!");
    Serial.print("IP: ");
    Serial.println(WiFi.localIP());

    configTime(0, 0, ntpServer);

    setenv("TZ", "CET-1CEST,M3.5.0/2,M10.5.0/3", 1);
    tzset();

    Serial.println("NTP configurado.");

    return true;
}