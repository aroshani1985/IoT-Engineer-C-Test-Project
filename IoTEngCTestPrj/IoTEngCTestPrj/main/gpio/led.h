#ifndef _LED_H
#define _LED_H


#define BLINK_GPIO CONFIG_BLINK_GPIO


void configure_led(void);
void blink_led(int s_led_state);


#endif 
