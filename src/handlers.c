#include <stdio.h>

#include <FreeRTOS.h>
#include <task.h>

#include <pico/stdlib.h>
#include <pico/multicore.h>
#include <pico/cyw43_arch.h>
#include "handlers.h"

#define LED_DELAY 1000

// Comments for review
bool on = false;
int count = 0;

void blink_task(__unused void *params) {
    hard_assert(cyw43_arch_init() == PICO_OK);
    while (true) {
        blink_led(&on, &count);
        vTaskDelay(LED_DELAY);
    }
}

void main_task(__unused void *params) {
    xTaskCreate(blink_task, "BlinkThread",
                BLINK_TASK_STACK_SIZE, NULL, BLINK_TASK_PRIORITY, NULL);
    char c;
    while(c = getchar()) {
        c = change_case(c);
        putchar(c);
    }
}