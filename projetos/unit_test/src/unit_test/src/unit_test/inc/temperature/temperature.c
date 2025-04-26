#include "temperature.h"
#include <math.h>
#include <stdio.h>             // Biblioteca padrão para entrada e saída, utilizada para printf.

// Função para converter o valor lido do ADC para temperatura em graus Fahrenheint
float adc_to_celsius(uint16_t adc_val) {
    // Constantes fornecidas no datasheet do RP2040
    const float conversion_factor = 3.3f / (1 << 12);  // Conversão de 12 bits (0-4095) para 0-3.3V
    float voltage = adc_val * conversion_factor;     // Converte o valor ADC para tensão
    float temperature = (27.0f - (voltage - 0.706f) / 0.001721f) ;  // Equação fornecida para conversão de tensão em temperatura °C

    return temperature;
}

void temperature_unit_test() {
    // 0.706V ~= 876 (ADC) ~= 27 °C
    float margin = 0.2;
    float result = adc_to_celsius(876);

    printf("\nUnity Test for Temeprature Reading ADC -> °C \n");
    if (fabs(result - 27.0f) <= margin) {
        printf("TEST PASSED! Temperature Reading: %.2f \n", adc_to_celsius(876));
    } else {
        printf("TEST FAILED! Temperature Reading: %.2f | Expected: 26.8 °C ~ 27.2 °C \n", adc_to_celsius(876));
    }
}