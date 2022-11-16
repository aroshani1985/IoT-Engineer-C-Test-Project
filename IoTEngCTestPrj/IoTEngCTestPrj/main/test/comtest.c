#include <stdio.h>
#include "esp_log.h"
#include "encdec.h"


static const char *TAG_TEST_COM = "TestComm";

void Test_01_enc_dec_fcn()
{
	int i = 0;
	int idx = 0;
	int frame_len = 260; //buffer size longer than 255, buffer limit
	char buff[32];       //small buffer for partial print 
	
	uint8_t pkt_in[frame_len];  // input buffer for encryption or decription
	uint8_t pkt_out[frame_len]; // output buffer for encryption or decription
	
	//////////////////////////////////initialiaze buffer for test 
	for (i = 0; i < frame_len; i++)
	{
		pkt_in[i] = i;
	}
	// just test that can handle more than 255 bytes of data for decriptin
	encrypt_decrypt_packet(pkt_in, frame_len, pkt_out, true);
	
	for (int i = 0; i < frame_len; i++)
	{
		if (idx >= 32)
		{
			idx = 0;
			ESP_LOGI(TAG_TEST_COM, "Enc result: %s", buff);
		}
		idx += sprintf(buff + idx, "%hhu ", pkt_out[i]);
	}
	ESP_LOGI(TAG_TEST_COM, "Enc result: %s", buff);
	
	
	for (i = 0; i < frame_len; i++)
	{
		pkt_in[i] = 2;
	}
	
	// just test that can handle more than 255 bytes of data for encryption
	encrypt_decrypt_packet(pkt_in, frame_len, pkt_out, false);
	
	idx = 0;
	for (int i = 0; i < frame_len; i++)
	{
		if (idx >= 32)
		{
			idx = 0;
			ESP_LOGI(TAG_TEST_COM, "Dec result: %s", buff);
		}
		idx += sprintf(buff + idx, "%hhu ", pkt_out[i]);
	}
	ESP_LOGI(TAG_TEST_COM, "Dec result: %s", buff);
}