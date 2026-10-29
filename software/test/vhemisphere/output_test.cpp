#include "../../src/VHemisphereOutput.h"
#include "../../src/src/extern/braids_quantizer.h"
#include <cassert>
#include <climits>
#include <cstdio>

int main() {
  using namespace VHemisphere;
  // Unequal slopes and nonzero offset exercise calibration, not just division.
  constexpr uint16_t lo = 23000, zero = 30000, hi = 36500;
  assert(calibrated(INT_MIN, lo, zero, hi) == lo);
  assert(calibrated(INT_MAX, lo, zero, hi) == hi);
  assert(calibrated(-7680, lo, zero, hi) == lo);
  assert(calibrated(0, lo, zero, hi) == zero);
  assert(calibrated(7680, lo, zero, hi) == hi);
  assert(calibrated(-3840, lo, zero, hi) == 26500);
  assert(calibrated(3840, lo, zero, hi) == 33250);
  assert(calibrated(3840, hi, zero, lo) == 26500);
  assert(calibrated(2, lo, zero, hi) > zero); // precision survives /5 conversion
  for (int p = -10000; p <= 10000; ++p) {
    const int value = calibrated(p, lo, zero, hi);
    assert(value >= lo && value <= hi);
    assert(value <= calibrated(p + 1, lo, zero, hi));
    assert(output_pitch(p) == -output_pitch(-p));
    assert(millivolts(p) >= -1000 && millivolts(p) <= 1000);
  }
  // Traverse the exact wizard state helper used on-device: 8 channels x 3 points.
  CalibrationCursor cursor{1, 0};
  for (int ch = 0; ch < 8; ++ch) {
    for (int point = 2; point <= 4; ++point) {
      cursor = move_calibration(cursor, 1, 2, 17, 3);
      assert(cursor.step == 2 + ch*2 && cursor.octave == point);
    }
  }
  cursor = move_calibration(cursor, 1, 2, 17, 3);
  assert(cursor.step == 18);
  for (int ch = 7; ch >= 0; --ch) {
    for (int point = 4; point >= 2; --point) {
      cursor = move_calibration(cursor, -1, 2, 17, 3);
      assert(cursor.step == 2 + ch*2 && cursor.octave == point);
    }
  }
  assert(move_calibration(cursor, -1, 2, 17, 3).step == 1);
  GateState gate;
  assert(!gate && !gate.high);
  gate.clock(17);
  assert(gate && gate.high);
  for (int i = 0; i < 16; ++i) { assert(!gate.tick()); assert(gate.high); }
  assert(gate.tick() && !gate.high);
  gate.clock(17); gate.clock(2); // retrigger replaces pulse duration
  assert(!gate.tick()); assert(gate.tick());
  gate.clock(17); gate.gate(true); // sustained gate cancels old timer
  for (int i = 0; i < 100; ++i) assert(!gate.tick() && gate.high);
  gate.gate(false); assert(gate && !gate.high);
  gate.clock(17); gate.cv(); // CV / applet switch cancels clock ownership
  assert(!gate && !gate.tick());
  gate.clock(0); assert(!gate.high && !gate.tick());
  gate.clock(-1); assert(!gate.high && !gate.tick());
  // Real firmware quantizer -> actual output transfer. Input scale remains 1V/oct.
  const braids::Scale chromatic = {1536, 12, {0,128,256,384,512,640,768,896,1024,1152,1280,1408}};
  braids::Quantizer quantizer;
  for (int octave = -5; octave <= 5; ++octave) {
    quantizer.Init();
    quantizer.Configure(chromatic);
    const int pitch = octave * 1536;
    assert(quantizer.Process(pitch) == pitch);
    assert(millivolts(quantizer.Process(pitch)) == octave * 200);
  }
  // A semitone remains a semitone internally, and becomes 1/60 V at output.
  quantizer.Init(); quantizer.Configure(chromatic);
  assert(quantizer.Process(128) == 128);
  assert(calibrated(128, lo, zero, hi) == 30108);
  puts("PASS: calibration endpoints, asymmetry, inverted tables, clipping, precision, monotonicity, real quantizer integration, gate/clock transitions, 24 calibration steps forward/backward");
}
