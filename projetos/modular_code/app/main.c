#include "include/hal_led.h"
#include "include/led_embutido.h"
#include "pico/stdlib.h"

int main() {
    stdio_init_all();
    led_init();

    while (true) {
        hal_led_toggle();
    }
    return 0;
}