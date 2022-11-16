#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "driver/gpio.h"
#include "led.h"

void blink_led(int s_led_state)
{
	gpio_set_level(BLINK_GPIO, s_led_state);
}


void configure_led(void)
{
	gpio_reset_pin(BLINK_GPIO);
	gpio_set_direction(BLINK_GPIO, GPIO_MODE_OUTPUT);	
}
