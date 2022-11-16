#include <stdio.h>
#include "esp_log.h"
#include "encdec.h"
#include "pktformat.h"
#include "pktreceive.h"
#include "cmdhandler.h"


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
			
		case ERR_OUT_OF_MEM1:
			ESP_LOGI(TAG_TEST_COM, "ERR_OUT_OF_MEM1");
			break;
			
		case ERR_PKT_INV_LEN:
			ESP_LOGI(TAG_TEST_COM, "ERR_PKT_INV_LEN");
			break;
			
		case ERR_PKT_INV_START:
			ESP_LOGI(TAG_TEST_COM, "ERR_PKT_INV_START");
			break;
			
		case ERR_OUT_OF_MEM2:
			ESP_LOGI(TAG_TEST_COM, "ERR_OUT_OF_MEM2");
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

void Test_03_fcn_dispacher()
{
	int i = 0;
	
	for (i = 0; i < CMD_COUNT; i++)
	{
		cmd_process_array[i](NULL, 0, NULL);
		ESP_LOGI(TAG_TEST_COM, "CMD[%d], ItemCount: %d", i, cmd_handle_params.items_count);
	}
	/////////////////////////////////////////////output
	/*
	TestComm : CMD[0], ItemCount : 10
	TestComm : CMD[1], ItemCount : 1001
	TestComm : CMD[2], ItemCount : 1002
	TestComm : CMD[3], ItemCount : 1003
	TestComm : CMD[4], ItemCount : 1004
	TestComm : CMD[5], ItemCount : 1005
	TestComm : CMD[6], ItemCount : 1006
	TestComm : CMD[7], ItemCount : 1007
	TestComm : CMD[8], ItemCount : 1008
	TestComm : CMD[9], ItemCount : 1009
	*/
}

void Test_04_Communication_onDataReceived_s1()
{
	int i = 0;
	int frame_len = 64;
	int payload_len = 32;
	uint8_t pkt[frame_len];
	pkt[0] = 0xAA;
	pkt[1] = 0x00;
	pkt[2] = 0x01;
	pkt[3] = payload_len;
	pkt[5] = 100;
	init_receive_process_flags(false);
	for (i = 0; i < CMD_COUNT; i++)
	{
		pkt[2] = i; //set cmd
		
		Communication_onDataReceived(pkt, frame_len);
		ESP_LOGI(TAG_TEST_COM, "CMD[%d], ItemCount: %d\n", i, cmd_handle_params.items_count);
		free_receive_resources();
	}
	
	/* Output 
		Send fcn: Communication_openResponse
		Send fcn: Communication_closeResponse
		TestComm: CMD[0], ItemCount: 10
     
		Send fcn: Communication_openResponse
		Send fcn: Communication_closeResponse
		TestComm: CMD[1], ItemCount: 1001

		Send fcn: Communication_openResponse
		Send fcn: Communication_closeResponse
		TestComm: CMD[2], ItemCount: 1002

		Send fcn: Communication_openResponse
		Send fcn: Communication_closeResponse
		TestComm: CMD[3], ItemCount: 1003

		Send fcn: Communication_openResponse
		Send fcn: Communication_closeResponse
		TestComm: CMD[4], ItemCount: 1004.[0m

		Send fcn: Communication_openResponse
		Send fcn: Communication_closeResponse
		TestComm: CMD[5], ItemCount: 1005.

		Send fcn: Communication_openResponse
		Send fcn: Communication_closeResponse
		TestComm: CMD[6], ItemCount: 1006

		Send fcn: Communication_openResponse
		Send fcn: Communication_closeResponse
		TestComm: CMD[7], ItemCount: 1007

		Send fcn: Communication_openResponse
		Send fcn: Communication_closeResponse
		TestComm: CMD[8], ItemCount: 1008

		Send fcn: Communication_openResponse
		Send fcn: Communication_closeResponse
		TestComm: CMD[9], ItemCount: 1009
	 */
}

void Test_05_Communication_onDataReceived_s2_10_items(uint16_t CMD_ID)
{
	int i = 0;
	int frame_len = 64;
	int payload_len = 32;
	uint8_t pkt[frame_len];
	pkt[0] = 0xAA;
	pkt[1] = CMD_ID >> 8;;
	pkt[2] = CMD_ID;
	pkt[3] = payload_len;
	pkt[5] = 100;
	init_receive_process_flags(false);

	Communication_onDataReceived(pkt, frame_len);
	ESP_LOGI(TAG_TEST_COM, "CMD[0x%04x], ItemCount: %d\n", CMD_ID, cmd_handle_params.items_count);
	free_receive_resources();
	
	/*
	 Send fcn: Communication_openResponse
     Send fcn: Send result: A0 01 0A A0 02 0A A0 03 0A A0 04
     Send fcn: Send result: 0A A0 05 0A A0 06 0A A0 07 0A A0
     Send fcn: Send result: 08 0A A0 09 0A A0 0A 0A 
     Send fcn: Send result: 0D 0A 
     Send fcn: Communication_closeResponse
     TestComm: CMD[0], ItemCount: 10
	 */	
	
     /*  output for 20 item, with header and footer
	 Send fcn: Communication_openResponse
     Send fcn: Send result: AA 00 01 00
     Send fcn: Send result: A0 01 0A A0 02 0A A0 03 0A A0 04
     Send fcn: Send result: 0A A0 05 0A A0 06 0A A0 07 0A A0
     Send fcn: Send result: 08 0A A0 09 0A A0 0A 0A A0 0B 0A
     Send fcn: Send result: A0 0C 0A A0 0D 0A A0 0E 0A A0 0F
     Send fcn: Send result: 0A A0 10 0A A0 11 0A A0 12 0A A0
     Send fcn: Send result: 13 0A A0 14 0A 
     Send fcn: Send result: 0D 0A 
     Send fcn: Communication_closeResponse
     TestComm: CMD[0x0001], ItemCount: 20
	 */
}