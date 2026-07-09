# FW91 OLED - Arduino IDE

Proyecto modular para ESP32 + OLED 0.96 (`128x64`) estilo Casio FW-91, con:

- Hora principal legible.
- Fase lunar.
- Termometro.
- Brujula.

## Estructura de archivos

- `arduino_fw91_oled.ino` -> setup/loop principal.
- `Config.h` -> pines y parametros del display.
- `UiState.h` -> estado global de UI.
- `Buttons.h/.cpp` -> lectura de botones y navegacion de modos.
- `Sensors.h/.cpp` -> actualizacion de reloj/sensores (placeholders).
- `DisplayUi.h/.cpp` -> render completo en OLED.

## Como abrir en Arduino IDE

1. Abrir Arduino IDE.
2. `Archivo > Abrir` y elegir `arduino_fw91_oled.ino`.
3. Verifica que todos los `.h/.cpp` aparezcan como pestañas.
4. Selecciona placa ESP32 y puerto.
5. Instala librerias:
   - `Adafruit GFX Library`
   - `Adafruit SSD1306`
6. Compila y sube.

## Preview legible (ASCII)

```text
┌────────────────────────────────────────────────────────────────┐
│ TIME        ALM SIG                               [||| ]       │
│                                              S45               │
│            10:28                                               │
│                                                                │
├────────────────────────────────────────────────────────────────┤
│ (◑) L        │  T                   │  C                       │
│     63%      │  24.3C               │  248 SW                  │
└────────────────────────────────────────────────────────────────┘
```

## Notas de sensores reales

Actualmente `Sensors.cpp` usa valores simulados para validar UI.
Cuando tengas hardware:

- Reemplazar temperatura por lectura real (ej. BME280/DS18B20).
- Reemplazar brujula por magnetometro calibrado (ej. QMC5883L/HMC5883L).
- Reemplazar fase lunar por calculo astronomico con fecha RTC/NTP.

