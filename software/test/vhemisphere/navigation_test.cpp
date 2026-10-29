#include <cassert>
#include <cstdint>
#include <cstdio>
#include <deque>
#include "../../src/src/UI/ui_events.h"
#define FLASHMEM
uint_fast8_t MENU_REDRAW = 0;
struct RuntimeSlot { void *instance; };
namespace OC {
enum UiControl { CONTROL_BUTTON_A = 1, CONTROL_BUTTON_L = 4,
                 CONTROL_BUTTON_R = 8, CONTROL_BUTTON_Z = 16 };
enum UiMode { UI_MODE_SCREENSAVER, UI_MODE_MENU, UI_MODE_APP_SETTINGS };
struct AppBase {
  bool can_exit = true;
  int dispatched = 0, short_right = 0, io_edits = 0;
  bool allow_long_press_exit() const { return can_exit; }
  UiMode DispatchEvent(const UI::Event &e) {
    ++dispatched;
    if (e.control == CONTROL_BUTTON_R && e.type == UI::EVENT_BUTTON_PRESS) ++short_right;
    return UI_MODE_MENU;
  }
  void EditIOSettings() { ++io_edits; }
};
struct Queue {
  std::deque<UI::Event> events;
  bool available() const { return !events.empty(); }
  UI::Event PullEvent() { auto e = events.front(); events.pop_front(); return e; }
};
// Hardware and app boundaries are simulated; DispatchEvents below is production code.
struct Ui {
  Queue event_queue_;
  bool screensaver_ = false, preempt_screensaver_ = false, jump_to_menu_ = false;
  bool app_ignores_right = false, swallow_release = false;
  int explicit_ignores = 0;
  uint32_t idle_time() const { return 0; }
  uint32_t screensaver_timeout() const { return 1; }
  void SetButtonIgnoreMask() {}
  void IgnoreButton(UiControl c) {
    assert(c == CONTROL_BUTTON_R);
    ++explicit_ignores;
    swallow_release = true;
  }
  bool IgnoreEvent(const UI::Event &e) {
    if (swallow_release && e.control == CONTROL_BUTTON_R &&
        (e.type == UI::EVENT_BUTTON_RELEASE || e.type == UI::EVENT_BUTTON_LONG_RELEASE)) {
      swallow_release = false;
      return true;
    }
    if (app_ignores_right && e.control == CONTROL_BUTTON_R) return true;
    if (screensaver_) { screensaver_ = false; return true; }
    return false;
  }
  UiMode DispatchEvents(const RuntimeSlot &appslot);
  void Push(UI::EventType type, uint16_t control, uint16_t mask = 0) {
    event_queue_.events.emplace_back(type, control, 0, mask);
  }
};
#include "../../src/OC_ui_dispatch.inc"
}
int main() {
  using namespace OC;
  // Editor / backup / overlay: the global hold must never reach app actions.
  for (bool consumed_down : {false, true}) {
    Ui ui;
    AppBase app;
    RuntimeSlot slot{&app};
    ui.app_ignores_right = consumed_down; // e.g. Hemisphere quantizer popup
    ui.Push(UI::EVENT_BUTTON_LONG_PRESS, CONTROL_BUTTON_R, CONTROL_BUTTON_R);
    ui.Push(UI::EVENT_BUTTON_LONG_RELEASE, CONTROL_BUTTON_R);
    assert(ui.DispatchEvents(slot) == UI_MODE_APP_SETTINGS);
    assert(app.dispatched == 0 && app.short_right == 0);
    assert(ui.explicit_ignores == 1 && MENU_REDRAW == 1);
    assert(ui.event_queue_.available());
    // The release must be consumed by IgnoreEvent, as the app picker also does.
    assert(ui.IgnoreEvent(ui.event_queue_.PullEvent()));
  }
  Ui ui;
  AppBase app;
  RuntimeSlot slot{&app};
  // Short presses and other long presses still belong to the app.
  ui.Push(UI::EVENT_BUTTON_PRESS, CONTROL_BUTTON_R);
  ui.Push(UI::EVENT_BUTTON_LONG_PRESS, CONTROL_BUTTON_L, CONTROL_BUTTON_L);
  assert(ui.DispatchEvents(slot) == UI_MODE_MENU);
  assert(app.dispatched == 2 && app.short_right == 1);
  // A wizard may explicitly reserve the hold and retain its ignore mask.
  app.can_exit = false;
  ui.app_ignores_right = true;
  ui.Push(UI::EVENT_BUTTON_LONG_PRESS, CONTROL_BUTTON_R, CONTROL_BUTTON_R);
  assert(ui.DispatchEvents(slot) == UI_MODE_MENU && app.dispatched == 2);
  ui.app_ignores_right = false;
  // Existing UP + encoder shortcuts continue to work.
  ui.Push(UI::EVENT_BUTTON_DOWN, CONTROL_BUTTON_R, CONTROL_BUTTON_R | CONTROL_BUTTON_A);
  assert(ui.DispatchEvents(slot) == UI_MODE_APP_SETTINGS);
  ui.Push(UI::EVENT_BUTTON_DOWN, CONTROL_BUTTON_L, CONTROL_BUTTON_L | CONTROL_BUTTON_A);
  assert(ui.DispatchEvents(slot) == UI_MODE_MENU && app.io_edits == 1);
  // A long press used to wake the screensaver must not also select an app.
  ui.screensaver_ = true;
  app.can_exit = true;
  ui.Push(UI::EVENT_BUTTON_LONG_PRESS, CONTROL_BUTTON_R, CONTROL_BUTTON_R);
  assert(ui.DispatchEvents(slot) == UI_MODE_MENU);
  assert(ui.explicit_ignores == 0);
  puts("PASS: production UI dispatcher, global exit, consumed popup presses, release suppression, calibration reservation and existing shortcuts");
}
