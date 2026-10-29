#include <Arduino.h>
#include "icons.h"
#include "OC_ADC.h"
#include "OC_digital_inputs.h"
#include "OC_app_switcher.h"
#include "OC_config.h"
#include "OC_core.h"
#include "OC_debug.h"
#include "OC_gpio.h"
#include "OC_menus.h"
#include "OC_ui.h"
#include "OC_strings.h"
#include "OC_apps.h"
#include "util/util_math.h"
#include "util/util_misc.h"
#include "src/extern/dspinst.h"
#include <malloc.h>

extern "C" char _ebss[], _heap_end[], *__brkval, _estack;

extern USBHost thisUSB;

#ifdef POLYLFO_DEBUG  
extern void POLYLFO_debug();
#endif // POLYLFO_DEBUG

#ifdef BBGEN_DEBUG  
extern void BBGEN_debug();
#endif // BBGEN_DEBUG

#ifdef ENVGEN_DEBUG  
extern void ENVGEN_debug();
#endif // ENVGEN_DEBUG

#ifdef BYTEBEATGEN_DEBUG  
extern void BYTEBEATGEN_debug();
#endif // BYTEBEATGEN_DEBUG

#ifdef H1200_DEBUG  
extern void H1200_debug();
#endif // H1200_DEBUG

#ifdef QQ_DEBUG  
extern void QQ_debug();
#endif // QQ_DEBUG

#ifdef ASR_DEBUG
extern void ASR_debug();
#endif // ASR_DEBUG

namespace OC {

namespace DEBUG {
  debug::AveragedCycles LOOP_cycles;
  debug::AveragedCycles ISR_cycles;
  debug::AveragedCycles UI_cycles;
  debug::AveragedCycles MENU_draw_cycles;
  uint32_t UI_event_count;
  uint32_t UI_max_queue_depth;
  uint32_t UI_queue_overflow;

