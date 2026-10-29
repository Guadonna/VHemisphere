#pragma once
#include "VHemisphereOutput.h"

// Algorithm units stay at 1536 per input volt. Output limits describe the
// logical signal before /5 conversion, independently of the DAC's bias.
#define ONE_OCTAVE (12 << 7)
#define PULSE_VOLTAGE HS::octave_max
#ifdef VHEMISPHERE_OUTPUT_RANGE
#define HEMISPHERE_MAX_CV (VHemisphere::input_limit)
#define HEMISPHERE_MIN_CV (-VHemisphere::input_limit)
#else
#define HEMISPHERE_MAX_CV (HS::octave_max * ONE_OCTAVE)
#define HEMISPHERE_MIN_CV (-OC::DAC::kOctaveZero * ONE_OCTAVE*(1+DAC_20Vpp))
#endif
#define HEMISPHERE_CENTER_CV ((HEMISPHERE_MAX_CV-HEMISPHERE_MIN_CV)/2)
#define HEMISPHERE_3V_CV (3 * ONE_OCTAVE)
#define HEMISPHERE_CENTER_INPUT_CV (NorthernLightModular*HEMISPHERE_MAX_CV/2)
#define HEMISPHERE_MAX_INPUT_CV (6*ONE_OCTAVE + NorthernLightModular*(4*ONE_OCTAVE))
