#pragma once
#include <stdio.h>
#include "VHemisphereOutput.h"

namespace VHemisphere {
// Round once, directly from algorithm units to hundredths of an output volt.
// Parameter contributions may exceed the output range before mixing/clipping.
inline int32_t centivolts(int32_t pitch, bool clip = true) {
  const int64_t value = clip ? clamp_pitch(pitch) : pitch;
  const int64_t magnitude = value < 0 ? -value : value;
  const int32_t rounded = (magnitude * 100 + input_limit / 2) / input_limit;
  return value < 0 ? -rounded : rounded;
}
inline void format_voltage(char *text, size_t size, int32_t pitch,
                           bool clip = true, bool compact = false) {
  const int32_t value = centivolts(pitch, clip);
  const int32_t magnitude = value < 0 ? -value : value;
  snprintf(text, size, "%s%ld.%02ld%s", value < 0 ? "-" : compact ? "" : "+",
           long(magnitude / 100), long(magnitude % 100), compact ? "" : "V");
}
}
