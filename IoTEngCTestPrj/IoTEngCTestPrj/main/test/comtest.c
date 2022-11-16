#include <stdio.h>
#include "esp_log.h"
#include "encdec.h"
#include "pktformat.h"
#include "pktreceive.h"


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

void Test_02_packet_format()
{
	// consider to access allocated memory out side of pkt_process,dont free it.
	int i = 0;
	int frame_len = 255; // contaner for packet 
	//////////////////////// sample correct packet 
	int payload_len = 20; 
	uint8_t pkt[frame_len];
	pkt[0] = 0xAA;
	pkt[1] = 0x00;
	pkt[2] = 0x01;
	pkt[3] = payload_len;
	
	for (i = 0; i < payload_len; i++)
	{
		pkt[4 + i] = i + 10;
	}
	//////////////////////////////////////////////////
	init_receive_process_flags(false);
	Communication_onDataReceived(pkt, frame_len);
	/////////////////////////////////////check status and print packet parameters
	if (rec_pkt_flags.status)
	{
		ESP_LOGI(TAG_TEST_COM,
			"Packet is valid\n CMD: 0x%04X \nPayload len: %d \n D[0] ... D[4]: %hhu %hhu %hhu %hhu %hhu",
			rec_pkt_params.cmd,
			rec_pkt_params.len,
			rec_pkt_params.payloadp[0],
			rec_pkt_params.payloadp[1],
			rec_pkt_params.payloadp[2],
			rec_pkt_params.payloadp[3],
			rec_pkt_params.payloadp[4]);
	}
	else // in case of error print error
	{
		ESP_LOGI(TAG_TEST_COM, "Invalid Packet, Error Code: %d", rec_pkt_flags.err_code);
		switch (rec_pkt_flags.err_code) 
		{
		case ERR_INV_FRAME:
			ESP_LOGI(TAG_TEST_COM, "ERR_INV_FRAME");
			break;
			
		case ERR_OUT_OF_MEM:
			ESP_LOGI(TAG_TEST_COM, "ERR_OUT_OF_MEM");
			break;
			
		case ERR_PKT_INV_LEN:
			ESP_LOGI(TAG_TEST_COM, "ERR_PKT_INV_LEN");
			break;
			
		case ERR_PKT_INV_START:
			ESP_LOGI(TAG_TEST_COM, "ERR_PKT_INV_START");
			break;
			
		default:
			ESP_LOGI(TAG_TEST_COM, "UnKnown Code");
			break;
		}
	}		
	free_receive_resources();
	/////////////////////////////////// output
	/*
	  TestComm: Packet is valid
      CMD: 0x0001 
      Payload len: 20 
      D[0] ... D[4]: 10 11 12 13 14.[0m
	 */
}