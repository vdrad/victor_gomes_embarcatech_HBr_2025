#include <stdio.h>             // Biblioteca padrão para entrada e saída, utilizada para printf.
#include "pico/stdlib.h"       // Biblioteca padrão para funções básicas do Pico, como GPIO e temporização.
#include "hardware/adc.h"      // Biblioteca para controle do ADC (Conversor Analógico-Digital).
#include "inc/pinout.h"                     // Biblioteca contendo a relação dos pinos da RP2040 utilizados no projeto.
#include "inc/oled_display/oled_display.h"  // Biblioteca do Display OLED.
#include <string.h>                         // Biblioteca para lidar com strings.

// MACROS DO ADC
#define ADC_TEMPERATURE_CHANNEL 4 // Canal do ADC vinculado ao sensor interno de temperatura

// Função para converter o valor lido do ADC para temperatura em graus Fahrenheint
float adc_to_temperature(uint16_t adc_value) {
    // Constantes fornecidas no datasheet do RP2040
    const float conversion_factor = 3.3f / (1 << 12);  // Conversão de 12 bits (0-4095) para 0-3.3V
    float voltage = adc_value * conversion_factor;     // Converte o valor ADC para tensão
    float temperature = (27.0f - (voltage - 0.706f) / 0.001721f) ;  // Equação fornecida para conversão de tensão em temperatura °C

    return temperature;
}

int main() {
    // Inicializa a comunicação serial para permitir o uso de printf
    stdio_init_all();
    oled_display_init();    // Inicializa o Display OLED
    // Inicializa o módulo ADC 
    adc_init();

    // Seleciona o canal 4 do ADC (sensor interno de temperatura)
    adc_set_temp_sensor_enabled(true);  // Habilita o sensor interno de temperatura 
    adc_select_input(ADC_TEMPERATURE_CHANNEL);  // Seleciona o canal do sensor interno de temperatura

    // Loop infinito para leitura contínua do valor de temperatura
    while (true) {
        // Lê o valor do ADC no canal selecionado (sensor de temperatura)
        uint16_t adc_value = adc_read();

        // Converte o valor do ADC para temperatura em graus Celsius
        float temperature = adc_to_temperature(adc_value);

        // Imprime a temperatura na comunicação serial
        // printf("Temperatura: %.2f °F\n", temperature);
        char *text[4] = {
            "TEMPERATURA",
            "",
            "",
            "23",                    
        };
        char str[10];
        sprintf(str, "%.0f C", temperature);
        text[3] = str;
        oled_display_write(text, count_of(text), 8);

        // Atraso de 1000 milissegundos (1 segundo) entre as leituras
        sleep_ms(1000);
    }

    return 0;
}
