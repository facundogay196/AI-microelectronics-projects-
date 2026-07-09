#include <math.h>
#include <time.h>

float getMoonPhase()
{
    struct tm localTime;

    if (!getLocalTime(&localTime))
        return 0.0f;
    time_t now =mktime(&localTime);

    struct tm utcTime;
    gmtime_r(&now, &utcTime);

    int year  = utcTime.tm_year + 1900;
    int month = utcTime.tm_mon + 1;
    int day   = utcTime.tm_mday;

    double hour =
        utcTime.tm_hour +
        utcTime.tm_min / 60.0 +
        utcTime.tm_sec / 3600.0;

    // Conversión a Día Juliano
    if (month <= 2) {
        year--;
        month += 12;
    }
    Serial.printf(
    "UTC: %04d-%02d-%02d %02d:%02d:%02d\n",
    utcTime.tm_year + 1900,
    utcTime.tm_mon + 1,
    utcTime.tm_mday,
    utcTime.tm_hour,
    utcTime.tm_min,
    utcTime.tm_sec
);
    Serial.printf(
    "LOCAL: %04d-%02d-%02d %02d:%02d:%02d\n",
    localTime.tm_year + 1900,
    localTime.tm_mon + 1,
    localTime.tm_mday,
    localTime.tm_hour,
    localTime.tm_min,
    localTime.tm_sec
);
    int A = year / 100;
    int B = 2 - A + (A / 4);

    double JD =
        floor(365.25 * (year + 4716))
      + floor(30.6001 * (month + 1))
      + day + B - 1524.5
      + hour / 24.0;

    // Siglos julianos desde J2000.0
    double T = (JD - 2451545.0) / 36525.0;

    // Longitud media del Sol
    double Ls = fmod(
        280.46646 +
        T * (36000.76983 + 0.0003032 * T),
        360.0);

    // Anomalía media del Sol
    double Ms = 357.52911 +
                T * (35999.05029 - 0.0001537 * T);

    // Longitud media de la Luna
    double Lm = fmod(
        218.3165 +
        481267.8813 * T,
        360.0);

    // Anomalía media de la Luna
    double Mm =
        134.963 +
        477198.8676 * T;

    // Elongación media
    double D =
        297.850 +
        445267.1115 * T;

    // Pasar a radianes
    double deg = PI / 180.0;

    Ms *= deg;
    Mm *= deg;
    D  *= deg;

    // Ángulo de fase (Meeus simplificado)
    double phaseAngle =
          180.0
        - (D / deg)
        - 6.289 * sin(Mm)
        + 2.100 * sin(Ms)
        - 1.274 * sin(2 * D - Mm)
        - 0.658 * sin(2 * D)
        - 0.214 * sin(2 * Mm)
        - 0.110 * sin(D);

    phaseAngle *= deg;

    // Iluminación (0–100 %)
    double illumination =
        (1.0 + cos(phaseAngle)) * 50.0;

    return (float)illumination;
}