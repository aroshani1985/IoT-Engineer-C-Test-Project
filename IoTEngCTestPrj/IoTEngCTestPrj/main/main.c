#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "esp_log.h"
#include "led_strip.h"
#include "sdkconfig.h"
#include "led.h"
#include "comtest.h"

static const char *TAG = "IoTEngCTestPrj";
static uint8_t s_led_state = 0;


void app_main(void)
{
	////////////////////// Test encryption and decription wrapper 
	//Test_01_enc_dec_fcn();
	///////////////////////// Test packrt format functions
	//Test_02_packet_format();
    ////////////////////////////// Test function dispacher
	//Test_03_fcn_dispacher();
	/////////////////////////////// Test Communication_onDataReceived Step 1
	//Test_04_Communication_onDataReceived_s1();
	//////////////////////////////////////
	Test_05_Communication_onDataReceived_s2_10_items();
	//////////////////////////////////////////////
    configure_led();
    while (1) 
    {
        ESP_LOGI(TAG, "Turning the LED %s!", s_led_state == true ? "ON" : "OFF");
	    blink_led(s_led_state);
        /* Toggle the LED state */
        s_led_state = !s_led_state;
        vTaskDelay(CONFIG_BLINK_PERIOD / portTICK_PERIOD_MS);
    }
}
