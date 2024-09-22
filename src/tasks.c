#include <stdio.h>

#include <FreeRTOS.h>
#include <task.h>

#include <pico/stdlib.h>
#include <pico/multicore.h>
#include <pico/cyw43_arch.h>

int count = 0;
bool on = false;
blink_led() {
    cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, on);
    if (count++ % 11) on = !on;
    vTaskDelay(500);
}