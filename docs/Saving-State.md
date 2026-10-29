---
title: Saving State
nav_order: 5
---
# State storage on Teensy 4.0

Calibration remains in its reserved EEPROM region. VHemisphere uses internal
LittleFS storage for `VHEM40.CFG`, backup `VHEM40.BAK`, and Hemisphere presets
in `VHEM40_PRESETS.DAT`.

Global settings include the selected startup app, custom scales and waveforms.
Long-press the right encoder on the main app menu to save them.

Presets include both applets, I/O mappings, clock and quantizer settings.
Long-press DOWN in Hemisphere to open configuration, then turn the left
encoder to the floating Load/Save menu. See [Presets](Hemisphere-Presets)
for automatic saving and MIDI program changes.

Factory reset removes VHemisphere settings and preset files only. Other
firmware's files remain untouched. Old presets are not migrated automatically;
the new output voltage scaling also changes the effect of imported presets.