  void Init() {
    debug::CycleMeasurement::Init();
    DebugPins::Init();
  }
}; // namespace DEBUG

FLASHMEM
static void debug_menu_ram() {

#ifdef __IMXRT1062__
  auto sp = (char*) __builtin_frame_address(0);
  auto stack = sp - _ebss;
  int heap = CORE::FreeRam(); // _heap_end - __brkval;
#else
  // T3.2
  char tos;
  int stack = &_estack - &tos;
  int heap = mallinfo().uordblks;
  int free = mallinfo().fordblks + (&tos - __brkval);

  graphics.setPrintPos(2, 32);
  graphics.printf("FREE  %7d (%dKB)", free, free >> 10);
#endif

  graphics.setPrintPos(2, 12);
  graphics.printf("STACK %7d (%dKB)", stack, stack >> 10);

  graphics.setPrintPos(2, 22);
  graphics.printf("HEAP  %7d (%dKB)", heap, heap >> 10);

}

FLASHMEM
static void debug_menu_core() {
  int y = 12;
  graphics.setPrintPos(2, y);
  graphics.printf("%uMHz %luus+%luus", F_CPU / 1000 / 1000, OC_CORE_TIMER_RATE, OC_UI_TIMER_RATE);

  y += 10;
  graphics.setPrintPos(2, y);
  uint32_t isr_us = debug::cycles_to_us(DEBUG::ISR_cycles.value());
  graphics.printf("CORE%3lu/%3lu/%3lu %2lu%%",
                  debug::cycles_to_us(DEBUG::ISR_cycles.min_value()),
                  isr_us,
                  debug::cycles_to_us(DEBUG::ISR_cycles.max_value()),
                  (isr_us * 100) /  OC_CORE_TIMER_RATE);

  y += 10;
  graphics.setPrintPos(2, y);
  graphics.printf("POLL%3lu/%3lu/%3lu",
                  debug::cycles_to_us(DEBUG::UI_cycles.min_value()),
                  debug::cycles_to_us(DEBUG::UI_cycles.value()),
                  debug::cycles_to_us(DEBUG::UI_cycles.max_value()));

#ifdef OC_DEBUG_UI
  y += 10;
  graphics.setPrintPos(2, y);
  graphics.printf("UI   !%lu #%lu", DEBUG::UI_queue_overflow, DEBUG::UI_event_count);
#endif

  y += 10;
  graphics.setPrintPos(2, y);
  graphics.printf("LOOP%3lu/%3lu/%3lu",
                  debug::cycles_to_us(DEBUG::LOOP_cycles.min_value()),
                  debug::cycles_to_us(DEBUG::LOOP_cycles.value()),
                  debug::cycles_to_us(DEBUG::LOOP_cycles.max_value()));
}

FLASHMEM
static void debug_menu_version()
{
  static int hwid = int(GetIDVoltage() * 1000);

  graphics.setPrintPos(2, 12);
  graphics.print(Strings::NAME);
  graphics.setPrintPos(2, 22);
  graphics.print(Strings::VERSION);
  graphics.setPrintPos(2, 32);
  graphics.print(Strings::BUILD_TAG);

#ifdef OC_DEV
  graphics.print(" DEV");
#else
  graphics.print(" PROD");
#endif

  graphics.setPrintPos(2, 42);
  graphics.print("usb=");
#if defined(USB_MIDI) || defined (USB_MIDI_AUDIO_SERIAL)
  graphics.print("MIDI");
#endif
#if defined(AUDIO_INTERFACE)
  graphics.print("+Audio");
#endif
#ifdef USB_MTPDISK
  graphics.print("+MTP");
#endif
#ifdef USB_SERIAL
  graphics.print("+Serial");
#endif

#ifdef __IMXRT1062__
  graphics.setPrintPos(2, 52);
  graphics.printf("HW_ID= 0.%03dV", hwid);
  if (DAC_20Vpp) graphics.print(", 20Vpp");
#endif
}

FLASHMEM
static void debug_menu_gfx() {
  graphics.drawFrame(0, 0, 128, 64);

  graphics.setPrintPos(0, 12);
  graphics.print("W");

  graphics.setPrintPos(2, 22);
  graphics.printf("MENU %3lu/%3lu/%3lu",
                  debug::cycles_to_us(DEBUG::MENU_draw_cycles.min_value()),
                  debug::cycles_to_us(DEBUG::MENU_draw_cycles.value()),
                  debug::cycles_to_us(DEBUG::MENU_draw_cycles.max_value()));
}

FLASHMEM
static void debug_menu_adc() {
  graphics.setPrintPos(2, 12);
  graphics.printf("C1 %5ld %5lu", ADC::value<ADC_CHANNEL_1>(), ADC::raw_value(ADC_CHANNEL_1));

  graphics.setPrintPos(2, 22);
  graphics.printf("C2 %5ld %5lu", ADC::value<ADC_CHANNEL_2>(), ADC::raw_value(ADC_CHANNEL_2));

  graphics.setPrintPos(2, 32);
  graphics.printf("C3 %5ld %5lu", ADC::value<ADC_CHANNEL_3>(), ADC::raw_value(ADC_CHANNEL_3));

  graphics.setPrintPos(2, 42);
  graphics.printf("C4 %5ld %5lu", ADC::value<ADC_CHANNEL_4>(), ADC::raw_value(ADC_CHANNEL_4));
  const uint8_t trigz[] = {
    DigitalInputs::read_immediate<DIGITAL_INPUT_1>(),
    DigitalInputs::read_immediate<DIGITAL_INPUT_2>(),
    DigitalInputs::read_immediate<DIGITAL_INPUT_3>(),
    DigitalInputs::read_immediate<DIGITAL_INPUT_4>()
  };
  graphics.setPrintPos(2, 52);
  graphics.printf("T1=%u T2=%u T3=%u T4=%u", trigz[0], trigz[1], trigz[2], trigz[3]);
}


#ifdef PEWPEWPEW
FLASHMEM
static void debug_menu_pewpewpew() {
  uint32_t i = 0;
  do {
    graphics.drawBitmap8(i*8 % 120, (i+8) % 56, 8, ZAP_ICON);
  } while (++i < (millis() / 10 % 64));
}
#endif

#ifdef OC_DEBUG_ADC_STATS
FLASHMEM
static void debug_menu_adc2() {
  weegfx::coord_t y = 12;
  for (int channel = 0; channel < ADC_CHANNEL_COUNT; ++channel) {
    auto &stats = ADC::get_channel_stats(static_cast<ADC_CHANNEL>(channel));
    graphics.setPrintPos(2, y);
    graphics.printf("CV%d %5d %5d", channel + 1, stats.min, stats.max);
    y += 10;
  }
}
#endif

FLASHMEM
static void debug_menu_app() {
  auto app = app_switcher.current_app();
  if (app) {
    graphics.print(app->name());
    app->DrawDebugInfo();
  } else {
    graphics.print("?");
  }
}

struct DebugMenu {
  const char *title;
  void (*display_fn)();
};

static const DebugMenu debug_menus[] = {
  { "CORE", debug_menu_core },
#ifdef __IMXRT1062__
  { "RAM (free)", debug_menu_ram },
#else
  { "RAM", debug_menu_ram },
#endif
  { "VERS", debug_menu_version },
  { "GFX", debug_menu_gfx },
  { "ADC", debug_menu_adc },
#ifdef OC_DEBUG_ADC_STATS
  { "ADC min/max", debug_menu_adc2 },
#endif
#ifdef POLYLFO_DEBUG  
  { "POLYLFO", POLYLFO_debug },
#endif // POLYLFO_DEBUG
#ifdef ENVGEN_DEBUG  
  { "ENVGEN", ENVGEN_debug },
#endif // ENVGEN_DEBUG
#ifdef BBGEN_DEBUG  
  { "BBGEN", BBGEN_debug },
#endif // BBGEN_DEBUG
#ifdef BYTEBEATGEN_DEBUG  
  { "BYTEBEATGEN", BYTEBEATGEN_debug },
#endif // BYTEBEATGEN_DEBUG
#ifdef H1200_DEBUG  
  { "H1200", H1200_debug },
#endif // H1200_DEBUG
#ifdef QQ_DEBUG  
  { "QQ", QQ_debug },
#endif // QQ_DEBUG
#ifdef ASR_DEBUG  
  { "ASR", ASR_debug },
#endif // ASR_DEBUG
  { " ", debug_menu_app },
#ifdef PEWPEWPEW
  { "PEW PEW PEW!", debug_menu_pewpewpew },
#endif
};

void midi_monitor() {
}

void Ui::DebugStats() {
  SERIAL_PRINTLN("DEBUG/STATS MENU");

  int current_menu_index = 0;
  bool exit_loop = false;
  uint32_t loopcount = 0;
  while (!exit_loop) {
    OC_DEBUG_PROFILE_SCOPE(DEBUG::LOOP_cycles);
    // Run current app
    if (CORE::app_loop_enabled)
      app_switcher.current_app()->DispatchLoop();
    else {
      // typically only happens from Boot menu
      midi_monitor();
    }

    thisUSB.Task();
    CORE::FlushTasks();

    const auto &current_menu = debug_menus[current_menu_index];

    GRAPHICS_BEGIN_FRAME(false);
      graphics.setPrintPos(2, 2);
      graphics.printf("%d/%u ", current_menu_index + 1, ARRAY_SIZE(debug_menus));
      graphics.print(current_menu.title);
      current_menu.display_fn();
    GRAPHICS_END_FRAME();

    while (event_queue_.available()) {
      UI::Event event = event_queue_.PullEvent();
      if (UI::EVENT_ENCODER == event.type && CONTROL_ENCODER_L == event.control) {
        current_menu_index = current_menu_index + event.value;
      } else if (UI::EVENT_BUTTON_PRESS == event.type) {
        if (CONTROL_BUTTON_R == event.control)
          exit_loop = true;
        if (CONTROL_BUTTON_L == event.control)
          ++current_menu_index;
      }
    }
    CONSTRAIN(current_menu_index, 0, (int)ARRAY_SIZE(debug_menus) - 1);

    ++loopcount;
    OC_DEBUG_RESET_CYCLES(loopcount, 0x1000000, DEBUG::LOOP_cycles);
    yield();
    //delayMicroseconds(10);
  }

  event_queue_.Flush();
  event_queue_.Poke();
}

} // namespace OC
