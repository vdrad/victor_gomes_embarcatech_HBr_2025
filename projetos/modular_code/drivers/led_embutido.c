#include "include/led_embutido.h"
#include "pico/stdlib.h"
#include "pico/cyw43_arch.h"

/**
 * Init Built-In LED of the Pico W
 */
uint8_t led_init() {
    if (cyw43_arch_init()) {
        return -1;
    }
}


/**
 * Turn On Built-In LED of the Pico W
 */
void led_on() {
    cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 1);
}

/**
 * Turn Off Built-In LED of the Pico W
 */
void led_off() {
    cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 0);
}