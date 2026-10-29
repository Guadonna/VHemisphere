---
title: Build
nav_order: 3
---
# Teensy 4.0 build

The sole PlatformIO environment is `VHemisphere`: `board = teensy40`, CPU
300 MHz, standard O_C T40 pinout and four CV outputs. Hemisphere hosts two
applets. Setup, scale and waveform editors, and backup are included.

From the repository root:

```sh
python3 -m venv .venv
. .venv/bin/activate
python -m pip install platformio==6.2.0
scripts/test-host.sh
pio run -d software -e VHemisphere -j 4
```

The firmware image is `software/.pio/build/VHemisphere/VHemisphere-v0.2.2-Teensy40.hex`.
See [Installation](Installation) to load it.
