// Included inside namespace OC by OC_ui.cpp and the host event-routing test.
FLASHMEM __attribute__((noinline))
UiMode Ui::DispatchEvents(const RuntimeSlot &appslot) {
  AppBase* app = static_cast<AppBase*>(appslot.instance);
  if (!app) return UiMode::UI_MODE_APP_SETTINGS;

  while (event_queue_.available()) {
    const UI::Event event = event_queue_.PullEvent();
    if (screensaver_ && UI::EVENT_BUTTON_LONG_RELEASE == event.type)
      continue; // saves some headaches
    // This must precede app-owned ignore masks: a popup may consume DOWN,
    // but holding the right encoder must still provide a way to leave it.
    // The app picker handles its own events separately, preserving hold-to-save.
    if (!screensaver_ && event.type == UI::EVENT_BUTTON_LONG_PRESS &&
        event.control == CONTROL_BUTTON_R &&
        !(event.mask & ~CONTROL_BUTTON_R) && app->allow_long_press_exit()) {
      MENU_REDRAW = 1;
      IgnoreButton(CONTROL_BUTTON_R); // also covers an already queued release
      jump_to_menu_ = true;
      break;
    }
    if (IgnoreEvent(event))
      continue;

    MENU_REDRAW = 1;

    const bool z_hold = (event.mask & CONTROL_BUTTON_Z);
    const bool a_hold = (event.mask & CONTROL_BUTTON_A);

    // --- Handle global hotkeys
    if (UI::EVENT_BUTTON_DOWN == event.type) {
      // Hold Z or A and push right encoder for main menu
      if (CONTROL_BUTTON_R == event.control && (z_hold || a_hold)) {
        jump_to_menu_ = true;
        break;
      }
      // Hold Z or A and push left encoder for IO settings menu
      if (CONTROL_BUTTON_L == event.control && (z_hold || a_hold)) {
        app->EditIOSettings();
        SetButtonIgnoreMask();
        continue;
      }
      // Hold Z and push A for screensaver (not available on O_C without VOR button)
      if (CONTROL_BUTTON_A == event.control && z_hold) {
        screensaver_ = true;
        SetButtonIgnoreMask();
        break;
      }
    }

    if (UI_MODE_SCREENSAVER == app->DispatchEvent(event)) {
      screensaver_ = true;
      // Break to handle screensaver; queued events will be handled next call
      break;
    }
  }

  // Turning screensaver seconds into screen-blanking minutes with the * 60 (chysn 9/2/2018)
  if (idle_time() > (screensaver_timeout() * 60) && !preempt_screensaver_)
    screensaver_ = true;

  if (screensaver_) {
    return UI_MODE_SCREENSAVER;
  } else if (jump_to_menu_) {
    SetButtonIgnoreMask(); // ignore release
    jump_to_menu_ = false;
    return UI_MODE_APP_SETTINGS;
  } else {
    return UI_MODE_MENU;
  }
}
