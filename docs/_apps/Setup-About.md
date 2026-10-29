---
layout: default
---
# Setup / About

Displays the firmware version, Teensy 4.0 target and fixed output range.
Rotate the left encoder to choose Calibrate or Reflash, then press to enter.
Hold the right encoder button on this screen to return to the app menu.
During calibration the right button advances through calibration steps.

## Calibration routine

For each output A–D, calibrate three points: **-1, 0 and +1 V**.
The left encoder selects the point; the right encoder adjusts its DAC code.
Press the right encoder to advance. Measure the selected output with an external
voltmeter; other outputs are held at their calibrated zero. Complete the wizard
and choose Save to persist the changes.

The wizard directly adjusts the DAC code and can exceed +/-1 V. Disconnect
the video synthesizer while calibrating. The normal output limiter operates
using the calibrated endpoints and cannot correct an inaccurate calibration.

Input calibration and its units are unchanged. Preserve an existing input
calibration by skipping those steps without resetting or editing it.
Encoder direction and screensaver settings remain available in the wizard.

## Verification

Use Voltage to check output levels and Scope to check inputs. The displayed
output voltage is calculated, not measured. Check actual voltage with a meter.
The release has passed host tests and compilation; behavior during power-up,
reset and power-down still requires measurement on the module.
