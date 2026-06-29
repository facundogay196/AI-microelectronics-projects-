float getMoonPhase() {

  struct tm timeinfo;
  if (!getLocalTime(&timeinfo)) {
    return 0;
  }

  // Convertir fecha a días desde 2000-01-06 (referencia lunar)
  int year = timeinfo.tm_year + 1900;
  int month = timeinfo.tm_mon + 1;
  int day = timeinfo.tm_mday;

  if (month < 3) {
    year--;
    month += 12;
  }

  int A = year / 100;
  int B = A / 4;
  int C = 2 - A + B;
  int E = (int)(365.25 * (year + 4716));
  int F = (int)(30.6001 * (month + 1));

  double jd = C + day + E + F - 1524.5;

  double daysSinceNewMoon = jd - 2451550.1;

  double lunarCycle = 29.53058867;

  double phase = fmod(daysSinceNewMoon, lunarCycle);

  if (phase < 0) phase += lunarCycle;

  return (phase / lunarCycle) * 100.0; // 0–100%
}