#include <Arduino.h>
#include <algorithm>
#include "HSUtils.h"
#include "OC_DAC.h"
#include "OC_digital_inputs.h"
#include "OC_gpio.h"
#include "OC_ADC.h"

// default settings for traditional O_C hardware wired for Teensy 3.2
//uint8_t CV1=19, CV2=18, CV3=20, CV4=17;
uint8_t TR1=0, TR2=1, TR3=2, TR4=3;
uint8_t OLED_DC=6, OLED_RST=7, OLED_CS=8;
uint8_t DAC_CS=10, DAC_RST=9;
uint8_t encL1=22, encL2=21, butL=23, encR1=16, encR2=15, butR=14;
uint8_t but_top=5, but_bot=4, but_mid=9, but_top2=255, but_bot2=255;
uint8_t OC_GPIO_DEBUG_PIN1=24, OC_GPIO_DEBUG_PIN2=25;
bool ADC33131D_Uses_FlexIO=false;
bool OLED_Uses_SPI1=false;
bool Large_OLED=false;
bool DAC8568_Uses_SPI=false;
bool I2S2_Audio_ADC=false;
bool I2S2_Audio_DAC=false;
bool I2C_Expansion=false;
bool MIDI_Uses_Serial8=false;
float id_voltage = 0.0;
bool flip_mode = false;
bool SDcard_Ready = false;

float OC::GetIDVoltage() {
  return OC::ADC::Read_ID_Voltage();
}
int OC::GetIDIndex() {
  return 1; // Standard O_C Teensy 4.0 hardware.
}

FLASHMEM
void OC::SetFlipMode(bool flip_180) {
  flip_mode = flip_180;

  if (CalSynthXL) return; // TODO:

  if (flip_180) {
    // reversed
    if (id_voltage >= 0.05f) {
      // new hardware
      but_top  = 15;
      but_top2 = 14;
      but_bot  = 28;
      but_bot2 = 29;

      encR1 = 30;
      encR2 = 31;
      butR  = 24;
      encL1 = 36;
      encL2 = 37;
      butL  = 25;

      TR4 = 0;
      TR3 = 1;
      TR2 = 23;
      TR1 = 22;
    } else {
      // old hardware
#ifdef NLM_hOC
      but_top = 5;
      but_bot = 4;
#else
      but_top = 4;
      but_bot = 5;
#endif

      encR2 = 22;
      encR1 = 21;
      butR  = 23;
      encL2 = 16;
      encL1 = 15;
      butL  = 14;

      //CV4 = 19;
      //CV3 = 18;
      //CV2 = 20;
      //CV1 = 17;
      TR4 = 0;
      TR3 = 1;
      TR2 = 2;
      TR1 = 3;
    }
  } else {
    // default orientation
    if (id_voltage >= 0.05f) {
      // new hardware
      but_top  = 29;
      but_top2 = 28;
      but_bot  = 14;
      but_bot2 = 15;

      encL1 = 30;
      encL2 = 31;
      butL  = 24;
      encR1 = 36;
      encR2 = 37;
      butR  = 25;

      TR1 = 0;
      TR2 = 1;
      TR3 = 23;
      TR4 = 22;
    } else {
      // old hardware
#ifdef NLM_hOC
      but_top = 4;
      but_bot = 5;
#else
      but_top = 5;
      but_bot = 4;
#endif

      encL1 = 22;
      encL2 = 21;
      butL  = 23;
      encR1 = 16;
      encR2 = 15;
      butR  = 14;

      //CV1 = 19;
      //CV2 = 18;
      //CV3 = 20;
      //CV4 = 17;
      TR1 = 0;
      TR2 = 1;
      TR3 = 2;
      TR4 = 3;
    }
  }
}
