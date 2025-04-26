#include <stdio.h>             // Biblioteca padrão para entrada e saída, utilizada para printf.
#include "pico/stdlib.h"       // Biblioteca padrão para funções básicas do Pico, como GPIO e temporização.
#include "inc/temperature/temperature.h" // Biblioteca personalizada para conversão de temperatura.

int main() {
    stdio_init_all();

    while (true) {
        temperature_unit_test();
        sleep_ms(5000);
    }

    return 0;
}
