# Development status: v0.2.4

See README.md for the implemented behavior and verification limits.
The release is software-validated, not hardware-validated.

Changes from the upstream commit:
- Single standalone Teensy 4.0 target, original Phazerville T40 pinout,
  300 MHz CPU clock and standard Teensy 4.0 linker script.
- Four CV outputs: /5 transfer, calibrated interpolation, ±1 V clamp.
- Explicit gate/clock state with fixed 0/1 V endpoints.
- Three-point output calibration (-1, 0, +1 V), selected channel only.
- Nominal voltage labels and live calculated output readout.
- Separate settings and Hemisphere preset filename; targeted reset.
- Host tests including real quantizer and calibration-navigation integration.
- CI build and release HEX/checksum packaging.

Upstream source is retained for attribution and shared dependencies; optional
full-screen apps are not instantiated in this target. Hardware-specific warnings
from upstream (including USB descriptor LTO declaration mismatch) remain; the
release build passes without disabling diagnostics or TLS verification.

Version 0.2.2 separates logical output bounds (+/-5 internal volts) from the
physical DAC bias. This corrects early negative clipping in applets and the
Voltage encoder range. Full-range generators use these bounds as well; their
amplitudes may change compared with older patches. Input scaling is unchanged.

Output labels now round once directly to centivolts. Parameter contributions
are displayed before final clipping; the output monitor applies the limiter.
EnsOscKey uses voltageToCode for both output and display (0.05..0.95 V).
Host tests run the actual Voltage and AttenOff applet classes with simulated I/O
and cover encoder endpoints, labels, preset restoration and bipolar input.

Version 0.2.3 restores right-encoder long-press to leave the Setup/About
landing page. Its release is consumed to avoid triggering Reset or the app
picker. Calibration step handling and the global UP + right-encoder shortcut
are unchanged.

Version 0.2.4 handles right-encoder hold in the shared UI dispatcher, before
application-specific ignore masks or I/O overlays can swallow it. The right
button release is explicitly consumed, including a release already in the queue.
Setup opts out only during calibration; the app picker retains hold-to-save.
Duplicate per-app exit handlers are removed. The host navigation harness runs
the production dispatcher with simulated app and hardware boundaries.
