#pragma once
#include <stdint.h>
namespace VHemisphere {
// Gate/clock state is independent of CV attenuation, slew and pitch scaling.
struct GateState {
  bool active = false;
  bool high = false;
  int remaining = 0;
  explicit operator bool() const { return active; }
  void cv() { active = false; high = false; remaining = 0; }
  void gate(bool value) { active = true; high = value; remaining = 0; }
  void clock(int ticks) { gate(ticks > 0); remaining = ticks > 0 ? ticks : 0; }
  bool tick() {
    if (remaining > 0 && --remaining == 0) { high = false; return true; }
    return false;
  }
};
struct CalibrationCursor { int step; int octave; };
inline CalibrationCursor move_calibration(CalibrationCursor c, int direction,
                                         int first, int last, int zero) {
  if (c.step >= first && c.step <= last) {
    const int octave = c.octave + direction;
    if (octave >= zero - 1 && octave <= zero + 1) return {c.step, octave};
  }
  c.step += direction;
  if (c.step >= first && c.step <= last && (c.step-first)%2) c.step += direction;
  c.octave = zero + (direction > 0 ? -1 : 1);
  return c;
}
constexpr int32_t pitch_per_volt = 1536;
constexpr int32_t input_limit = 5 * pitch_per_volt;
inline int32_t clamp_pitch(int32_t p) {
  return p < -input_limit ? -input_limit : p > input_limit ? input_limit : p;
}
inline int32_t output_pitch(int32_t p) { return clamp_pitch(p) / 5; }
inline int32_t millivolts(int32_t p) { return clamp_pitch(p) * 1000 / input_limit; }
// Interpolate directly in source units: retain DAC resolution rather than
// rounding the scaled voltage to 1/1536 V. Signed spans also support inverted tables.
inline uint16_t calibrated(int32_t p, uint16_t minus, uint16_t zero, uint16_t plus) {
  p = clamp_pitch(p);
  const int32_t span = int32_t(p < 0 ? minus : plus) - zero;
  const int32_t magnitude = p < 0 ? -p : p;
  return uint16_t(int32_t(zero) + int64_t(span) * magnitude / input_limit);
}
}
