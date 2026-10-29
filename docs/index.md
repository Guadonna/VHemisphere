---
title: VHemisphere
nav_order: 1
---
# VHemisphere for Teensy 4.0

Firmware for standard four-output O_C hardware with Teensy 4.0.
Hemisphere runs two applets simultaneously. CV outputs use a fixed /5 transfer
and are limited to -1 through +1 V; typed gate/clock outputs use 0/1 V.
CV and trigger inputs retain their original ranges.

See the [project README](https://github.com/Guadonna/VHemisphere#readme)
for installation, output calibration and validation limits.
Download firmware from [VHemisphere releases](https://github.com/Guadonna/VHemisphere/releases).

The applet reference describes the underlying Hemisphere algorithms. Original
voltage examples describe internal values: divide output CV by five and limit
to +/-1 V when interpreting them for VHemisphere. Input thresholds and note
parameters keep their original meaning. The current release is a prerelease
awaiting measurements on physical hardware.

Derived from Ornament & Crime, Hemisphere Suite and Phazerville; see
[provenance and licensing](https://github.com/Guadonna/VHemisphere/blob/main/NOTICE.md).
