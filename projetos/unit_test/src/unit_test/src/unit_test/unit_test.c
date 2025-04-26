#include <stdio.h>             // Biblioteca padrão para entrada e saída, utilizada para printf.
#include "pico/stdlib.h"       // Biblioteca padrão para funções básicas do Pico, como GPIO e temporização.
#include "inc/temperature/temperature.h" // Biblioteca personalizada para conversão de temperatura.

int main() {
    stdio_init_all();

    printf("Unity Test for Temeprature Reading ADC -> DEGC");
    uint8_t result = temperature_unit_test();
    if (result == 1) {
        printf("TEST PASSED! Temperature Reading: %f", adc_to_celsius(0.706));
    } else {
        printf("TEST FAILED! Temperature Reading: %f | Expected: 26.8 °C ~ 27.2 °C", adc_to_celsius(0.706));
    }

    return 0;
}
