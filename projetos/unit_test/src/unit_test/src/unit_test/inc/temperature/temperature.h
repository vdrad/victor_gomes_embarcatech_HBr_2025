#ifndef TEMPERATURE_H
#define TEMPERATURE_H

#include <stdint.h>

// MACROS DO ADC
#define ADC_TEMPERATURE_CHANNEL 4 // Canal do ADC vinculado ao sensor interno de temperatura

float adc_to_celsius(uint16_t adc_val);
void temperature_unit_test();

#endif // TEMPERATURE_H