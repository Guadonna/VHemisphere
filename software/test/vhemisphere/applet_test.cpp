// Host harness: run the actual Voltage and AttenOff applets with simulated I/O.
#include <algorithm>
#include <cassert>
#include <cstdint>
#include <cstdio>
#include <string>
#include <vector>
#define VHEMISPHERE_OUTPUT_RANGE
constexpr bool NorthernLightModular = false;
#include "../../src/HSVoltage.h"
#include "../../src/VHemisphereDisplay.h"
#define ForEachChannel(ch) for (int ch = 0; ch < 2; ++ch)
#define CONSTRAIN(v, lo, hi) v = constrain(v, lo, hi)
int constrain(int v, int lo, int hi) { return std::clamp(v, lo, hi); }
int Proportion(int value, int max, int scale) { return int(int64_t(value) * scale / max); }
struct PackLocation { int offset, size; };
void Pack(uint64_t &data, PackLocation p, uint64_t v) {
    data |= (v & ((uint64_t(1) << p.size) - 1)) << p.offset;
}
int Unpack(uint64_t data, PackLocation p) {
    return (data >> p.offset) & ((uint64_t(1) << p.size) - 1);
}
namespace PhzIcons { const uint8_t voltage[] = {0}, dualAttenuverter[] = {0}; }
const uint8_t DOWN_ICON[] = {0};
std::vector<std::string> voltage_labels;
void gfxPrintOutputVoltage(int cv, bool clip = true, bool compact = false) {
    char text[24];
    VHemisphere::format_voltage(text, sizeof(text), cv, clip, compact);
    voltage_labels.emplace_back(text);
}
template <typename... T> void gfxPrint(T...) {}
template <typename... T> void gfxInvert(T...) {}
template <typename... T> void gfxCursor(T...) {}
template <typename... T> void gfxIcon(T...) {}
template <typename... T> void gfxFrame(T...) {}
class HemisphereApplet {
public:
    bool editing = true;
    int input[2] = {}, output[2] = {};
    bool gates[2] = {};
    bool EditMode() const { return editing; }
    void CursorToggle() { editing = !editing; }
    bool CursorBlink() const { return true; }
    void MoveCursor(int &cursor, int direction, int max) { cursor = constrain(cursor + direction, 0, max); }
    bool Gate(int ch) const { return gates[ch]; }
    int In(int ch) const { return input[ch]; }
    void Out(int ch, int cv) { output[ch] = cv; }
    const char* OutputLabel(int ch) const { return ch ? "B" : "A"; }
protected:
    enum { HELP_DIGITAL1, HELP_DIGITAL2, HELP_CV1, HELP_CV2, HELP_OUT1, HELP_OUT2, HELP_EXTRA1, HELP_EXTRA2 };
    const char *help[8] = {};
};
#include "../../src/applets/Voltage.h"
#include "../../src/applets/AttenuateOffset.h"

int main() {
    static_assert(HEMISPHERE_MAX_INPUT_CV == 9216); // physical input units unchanged
    static_assert(HEMISPHERE_MIN_CV == -7680 && HEMISPHERE_MAX_CV == 7680);
    Voltage app{};
    app.Start(); app.Controller(); app.View();
    assert((voltage_labels == std::vector<std::string>{"+1.00V", "-1.00V"}));
    assert(app.output[0] == 7680 && app.output[1] == -7680);
    // Sweep the real encoder path over every setting and into both end stops.
    app.OnEncoderMove(-1000);
    for (int step = -60; step <= 60; ++step) {
        app.Controller();
        assert(app.output[0] == step * 128);
        const int expected_cents = (std::abs(step)*100 + 30)/60 * (step < 0 ? -1 : 1);
        assert(VHemisphere::centivolts(app.output[0]) == expected_cents);
        voltage_labels.clear(); app.View();
        if (step == -36) assert(voltage_labels[0] == "-0.60V");
        if (step == 36) assert(voltage_labels[0] == "+0.60V");
        if (step == 0) assert(voltage_labels[0] == "+0.00V");
        app.OnEncoderMove(1);
    }
    app.Controller(); assert(app.output[0] == 7680);
    Voltage restored{};
    restored.Start(); restored.OnDataReceive(app.OnDataRequest()); restored.Controller();
    assert(restored.output[0] == 7680 && restored.output[1] == -7680);
    assert(VHemisphere::calibrated(restored.output[1], 23000, 30000, 36500) == 23000);
    restored.gates[1] = true; restored.Controller(); assert(restored.output[1] == 0);
    restored.gates[1] = false; restored.Controller(); assert(restored.output[1] == -7680);
    // Existing -3V internal presets keep their value but display -0.60V correctly.
    uint64_t legacy = 0;
    Pack(legacy, {0,9}, 256-36); Pack(legacy, {10,9}, 256+36);
    restored.OnDataReceive(legacy); restored.Controller();
    voltage_labels.clear(); restored.View();
    assert((voltage_labels == std::vector<std::string>{"-0.60V", "+0.60V"}));
    // Pass-through of bipolar CV and offset edits use the full logical range.
    AttenuateOffset atten{};
    atten.Start(); atten.input[0] = -7680; atten.input[1] = 7680; atten.Controller();
    assert(atten.output[0] == -7680 && atten.output[1] == 7680);
    atten.input[0] = 0; atten.OnEncoderMove(-1000); atten.Controller();
    voltage_labels.clear(); atten.View();
    assert(atten.output[0] == -7680 && voltage_labels[0] == "-1.00V");
    atten.OnEncoderMove(1000); atten.Controller();
    voltage_labels.clear(); atten.View();
    assert(atten.output[0] == 7680 && voltage_labels[0] == "+1.00V");
    puts("PASS: real Voltage encoder sweep, display, gates and presets; AttenOff bipolar input and offsets");
}
