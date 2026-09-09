#include <stdio.h>
#include <unistd.h>

#include <driver/gpio.h>

#define LED_PIN GPIO_NUM_2

void app_main(void)
{
    gpio_reset_pin(LED_PIN);

    gpio_config_t gpio_out_config = {
        .intr_type = GPIO_INTR_DISABLE,
        .mode = GPIO_MODE_OUTPUT,
        .pin_bit_mask = (1UL << LED_PIN),
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .pull_up_en = GPIO_PULLUP_DISABLE
    };

    gpio_config(&gpio_out_config);

    while(1)
    {
        gpio_set_level(LED_PIN, 1);
        sleep(1);
        
        gpio_set_level(LED_PIN, 0);
        sleep(1);
    }

}