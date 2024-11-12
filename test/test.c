#include <stdio.h>
#include <pico/stdlib.h>
#include <stdint.h>
#include <unity.h>
#include <pico/cyw43_arch.h>
#include "unity_config.h"
#include "handlers.h"

void setUp(void) {}

void tearDown(void) {}

void test_change_case() {
    TEST_ASSERT_EQUAL('a', change_case('A'));
    TEST_ASSERT_EQUAL('A', change_case('a'));
    TEST_ASSERT_EQUAL('b', change_case('B'));
    TEST_ASSERT_EQUAL('B', change_case('b'));
    TEST_ASSERT_EQUAL('c', change_case('C'));
    TEST_ASSERT_EQUAL('C', change_case('c'));
    TEST_ASSERT_EQUAL('1', change_case('1'));
    TEST_ASSERT_EQUAL('!', change_case('!'));
    TEST_ASSERT_EQUAL('*', change_case('*'));
    TEST_ASSERT_EQUAL('x', change_case('X'));
    TEST_ASSERT_EQUAL('X', change_case('x'));
    TEST_ASSERT_EQUAL('y', change_case('Y'));
    TEST_ASSERT_EQUAL('Y', change_case('y'));
    TEST_ASSERT_EQUAL('z', change_case('Z'));
    TEST_ASSERT_EQUAL('Z', change_case('z'));
    TEST_ASSERT_EQUAL('\"', change_case('\"'));
}

void test_blink(void) {
    int count = 0;
    bool on = false;

    // Set the led off before test begins
    cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 0);

    for (int i = 0; i < 100; i++) {
        blink_led(&on, &count);

        // On has changed but LED hasn't yet when count % 1 is true. 
        if (count % 11) {
            TEST_ASSERT_NOT_EQUAL(on, cyw43_arch_gpio_get(CYW43_WL_GPIO_LED_PIN));
        }
        // On and the LED should be same value otherwise
        else {
            TEST_ASSERT_EQUAL(on, cyw43_arch_gpio_get(CYW43_WL_GPIO_LED_PIN));

        }
    }
}

int main (void)
{
    stdio_init_all();
    hard_assert(cyw43_arch_init() == PICO_OK); // Init the pico board
    sleep_ms(10000); // Give time for TTY to attach.
    printf("Start tests\n");
    UNITY_BEGIN();
    RUN_TEST(test_change_case);
    RUN_TEST(test_blink);
    sleep_ms(5000);
    return UNITY_END();
}
