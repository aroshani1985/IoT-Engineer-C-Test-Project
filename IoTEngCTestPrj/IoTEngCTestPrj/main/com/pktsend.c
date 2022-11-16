#include "pktsend.h"
#include "esp_log.h"
#include "cmdhandler.h"
#include "pktformat.h"

//just simple implementation for test purposes
void Communication_openResponse()
{
	ESP_LOGI("Send fcn", "Communication_openResponse");
}

//just simple implementation for test purposes
void Communication_closeResponse()
{
	ESP_LOGI("Send fcn", "Communication_closeResponse");
}

//just simple implementation for test purposes
void Communication_sendData(uint8_t* data, uint16_t length)
{
	int i;
	int idx = 0;   // index for collecting data to buffer
	char buff[32]; // small buffer for print data 
	////////////////////////////////////
	for (i = 0; i < length; i++)
	{
		if (idx >= 32)
		{
			idx = 0;
			ESP_LOGI("Send fcn", "Send result: %s", buff);
		}
		idx += sprintf(buff + idx, "%02X ", data[i]);    // hex like 0xAA print
		//idx += sprintf(buff + idx, "%hhu ", data[i]);  // desimal print
		//idx += sprintf(buff + idx, "%c", data[i]);     // char print
	}
	if(idx < 32 && idx!= 0)
	   ESP_LOGI("Send fcn", "Send result: %s", buff);
}

//just simple implementation for test purposes
void Communication_appendResponse(uint8_t* data, uint16_t  length)
{
	// pattern for 1 and 3 bytes length: A010A A010A A010A 
	// pattern for 1 and 5 bytes length: A01110A A01110A A01110A 
	uint16_t i;
	data[0] = 0xA0;
	data[length-1] = 0x0A;
	for (i = 1; i < length-1; i++)
		data[i] = cmd_handle_params.curr_item;
}

// send protocol header 4 byte in response packet
void Communication_send_Header_Packet(uint16_t CMDIs)
{
	uint8_t data_buff[PACKET_HEADER_LEN];
	//////////////////////////////////
	data_buff[0] = PACKET_START;
	data_buff[1] = CMDIs>>8;
	data_buff[2] = CMDIs;
	data_buff[3] = 0; // length of reply is unknown

	////////////////////////////////////
	Communication_sendData(data_buff, PACKET_HEADER_LEN);
}

// send protocol footer 2 byte
void Communication_send_EndOfPacket()
{
	uint8_t data_buff[PACKET_FOOTER_LEN];
	//////////////////////////////////
	data_buff[0] = PACKET_EOF1;
	data_buff[1] = PACKET_EOF2;
	////////////////////////////////////
	Communication_sendData(data_buff, PACKET_FOOTER_LEN);
}
