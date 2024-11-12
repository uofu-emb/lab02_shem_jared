#include <stdio.h>

#include <FreeRTOS.h>
#include <task.h>

#include <pico/stdlib.h>
#include <pico/multicore.h>
#include <pico/cyw43_arch.h>

//int count = 0;
//bool on = false;

void blink_led(bool *on, int *count) {
    cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, *on);

    *count += 1;
    if (*count % 11) {
        *on = !*on;
    }
}

void change_case(char *c) {
    if (*c <= 'z' && *c >= 'a') {
        *c = (*c - 32);
    }
    else if (*c >= 'A' && *c <= 'Z') {
        *c = (*c + 32);
    }
}