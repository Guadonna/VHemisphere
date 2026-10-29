---
title: Installation
nav_order: 2
---
# Install on Teensy 4.0

1. Back up the module's calibration and presets using the installed firmware.
2. Download `VHemisphere-v0.2.3-Teensy40.hex` and `SHA256SUMS` from
   [VHemisphere releases](https://github.com/Guadonna/VHemisphere/releases).
3. Open the HEX in [Teensy Loader](https://www.pjrc.com/teensy/loader.html).
   Follow the module manufacturer's USB and power connection instructions.
4. Enter programming mode with the Teensy program button or Setup/About →
   Reflash in the existing firmware. Program the image and reboot.
5. Measure outputs A–D and calibrate at -1, 0 and +1 V using
   [Setup/About](Setup-About). Keep the video synthesizer disconnected during
   calibration because the wizard directly adjusts the DAC code.

This image uses the standard O_C Teensy 4.0 pinout and four outputs.
Input calibration is retained. Settings use `VHEM40.CFG`, `VHEM40.BAK`
and `VHEM40_PRESETS.DAT`; old Hemisphere presets are not loaded automatically.

For a local build, see [Build](Build-Choices). Software tests and compilation
are verified; physical voltages, noise and startup behavior still need checking
on a module.
