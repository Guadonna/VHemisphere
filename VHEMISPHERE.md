# Development status: v0.1.0

See README.md for the implemented behavior and verification limits.
The release is software-validated, not hardware-validated.

Changes from the upstream commit:
- Single standalone Teensy 4.1 target; no multiboot jumps.
- Eight CV outputs: /5 transfer, calibrated interpolation, ±1 V clamp.
- Explicit gate/clock state with fixed 0/1 V endpoints.
- Three-point output calibration (-1, 0, +1 V), selected channel only.
- Nominal voltage labels and live calculated output readout.
- Separate settings and preset bank filenames; targeted reset.
- Host tests including real quantizer and calibration-navigation integration.
- CI build and release HEX/checksum packaging.

Upstream source is retained for attribution and shared dependencies; optional
full-screen apps are not instantiated in this target. Hardware-specific warnings
from upstream (including USB descriptor LTO declaration mismatch) remain; the
release build passes without disabling diagnostics or TLS verification.
