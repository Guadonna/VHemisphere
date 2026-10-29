#ifndef OC_GPIO_H_
#define OC_GPIO_H_

#include "OC_options.h"

// All platforms now have dynamic pinouts.
// Controls can be remapped, and flip_180 is a calibration flag.

// extern uint8_t CV1, CV2, CV3, CV4;
extern uint8_t TR1, TR2, TR3, TR4;
extern uint8_t OLED_DC, OLED_RST, OLED_CS;
extern uint8_t DAC_CS, DAC_RST;
extern uint8_t encL1, encL2, butL, encR1, encR2, butR;
extern uint8_t but_top, but_bot, but_mid, but_top2, but_bot2;
extern uint8_t OC_GPIO_DEBUG_PIN1, OC_GPIO_DEBUG_PIN2;
extern bool ADC33131D_Uses_FlexIO;
extern bool OLED_Uses_SPI1;
extern bool Large_OLED;
extern bool DAC8568_Uses_SPI;
extern bool I2S2_Audio_ADC;
extern bool I2S2_Audio_DAC;
extern bool I2C_Expansion;
extern bool MIDI_Uses_Serial8;
extern bool SDcard_Ready;
static constexpr bool DAC_20Vpp = false;
static constexpr bool CalSynthXL = false;
static constexpr bool DAC_is_inverted = false;
static constexpr bool NLMSerge = false;

#ifdef NORTHERNLIGHT
static constexpr bool NorthernLightModular = true;
#else
static constexpr bool NorthernLightModular = false;
#endif

// OLED CS is active low
#define OLED_CS_ACTIVE LOW
#define OLED_CS_INACTIVE HIGH

#define OC_GPIO_BUTTON_PINMODE INPUT_PULLUP
#define OC_GPIO_TRx_PINMODE INPUT_PULLUP
#define OC_GPIO_ENC_PINMODE INPUT_PULLUP

namespace OC { 

  void Pinout_Detect();
  void SetFlipMode(bool flip_180);
  float GetIDVoltage();
  int GetIDIndex();
}

#endif // OC_GPIO_H_
