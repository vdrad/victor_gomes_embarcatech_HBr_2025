#include "temperature.h"
#include <math.h>

// Função para converter o valor lido do ADC para temperatura em graus Fahrenheint
float adc_to_celsius(uint16_t adc_val) {
    // Constantes fornecidas no datasheet do RP2040
    const float conversion_factor = 3.3f / (1 << 12);  // Conversão de 12 bits (0-4095) para 0-3.3V
    float voltage = adc_val * conversion_factor;     // Converte o valor ADC para tensão
    float temperature = (27.0f - (voltage - 0.706f) / 0.001721f) ;  // Equação fornecida para conversão de tensão em temperatura °C

    return temperature;
}

uint8_t temperature_unit_test() {
    // 0.706V ~= 27 °C
    float result = adc_to_celsius(0.706);
    float margin = 0.2;

    if (fabs(result - 27.0f) <= margin) return 1;
    return -1;
}