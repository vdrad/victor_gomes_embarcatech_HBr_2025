#ifndef __LED_EMBUTIDO_H__ // Caso já tenha sido declarada em algum outro lugar, não declare novamente.
#define __LED_EMBUTIDO_H__

#include <stdint.h>

uint8_t led_init();
void led_on();
void led_off();

#endif