#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/adc.h"
#include "inc/pinout.h"                     // Biblioteca contendo a relação dos pinos da RP2040 utilizados no projeto.
#include "inc/oled_display/oled_display.h"  // Biblioteca do Display OLED.
#include <string.h>                         // Biblioteca para lidar com strings.

int main() {
    // Inicialização de STDI
    stdio_init_all();

    // Inicialização do ADC
    adc_init();
    
    // Configura os pinos GPIO 26 e 27 do Joystick
    adc_gpio_init(26);
    adc_gpio_init(27);

    // Loop infinito
    for(;;) {
        // Seleciona a entrada ADC 0 (conectada ao eixo X do joystick)
        adc_select_input(1);
        oled_display_init();    // Inicializa o Display OLED
        // Lê o valor do ADC para o eixo X
        uint adc_x_raw = adc_read();
        
        // Seleciona a entrada ADC 1 (conectada ao eixo Y do joystick)
        adc_select_input(0);

        // Lê o valor do ADC para o eixo Y
        uint adc_y_raw = adc_read();

        // Configuração da barra de exibição dos valores de X e Y no terminal
    // Mostra a posição do joystick de uma forma como esta: 
        // X: [            o             ]  Y: [              o         ]
        const uint bar_width = 100; // Define a largura da barra
        const uint adc_max = (1 << 12) - 1; // Valor máximo do ADC (12 bits, então 4095)
        
        // Calcula a posição do marcador 'o' na barra de X e Y com base nos valores lidos
        uint bar_x_pos = adc_x_raw * bar_width / adc_max;
        uint bar_y_pos = adc_y_raw * bar_width / adc_max;
        
        char *text[4] = {
            "",
            "",
            "",
            ""
        };
        
        char str_x[50];
        sprintf(str_x, "POSICAO X %d", adc_x_raw);
        text[0] = str_x;

        char str_y[50];
        sprintf(str_y, "POSICAO Y %d", adc_y_raw);
        text[1] = str_y;

        oled_display_write(text, count_of(text), 8);
        // Pausa o programa por 50 milissegundos antes de ler novamente
        sleep_ms(50);
    }
}