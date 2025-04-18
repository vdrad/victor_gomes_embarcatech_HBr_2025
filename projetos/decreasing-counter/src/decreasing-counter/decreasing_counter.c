#include <stdio.h>
#include "pico/stdlib.h"
#include <string.h>                         // Biblioteca para lidar com strings.
#include "hardware/timer.h"
#include "inc/pinout.h"                     // Biblioteca contendo a relação dos pinos da RP2040 utilizados no projeto.
#include "inc/oled_display/oled_display.h"  // Biblioteca do Display OLED.
#include "inc/buttons/buttons.h"            // Biblioteca do Botão.
// State machine
typedef enum {
    WAITING,
    COUNTING_STARTED,
    COUNTING,
    COUNTING_FINISHED
} STATES;
STATES current_state = WAITING;

uint8_t time_count      = 9;
uint8_t b_button_count  = 0;

bool alarm_callback();
void exibe_contagens_no_display(bool ini);

int main() {

    stdio_init_all();
    oled_display_init();    // Inicializa o Display OLED
    button_init('A');       // Inicializa o Botão A
    button_init('B');       // Inicializa o Botão B

    static struct repeating_timer count_timer;  // Cria a estrutura de timer ciclico
    // add_repeating_timer_us(100 *1000, alarm_callback, &{count}, &count_timer); // Configura a função para ser executada a cada 100 ms
    // cancel_repeating_timer(&count_timer);

    for(;;) {
        switch(current_state) {
            case WAITING:
                exibe_contagens_no_display(true);
                while(get_a_button_state() == false);
                current_state = COUNTING_STARTED;
                break;
            case COUNTING_STARTED:
                time_count      = 9;
                b_button_count  = 0;
                add_repeating_timer_ms(1*1000, alarm_callback, NULL, &count_timer);

                current_state = COUNTING;
                break;
            case COUNTING:
                exibe_contagens_no_display(false);
                if (time_count == 0) current_state = COUNTING_FINISHED;
                if (get_b_button_state()) b_button_count++;
                break;
            case COUNTING_FINISHED:
                exibe_contagens_no_display(false);
                cancel_repeating_timer(&count_timer);
                current_state = WAITING;
                break;
            default:
                break;
        }
    }
}

bool alarm_callback() {
    if (time_count == 0) return true;
    time_count--;
    return true;
}

void exibe_contagens_no_display(bool ini) {
    char *text[4] = {
        "Aperte o BOTAO ",
        "A para comecar",
        "Contagem  ",
        "Botao B ",                    
    };

    if (!ini) {
        text[0] = "";
        text[1] = "";
    } 

    char count_string[20];
    char button_string[20];
    // Transforma a contagem de tempo em texto e concatena 
    sprintf(count_string, "Contagem %d", time_count);
    text[2] = count_string;

    // Transforma a contagem de pressionamentos do botão em texto e concatena 
    sprintf(button_string, "Botao B %d", b_button_count);
    text[3] = button_string;

    oled_display_write(text, count_of(text), 8);
}
